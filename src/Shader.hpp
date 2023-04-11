#pragma once
#include "Embed.hpp"
#include "Integers.hpp"
#include "FixedString.hpp"
#include "Pimpl.hpp"

#include <unordered_map>
#include <string>

namespace GL {

class Shader {
    u32 m_program {};
    const char* m_vSource;
    const char* m_fSource;
    std::unordered_map<std::string, u32> m_attributes;
    std::unordered_map<std::string, u32> m_uniforms;

public:
    Shader();
    Shader(const char* vsource, const char* fsource);
    ~Shader();

    u32 getAttrib(const char* name) {
        return m_attributes[name];
    }
    u32 getUniform(const char* name) {
        return m_uniforms[name];
    }

    Shader& operator=(Shader&&);

    operator u32() {
        return m_program;
    }
};

template<FixedString str>
struct EmbedShader : Shader { 
    EmbedShader() : Shader(embed<"shaders/" + str + ".vert">, embed<"shaders/" + str + ".frag">) {

    }
};

}

