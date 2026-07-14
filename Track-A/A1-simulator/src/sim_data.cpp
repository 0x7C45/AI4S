#include "sim_data.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <utility>

namespace {

constexpr uint32_t kMagic = 0x41315344U;
constexpr uint32_t kVersion = 2U;
constexpr std::size_t kMaxFileBytes = 256U * 1024U * 1024U;
constexpr uint32_t kMaxModules = 100000U;
constexpr uint32_t kMaxEntries = 1000000U;
constexpr uint32_t kMaxAstNodes = 4000000U;
constexpr uint32_t kMaxChildren = 1000000U;
constexpr uint32_t kMaxStringBytes = 1U << 20;

class ByteWriter {
public:
    void u8(uint8_t value) { data_.push_back(value); }

    void u32(uint32_t value) {
        for (unsigned int shift = 0; shift < 32; shift += 8) {
            data_.push_back(static_cast<uint8_t>((value >> shift) & 0xffU));
        }
    }

    void i32(int32_t value) { u32(static_cast<uint32_t>(value)); }

    void u64(uint64_t value) {
        for (unsigned int shift = 0; shift < 64; shift += 8) {
            data_.push_back(static_cast<uint8_t>((value >> shift) & 0xffU));
        }
    }

    void string(const std::string &value) {
        u32(static_cast<uint32_t>(value.size()));
        data_.insert(data_.end(), value.begin(), value.end());
    }

    void bytes(const std::vector<uint8_t> &value) {
        data_.insert(data_.end(), value.begin(), value.end());
    }

    const std::vector<uint8_t> &data() const { return data_; }

private:
    std::vector<uint8_t> data_;
};

class ByteReader {
public:
    explicit ByteReader(const std::vector<uint8_t> &data) : data_(data) {}

    bool u8(uint8_t &value) {
        if (remaining() < 1) return false;
        value = data_[pos_++];
        return true;
    }

    bool u32(uint32_t &value) {
        if (remaining() < 4) return false;
        value = static_cast<uint32_t>(data_[pos_]) |
                (static_cast<uint32_t>(data_[pos_ + 1]) << 8) |
                (static_cast<uint32_t>(data_[pos_ + 2]) << 16) |
                (static_cast<uint32_t>(data_[pos_ + 3]) << 24);
        pos_ += 4;
        return true;
    }

    bool i32(int32_t &value) {
        uint32_t raw = 0;
        if (!u32(raw)) return false;
        value = static_cast<int32_t>(raw);
        return true;
    }

    bool u64(uint64_t &value) {
        if (remaining() < 8) return false;
        value = 0;
        for (unsigned int shift = 0; shift < 64; shift += 8) {
            value |= static_cast<uint64_t>(data_[pos_++]) << shift;
        }
        return true;
    }

    bool string(std::string &value) {
        uint32_t length = 0;
        if (!u32(length) || length > kMaxStringBytes || remaining() < length) return false;
        value.assign(reinterpret_cast<const char *>(data_.data() + pos_), length);
        pos_ += length;
        return true;
    }

    bool done() const { return pos_ == data_.size(); }
    std::size_t remaining() const { return data_.size() - pos_; }

private:
    const std::vector<uint8_t> &data_;
    std::size_t pos_ = 0;
};

bool validNodeType(uint32_t value) {
    return value <= static_cast<uint32_t>(NodeType::MEMORY_DECL);
}

bool validEventEdge(uint8_t value) {
    return value <= static_cast<uint8_t>(EventEdge::LEVEL);
}

bool validPartSelectDirection(uint8_t value) {
    return value <= static_cast<uint8_t>(PartSelectDirection::MINUS);
}

bool readCount(ByteReader &reader, uint32_t limit, uint32_t &count) {
    return reader.u32(count) && count <= limit;
}

struct FlatAst {
    std::vector<const ASTNode *> nodes;
    std::unordered_map<const ASTNode *, uint32_t> indices;
};

bool flattenAst(const ASTNode *node, FlatAst &flat) {
    if (node == nullptr) return false;
    if (flat.indices.find(node) != flat.indices.end()) return true;
    if (flat.nodes.size() >= kMaxAstNodes) return false;
    const uint32_t index = static_cast<uint32_t>(flat.nodes.size());
    flat.indices.emplace(node, index);
    flat.nodes.push_back(node);
    if (node->children.size() > kMaxChildren) return false;
    for (const ASTNode *child : node->children) {
        if (!flattenAst(child, flat)) return false;
    }
    return true;
}

bool writeAst(ByteWriter &writer, const ModuleDef &module) {
    FlatAst flat;
    for (const ASTNode *item : module.items) {
        if (!flattenAst(item, flat)) return false;
    }
    writer.u32(static_cast<uint32_t>(flat.nodes.size()));
    for (const ASTNode *node : flat.nodes) {
        writer.u32(static_cast<uint32_t>(node->type));
        writer.string(node->value);
        writer.i32(node->msb);
        writer.i32(node->lsb);
        writer.i32(node->line_no);
        writer.string(node->source_file);
        writer.u8(static_cast<uint8_t>(node->event_edge));
        writer.u8(static_cast<uint8_t>(node->part_select_direction));
        writer.u32(static_cast<uint32_t>(node->children.size()));
        for (const ASTNode *child : node->children) {
            auto it = flat.indices.find(child);
            if (it == flat.indices.end()) return false;
            writer.u32(it->second);
        }
    }
    writer.u32(static_cast<uint32_t>(module.items.size()));
    for (const ASTNode *item : module.items) {
        auto it = flat.indices.find(item);
        if (it == flat.indices.end()) return false;
        writer.u32(it->second);
    }
    return true;
}

bool readAst(ByteReader &reader, ModuleDef &module) {
    uint32_t node_count = 0;
    if (!readCount(reader, kMaxAstNodes, node_count)) return false;

    struct NodeLinks {
        ASTNode *node = nullptr;
        std::vector<uint32_t> children;
    };
    std::vector<NodeLinks> links;
    links.reserve(node_count);
    for (uint32_t i = 0; i < node_count; ++i) {
        uint32_t type = 0;
        std::string value;
        int32_t msb = 0;
        int32_t lsb = 0;
        int32_t line_no = 0;
        std::string source_file;
        uint8_t edge = 0;
        uint8_t direction = 0;
        uint32_t child_count = 0;
        if (!reader.u32(type) || !validNodeType(type) || !reader.string(value) ||
            !reader.i32(msb) || !reader.i32(lsb) || !reader.i32(line_no) ||
            !reader.string(source_file) || !reader.u8(edge) || !validEventEdge(edge) ||
            !reader.u8(direction) || !validPartSelectDirection(direction) ||
            !readCount(reader, kMaxChildren, child_count)) {
            return false;
        }
        auto *node = new ASTNode();
        node->type = static_cast<NodeType>(type);
        node->value = std::move(value);
        node->msb = msb;
        node->lsb = lsb;
        node->line_no = line_no;
        node->source_file = std::move(source_file);
        node->event_edge = static_cast<EventEdge>(edge);
        node->part_select_direction = static_cast<PartSelectDirection>(direction);
        NodeLinks node_links;
        node_links.node = node;
        node_links.children.reserve(child_count);
        for (uint32_t child = 0; child < child_count; ++child) {
            uint32_t child_index = 0;
            if (!reader.u32(child_index) || child_index >= node_count) return false;
            node_links.children.push_back(child_index);
        }
        links.push_back(std::move(node_links));
    }

    for (const NodeLinks &node : links) {
        for (uint32_t child_index : node.children) {
            node.node->children.push_back(links[child_index].node);
        }
    }

    uint32_t item_count = 0;
    if (!readCount(reader, kMaxEntries, item_count)) return false;
    module.items.reserve(item_count);
    for (uint32_t i = 0; i < item_count; ++i) {
        uint32_t item_index = 0;
        if (!reader.u32(item_index) || item_index >= node_count) return false;
        module.items.push_back(links[item_index].node);
    }
    return true;
}

void writeBool(ByteWriter &writer, bool value) {
    writer.u8(value ? 1U : 0U);
}

bool readBool(ByteReader &reader, bool &value) {
    uint8_t raw = 0;
    if (!reader.u8(raw) || raw > 1U) return false;
    value = raw != 0;
    return true;
}

bool writePayload(const std::vector<ModuleDef *> &modules, std::vector<uint8_t> &payload) {
    ByteWriter writer;
    writer.u32(static_cast<uint32_t>(modules.size()));
    for (const ModuleDef *module : modules) {
        if (module == nullptr || module->params.size() > kMaxEntries ||
            module->parameter_decls.size() > kMaxEntries || module->signals.size() > kMaxEntries ||
            module->memories.size() > kMaxEntries || module->dependencies.size() > kMaxEntries) {
            return false;
        }
        writer.string(module->name);
        writer.string(module->source_file);
        writer.u32(module->source_line);

        writer.u32(static_cast<uint32_t>(module->params.size()));
        for (const auto &param : module->params) {
            writer.string(param.first);
            writer.u64(param.second);
        }

        writer.u32(static_cast<uint32_t>(module->parameter_decls.size()));
        for (const ParameterDef &param : module->parameter_decls) {
            writer.string(param.name);
            writer.u64(param.value);
            writeBool(writer, param.overridden);
            writer.string(param.source_file);
            writer.u32(param.source_line);
        }

        writer.u32(static_cast<uint32_t>(module->signals.size()));
        for (const SignalDef &signal : module->signals) {
            writer.string(signal.name);
            writer.i32(signal.width);
            writer.u64(signal.init_value);
            writeBool(writer, signal.is_reg);
            writeBool(writer, signal.is_signed);
            writer.string(signal.port_direction);
            writer.u32(signal.port_order);
            writeBool(writer, signal.is_port);
            writeBool(writer, signal.has_initial_value);
            writer.string(signal.init_expression);
            writer.string(signal.source_file);
            writer.u32(signal.source_line);
        }

        writer.u32(static_cast<uint32_t>(module->memories.size()));
        for (const MemoryDef &memory : module->memories) {
            writer.string(memory.name);
            writer.i32(memory.address_msb);
            writer.i32(memory.address_lsb);
            writer.i32(memory.element_width);
            writeBool(writer, memory.is_signed);
            writer.string(memory.source_file);
            writer.u32(memory.source_line);
        }

        writer.u32(static_cast<uint32_t>(module->dependencies.size()));
        for (const SourceDependency &dependency : module->dependencies) {
            writer.string(dependency.including_file);
            writer.string(dependency.included_file);
            writer.u32(dependency.include_line);
        }
        if (!writeAst(writer, *module)) return false;
    }
    payload = writer.data();
    return true;
}

bool readPayload(ByteReader &reader, std::vector<ModuleDef *> &modules) {
    uint32_t module_count = 0;
    if (!readCount(reader, kMaxModules, module_count)) return false;
    std::vector<ModuleDef *> decoded;
    decoded.reserve(module_count);
    for (uint32_t i = 0; i < module_count; ++i) {
        auto *module = new ModuleDef();
        if (!reader.string(module->name) || !reader.string(module->source_file) ||
            !reader.u32(module->source_line)) return false;

        uint32_t count = 0;
        if (!readCount(reader, kMaxEntries, count)) return false;
        for (uint32_t entry = 0; entry < count; ++entry) {
            std::string name;
            uint64_t value = 0;
            if (!reader.string(name) || !reader.u64(value)) return false;
            module->params.emplace(std::move(name), value);
        }

        if (!readCount(reader, kMaxEntries, count)) return false;
        module->parameter_decls.reserve(count);
        for (uint32_t entry = 0; entry < count; ++entry) {
            ParameterDef parameter;
            if (!reader.string(parameter.name) || !reader.u64(parameter.value) ||
                !readBool(reader, parameter.overridden) || !reader.string(parameter.source_file) ||
                !reader.u32(parameter.source_line)) return false;
            module->parameter_decls.push_back(std::move(parameter));
        }

        if (!readCount(reader, kMaxEntries, count)) return false;
        module->signals.reserve(count);
        for (uint32_t entry = 0; entry < count; ++entry) {
            SignalDef signal;
            int32_t width = 0;
            if (!reader.string(signal.name) || !reader.i32(width) || width <= 0 || width > 65536 ||
                !reader.u64(signal.init_value) || !readBool(reader, signal.is_reg) ||
                !readBool(reader, signal.is_signed) || !reader.string(signal.port_direction) ||
                !reader.u32(signal.port_order) || !readBool(reader, signal.is_port) ||
                !readBool(reader, signal.has_initial_value) || !reader.string(signal.init_expression) ||
                !reader.string(signal.source_file) || !reader.u32(signal.source_line)) return false;
            signal.width = width;
            module->signals.push_back(std::move(signal));
        }

        if (!readCount(reader, kMaxEntries, count)) return false;
        module->memories.reserve(count);
        for (uint32_t entry = 0; entry < count; ++entry) {
            MemoryDef memory;
            if (!reader.string(memory.name) || !reader.i32(memory.address_msb) ||
                !reader.i32(memory.address_lsb) || !reader.i32(memory.element_width) ||
                memory.element_width <= 0 || memory.element_width > 65536 ||
                !readBool(reader, memory.is_signed) || !reader.string(memory.source_file) ||
                !reader.u32(memory.source_line)) return false;
            module->memories.push_back(std::move(memory));
        }

        if (!readCount(reader, kMaxEntries, count)) return false;
        module->dependencies.reserve(count);
        for (uint32_t entry = 0; entry < count; ++entry) {
            SourceDependency dependency;
            if (!reader.string(dependency.including_file) ||
                !reader.string(dependency.included_file) || !reader.u32(dependency.include_line)) {
                return false;
            }
            module->dependencies.push_back(std::move(dependency));
        }
        if (!readAst(reader, *module)) return false;
        decoded.push_back(module);
    }
    modules.insert(modules.end(), decoded.begin(), decoded.end());
    return true;
}

}  // namespace

bool writeModuleDefs(const std::string &path, const std::vector<ModuleDef *> &modules) {
    if (modules.size() > kMaxModules) return false;
    std::vector<uint8_t> payload;
    if (!writePayload(modules, payload) || payload.size() > kMaxFileBytes) return false;

    ByteWriter frame;
    frame.u32(kMagic);
    frame.u32(kVersion);
    frame.u64(static_cast<uint64_t>(payload.size()));
    frame.bytes(payload);

    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (!output) return false;
    const auto &data = frame.data();
    output.write(reinterpret_cast<const char *>(data.data()), static_cast<std::streamsize>(data.size()));
    return output.good();
}

bool readModuleDefs(const std::string &path, std::vector<ModuleDef *> &modules) {
    std::ifstream input(path, std::ios::binary | std::ios::ate);
    if (!input) return false;
    const std::streamoff size = input.tellg();
    if (size < 0 || static_cast<uint64_t>(size) > kMaxFileBytes + 16U) return false;
    input.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(static_cast<std::size_t>(size));
    if (!data.empty()) {
        input.read(reinterpret_cast<char *>(data.data()), static_cast<std::streamsize>(data.size()));
        if (!input) return false;
    }

    ByteReader frame(data);
    uint32_t magic = 0;
    uint32_t version = 0;
    uint64_t payload_size = 0;
    if (!frame.u32(magic) || !frame.u32(version) || !frame.u64(payload_size) ||
        magic != kMagic || version != kVersion || payload_size != frame.remaining() ||
        payload_size > kMaxFileBytes) return false;

    std::vector<uint8_t> payload;
    payload.reserve(static_cast<std::size_t>(payload_size));
    for (uint64_t i = 0; i < payload_size; ++i) {
        uint8_t byte = 0;
        if (!frame.u8(byte)) return false;
        payload.push_back(byte);
    }
    ByteReader reader(payload);
    return readPayload(reader, modules) && reader.done();
}
