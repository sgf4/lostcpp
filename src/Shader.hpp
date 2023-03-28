#pragma once
#include "Embed.hpp"
#include "Integers.hpp"
#include "FixedString.hpp"
#include <memory>

class ShaderInfo;

class Shader {
    u32 m_program {};
    const char* m_vSource;
    const char* m_fSource;
    std::unique_ptr<ShaderInfo> m_shaderInfo;

public:
    Shader(const char* vsource, const char* fsource);
    ~Shader();

    u32 getUniform(const char* name);

    operator u32() {
        return m_program;
    }
    
};

template<FixedString str>
Shader shader { embed<str + ".frag">, embed<str + ".vert"> };