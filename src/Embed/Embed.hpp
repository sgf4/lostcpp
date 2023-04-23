#pragma once
#include "FixedString.hpp"
#include <array>
#include <string_view>
#include "Integers.hpp"

class Embed {
    u8* m_data;
    std::size_t m_size;
    std::string_view m_password;

public:
    template<std::size_t N>
    Embed(u8 (&data)[N], std::string_view password) : m_data(data), m_size(N), m_password(password) {}

    class XorInstance {
        Embed& e;
    public:
        XorInstance(Embed& e) : e(e) {
            e.doXor();
        }

        operator u8*() const {
            return e;
        }

        operator const char*() const {
            return e;
        }

        operator Embed&() {
            return e;
        }

        ~XorInstance() {
            e.doXor();
        }
    };

    XorInstance newXorInstance() {
        return {*this};
    }

    Embed& doXor() {
        for (std::size_t i=0; i<m_size; i++) {
            m_data[i] ^= m_password[i % m_password.size()];
        }
        return *this;
    }

    auto data() const {
        return m_data;
    }


    operator const char*() const {
        return reinterpret_cast<const char*>(data());
    }

    operator u8*() const {
        return data();
    }

    auto size() const {
        return m_size;
    }


};

template<FixedString str>
extern Embed embed;

template<FixedString str>
Embed::XorInstance getEmbed() {
    return embed<str>.newXorInstance();
}