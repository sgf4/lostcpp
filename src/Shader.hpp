#pragma once
#include "Embed/Embed.hpp"
#include "Integers.hpp"
#include "FixedString.hpp"

#include <unordered_map>

namespace GL {

class Shader {
    u32 m_program {};
    std::unordered_map<std::string, u32> m_attributes;
    std::unordered_map<std::string, u32> m_uniforms;

public:
    Shader();
    Shader(const Embed& vsource, const Embed& fsource);
    ~Shader();

    u32 getAttrib(const char* name) {
        return m_attributes[name];
    }
    u32 getUniform(const char* name) {
        return m_uniforms[name];
    }

    Shader(Shader&& other) {
        *this = std::move(other);
    }

    Shader& operator=(Shader&& other);

    operator u32() {
        return m_program;
    }
};

template<FixedString str1, FixedString str2 = str1>
struct EmbedShader : Shader { 
    EmbedShader() : Shader(
        embed<"shaders/" + str1 + ".vert">.newXorInstance(), 
        embed<"shaders/" + str2 + ".frag">.newXorInstance()
    ) {}
};

}

