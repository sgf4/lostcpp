#pragma once
#include "Embed.hpp"
#include "Integers.hpp"
#include "FixedString.hpp"
#include "Pimpl.hpp"

class ShaderInfo;


class Shader {
    PIMPL(Shader);

public:
    template<FixedString str>
    static Shader FromEmbed() {
        return Shader(embed<"shaders/" + str + ".vert">, embed<"shaders/" + str + ".frag">);
    }
    Shader(const char* vsource, const char* fsource);
    ~Shader();

    u32 getAttrib(const char* name);
    u32 getUniform(const char* name);

    operator u32();
};