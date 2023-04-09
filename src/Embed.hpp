#pragma once
#include "FixedString.hpp"

struct Embed {
    const char* asdf = "akdsasdfjkasdfj";
    const unsigned char* m_data;
    const unsigned int m_size;

    Embed(unsigned char* data, unsigned int size) : m_data(data), m_size(size) {
    }

    operator const char*() {
        return reinterpret_cast<const char*>(m_data);
    }

    operator const unsigned char*() {
        return m_data;
    }

    const unsigned char* getData() const {
        return m_data;
    }
};

template<FixedString str>
extern Embed embed;
