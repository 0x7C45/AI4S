#include "preprocessor.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <utility>

namespace {

namespace fs = std::filesystem;

constexpr std::size_t kMaxIncludeDepth = 128;
constexpr std::size_t kMaxMacroExpansionDepth = 64;
constexpr std::size_t kMaxOutputBytes = 32U * 1024U * 1024U;
constexpr std::size_t kMaxOutputLines = 1000000;

struct IncludeFrame {
    std::string file;
    std::string include_from;
    std::size_t include_line = 0;
};

struct ConditionalFrame {
    bool parent_active = true;
    bool branch_taken = false;
    bool active = true;
};

struct Context {
    PreprocessResult result;
    std::set<std::string> active_files;
    std::vector<IncludeFrame> include_stack;
    MacroTable macros;
    std::set<std::string> expansion_stack;
    std::size_t output_line = 0;
};

std::string trim(const std::string &value) {
    std::size_t first = 0;
    while (first < value.size() && std::isspace(static_cast<unsigned char>(value[first]))) ++first;
    std::size_t last = value.size();
    while (last > first && std::isspace(static_cast<unsigned char>(value[last - 1]))) --last;
    return value.substr(first, last - first);
}

bool isIdentifierStart(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch)) || ch == '_';
}

bool isIdentifierChar(char ch) {
    return std::isalnum(static_cast<unsigned char>(ch)) || ch == '_' || ch == '$';
}

std::string canonicalPath(const std::string &path) {
    std::error_code ec;
    fs::path canonical = fs::weakly_canonical(fs::absolute(fs::path(path)), ec);
    if (ec) return fs::absolute(fs::path(path)).lexically_normal().string();
    return canonical.string();
}

void diagnostic(Context &ctx, const IncludeFrame &frame, const std::string &message) {
    std::ostringstream out;
    out << frame.file << ':' << frame.include_line << ": " << message;
    ctx.result.diagnostics.push_back(out.str());
}

bool currentActive(const std::vector<ConditionalFrame> &conditionals) {
    return conditionals.empty() || conditionals.back().active;
}

bool parseIdentifier(const std::string &text, std::size_t &pos, std::string &identifier) {
    if (pos >= text.size() || !isIdentifierStart(text[pos])) return false;
    const std::size_t start = pos++;
    while (pos < text.size() && isIdentifierChar(text[pos])) ++pos;
    identifier = text.substr(start, pos - start);
    return true;
}

bool parseMacroDefinition(const std::string &body, MacroDefinition &macro) {
    std::size_t pos = 0;
    while (pos < body.size() && std::isspace(static_cast<unsigned char>(body[pos]))) ++pos;
    if (!parseIdentifier(body, pos, macro.name)) return false;

    if (pos < body.size() && body[pos] == '(') {
        ++pos;
        while (true) {
            while (pos < body.size() && std::isspace(static_cast<unsigned char>(body[pos]))) ++pos;
            if (pos < body.size() && body[pos] == ')') {
                ++pos;
                break;
            }
            std::string parameter;
            if (!parseIdentifier(body, pos, parameter)) return false;
            macro.parameters.push_back(parameter);
            while (pos < body.size() && std::isspace(static_cast<unsigned char>(body[pos]))) ++pos;
            if (pos < body.size() && body[pos] == ',') {
                ++pos;
                continue;
            }
            if (pos < body.size() && body[pos] == ')') {
                ++pos;
                break;
            }
            return false;
        }
    }
    macro.replacement = trim(body.substr(pos));
    return true;
}

bool parseInvocationArguments(const std::string &text, std::size_t open_pos,
                              std::vector<std::string> &arguments, std::size_t &end_pos) {
    if (open_pos >= text.size() || text[open_pos] != '(') return false;
    std::size_t pos = open_pos + 1;
    std::size_t start = pos;
    int depth = 0;
    bool in_string = false;
    bool escaped = false;
    while (pos < text.size()) {
        const char ch = text[pos];
        if (in_string) {
            if (escaped) escaped = false;
            else if (ch == '\\') escaped = true;
            else if (ch == '"') in_string = false;
        } else if (ch == '"') {
            in_string = true;
        } else if (ch == '(') {
            ++depth;
        } else if (ch == ')') {
            if (depth == 0) {
                const std::string last = trim(text.substr(start, pos - start));
                if (!last.empty() || !arguments.empty()) arguments.push_back(last);
                end_pos = pos + 1;
                return true;
            }
            --depth;
        } else if (ch == ',' && depth == 0) {
            arguments.push_back(trim(text.substr(start, pos - start)));
            start = pos + 1;
        }
        ++pos;
    }
    return false;
}

std::string substituteMacro(const MacroDefinition &macro,
                            const std::vector<std::string> &arguments) {
    if (!macro.function_like()) return macro.replacement;
    std::map<std::string, std::string> substitutions;
    for (std::size_t i = 0; i < macro.parameters.size(); ++i) {
        substitutions[macro.parameters[i]] = i < arguments.size() ? arguments[i] : std::string();
    }

    std::string output;
    bool in_string = false;
    bool escaped = false;
    for (std::size_t pos = 0; pos < macro.replacement.size();) {
        const char ch = macro.replacement[pos];
        if (in_string) {
            output += ch;
            if (escaped) escaped = false;
            else if (ch == '\\') escaped = true;
            else if (ch == '"') in_string = false;
            ++pos;
            continue;
        }
        if (ch == '"') {
            in_string = true;
            output += ch;
            ++pos;
            continue;
        }
        if (isIdentifierStart(ch)) {
            std::size_t end = pos + 1;
            while (end < macro.replacement.size() && isIdentifierChar(macro.replacement[end])) ++end;
            const std::string token = macro.replacement.substr(pos, end - pos);
            auto it = substitutions.find(token);
            output += it == substitutions.end() ? token : it->second;
            pos = end;
            continue;
        }
        output += ch;
        ++pos;
    }
    return output;
}

std::string expandText(Context &ctx, const std::string &text, std::size_t depth,
                       const IncludeFrame &frame, bool &ok) {
    if (depth > kMaxMacroExpansionDepth) {
        diagnostic(ctx, frame, "macro expansion depth exceeded");
        ok = false;
        return text;
    }

    std::string output;
    bool in_string = false;
    bool in_block_comment = false;
    bool escaped = false;
    for (std::size_t pos = 0; pos < text.size();) {
        const char ch = text[pos];
        if (in_block_comment) {
            output += ch;
            if (ch == '*' && pos + 1 < text.size() && text[pos + 1] == '/') {
                output += '/';
                pos += 2;
                in_block_comment = false;
            } else {
                ++pos;
            }
            continue;
        }
        if (in_string) {
            output += ch;
            if (escaped) escaped = false;
            else if (ch == '\\') escaped = true;
            else if (ch == '"') in_string = false;
            ++pos;
            continue;
        }
        if (ch == '"') {
            in_string = true;
            output += ch;
            ++pos;
            continue;
        }
        if (ch == '/' && pos + 1 < text.size() && text[pos + 1] == '/') {
            output.append(text.substr(pos));
            break;
        }
        if (ch == '/' && pos + 1 < text.size() && text[pos + 1] == '*') {
            output += "/*";
            pos += 2;
            in_block_comment = true;
            continue;
        }
        if (ch != '`') {
            output += ch;
            ++pos;
            continue;
        }

        std::size_t name_pos = pos + 1;
        std::string name;
        if (!parseIdentifier(text, name_pos, name)) {
            output += ch;
            ++pos;
            continue;
        }
        auto macro_it = ctx.macros.find(name);
        if (macro_it == ctx.macros.end()) {
            output.append(text, pos, name_pos - pos);
            pos = name_pos;
            continue;
        }
        const MacroDefinition &macro = macro_it->second;
        std::vector<std::string> arguments;
        std::size_t end_pos = name_pos;
        if (macro.function_like()) {
            while (end_pos < text.size() && std::isspace(static_cast<unsigned char>(text[end_pos]))) ++end_pos;
            if (end_pos >= text.size() || text[end_pos] != '(' ||
                !parseInvocationArguments(text, end_pos, arguments, end_pos)) {
                output.append(text, pos, name_pos - pos);
                pos = name_pos;
                continue;
            }
        }
        if (ctx.expansion_stack.count(name) != 0) {
            diagnostic(ctx, frame, "recursive macro expansion for `" + name + "`");
            ok = false;
            output.append(text, pos, end_pos - pos);
            pos = end_pos;
            continue;
        }
        ctx.expansion_stack.insert(name);
        const std::string replacement = substituteMacro(macro, arguments);
        bool nested_ok = true;
        output += expandText(ctx, replacement, depth + 1, frame, nested_ok);
        ctx.expansion_stack.erase(name);
        ok = ok && nested_ok;
        pos = end_pos;
    }
    return output;
}

bool parseIncludePath(const std::string &directive, std::string &path) {
    const std::string rest = trim(directive);
    if (rest.empty()) return false;
    if (rest.front() == '"') {
        const std::size_t end = rest.find('"', 1);
        if (end == std::string::npos) return false;
        path = rest.substr(1, end - 1);
        return true;
    }
    if (rest.front() == '<') {
        const std::size_t end = rest.find('>', 1);
        if (end == std::string::npos) return false;
        path = rest.substr(1, end - 1);
        return true;
    }
    return false;
}

bool processFile(Context &ctx, const std::string &requested_path,
                 const std::string &include_from, std::size_t include_line);

void emitLine(Context &ctx, const std::string &line, const IncludeFrame &frame) {
    if (ctx.result.source.size() + line.size() + 1 > kMaxOutputBytes ||
        ctx.output_line >= kMaxOutputLines) {
        diagnostic(ctx, frame, "preprocessor output limit exceeded");
        return;
    }
    ++ctx.output_line;
    ctx.result.source += line;
    ctx.result.source.push_back('\n');
    ctx.result.source_records.push_back({ctx.output_line, line,
                                         {frame.file, frame.include_line,
                                          frame.include_from, frame.include_line}});
}

bool processFile(Context &ctx, const std::string &requested_path,
                 const std::string &include_from, std::size_t include_line) {
    if (ctx.include_stack.size() >= kMaxIncludeDepth) {
        IncludeFrame frame{canonicalPath(requested_path), include_from, include_line};
        diagnostic(ctx, frame, "include nesting depth exceeded");
        return false;
    }

    const std::string path = canonicalPath(requested_path);
    IncludeFrame frame{path, include_from, include_line};
    if (ctx.active_files.count(path) != 0) {
        diagnostic(ctx, frame, "recursive include rejected");
        return false;
    }

    std::ifstream input(path);
    if (!input) {
        diagnostic(ctx, frame, "cannot open source file");
        return false;
    }

    ctx.active_files.insert(path);
    ctx.include_stack.push_back(frame);
    std::vector<ConditionalFrame> conditionals;
    std::string raw_line;
    std::size_t line_number = 0;
    bool ok = true;
    while (std::getline(input, raw_line)) {
        ++line_number;
        const std::string stripped = trim(raw_line);
        const bool has_directive = !stripped.empty() && stripped.front() == '`';
        std::string directive = stripped;
        if (has_directive) directive.erase(0, 1);
        std::size_t directive_end = 0;
        while (directive_end < directive.size() && isIdentifierChar(directive[directive_end])) ++directive_end;
        const std::string directive_name = directive.substr(0, directive_end);
        const std::string directive_args = trim(directive.substr(directive_end));
        const IncludeFrame line_frame{path, include_from, line_number};
        const bool is_control_directive = has_directive &&
            (directive_name == "ifdef" || directive_name == "ifndef" ||
             directive_name == "else" || directive_name == "endif" ||
             directive_name == "define" || directive_name == "undef" ||
             directive_name == "include" || directive_name == "timescale" ||
             directive_name == "resetall" || directive_name == "default_nettype");

        if (is_control_directive &&
            (directive_name == "ifdef" || directive_name == "ifndef")) {
            const bool parent = currentActive(conditionals);
            const bool defined = ctx.macros.count(directive_args) != 0;
            const bool condition = directive_name == "ifdef" ? defined : !defined;
            conditionals.push_back({parent, parent && condition, parent && condition});
            continue;
        }
        if (is_control_directive && directive_name == "else") {
            if (conditionals.empty()) {
                diagnostic(ctx, line_frame, "unmatched `else");
                ok = false;
            } else {
                auto &conditional = conditionals.back();
                conditional.active = conditional.parent_active && !conditional.branch_taken;
                conditional.branch_taken = true;
            }
            continue;
        }
        if (has_directive && directive_name == "endif") {
            if (conditionals.empty()) {
                diagnostic(ctx, line_frame, "unmatched `endif");
                ok = false;
            } else {
                conditionals.pop_back();
            }
            continue;
        }

        if (!currentActive(conditionals)) continue;
        if (has_directive && directive_name == "define") {
            MacroDefinition macro;
            if (!parseMacroDefinition(directive_args, macro)) {
                diagnostic(ctx, line_frame, "malformed `define");
                ok = false;
            } else {
                ctx.macros[macro.name] = macro;
            }
            continue;
        }
        if (has_directive && directive_name == "undef") {
            ctx.macros.erase(directive_args);
            continue;
        }
        if (has_directive && directive_name == "include") {
            std::string include_path;
            if (!parseIncludePath(directive_args, include_path)) {
                diagnostic(ctx, line_frame, "malformed `include path");
                ok = false;
                continue;
            }
            const std::string resolved = (fs::path(path).parent_path() / include_path).string();
            ctx.result.dependencies.push_back({path, canonicalPath(resolved), line_number});
            if (!processFile(ctx, resolved, path, line_number)) ok = false;
            continue;
        }
        if (is_control_directive) continue;

        bool expanded_ok = true;
        const std::string expanded = expandText(ctx, raw_line, 0, line_frame, expanded_ok);
        emitLine(ctx, expanded, line_frame);
        ok = ok && expanded_ok;
    }

    if (!conditionals.empty()) {
        diagnostic(ctx, {path, include_from, line_number}, "unterminated conditional directive");
        ok = false;
    }
    ctx.include_stack.pop_back();
    ctx.active_files.erase(path);
    return ok;
}

}  // namespace

PreprocessResult preprocessFiles(const std::vector<std::string> &files) {
    Context ctx;
    bool ok = !files.empty();
    for (const std::string &file : files) {
        if (!processFile(ctx, file, std::string(), 0)) ok = false;
    }
    ctx.result.ok = ok && ctx.result.diagnostics.empty();
    ctx.result.macros = ctx.macros;
    return std::move(ctx.result);
}

const SourceRecord *sourceRecordForOutputLine(const PreprocessResult &result,
                                              std::size_t output_line) {
    if (output_line == 0 || output_line > result.source_records.size()) return nullptr;
    const SourceRecord &record = result.source_records[output_line - 1];
    return record.output_line == output_line ? &record : nullptr;
}
