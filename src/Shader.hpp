#pragma once
#include "Embed/Embed.hpp"
#include "Integers.hpp"
#include "FixedString.hpp"

#include <unordered_map>
#include <unordered_set>

namespace GL {

class Shader {
    u32 m_program {};
    std::unordered_map<std::string, u32> m_attributes;
    std::unordered_map<std::string, u32> m_uniforms;

public:
    static std::unordered_set<GL::Shader*> shaders;

    Shader();
    Shader(const Embed& vsource, const Embed& fsource);
    ~Shader();

    u32 getAttrib(const char* name) {
        return m_attributes.at(name);
    }
    u32 getUniform(const char* name) {
        return m_uniforms.at(name);
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
        getEmbed<"shaders/" + str1 + ".vert">(), 
        getEmbed<"shaders/" + str2 + ".frag">()
    ) {}
};

}

