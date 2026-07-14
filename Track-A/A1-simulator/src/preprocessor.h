#ifndef A1_SIMULATOR_PREPROCESSOR_H
#define A1_SIMULATOR_PREPROCESSOR_H

#include <cstddef>
#include <map>
#include <string>
#include <vector>

struct MacroDefinition {
    std::string name;
    std::vector<std::string> parameters;
    std::string replacement;

    bool function_like() const { return !parameters.empty(); }
};

using MacroTable = std::map<std::string, MacroDefinition>;

struct SourceLocation {
    std::string file;
    std::size_t line = 0;
    std::string include_from;
    std::size_t include_line = 0;
};

struct SourceRecord {
    std::size_t output_line = 0;
    std::string text;
    SourceLocation location;
};

struct IncludeDependency {
    std::string including_file;
    std::string included_file;
    std::size_t include_line = 0;
};

struct PreprocessResult {
    bool ok = false;
    std::string source;
    std::vector<SourceRecord> source_records;
    std::vector<IncludeDependency> dependencies;
    MacroTable macros;
    std::vector<std::string> diagnostics;
};

PreprocessResult preprocessFiles(const std::vector<std::string> &files);

const SourceRecord *sourceRecordForOutputLine(const PreprocessResult &result,
                                              std::size_t output_line);

#endif
