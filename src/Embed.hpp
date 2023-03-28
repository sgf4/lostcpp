#pragma once
#include "FixedString.hpp"

struct Embed {
    const unsigned char (&data)[];
    const unsigned int size;

    Embed(const unsigned char (&data)[], unsigned int size) : data(data), size(size) {}

    operator const unsigned char*() {
        return data;
    }
};

template<FixedString str>
inline Embed embed {{0x00}, 0};