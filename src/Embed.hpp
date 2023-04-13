#pragma once
#include "FixedString.hpp"
#include <array>
#include <string_view>
#include "Integers.hpp"

template<std::size_t N>
constexpr auto ctimeXor(const u8 (&arr)[N], std::string_view password) {
    std::array<u8, N> result; 
    for (std::size_t i=0; i<N; i++) {
        result[i] = arr[i] ^ password[i % password.size()];
    }
    return result;
}

class Embed {
    u8* m_data;
    std::size_t m_size;
    std::string_view m_password;

public:
    template<std::size_t N>
    Embed(std::array<u8, N>& data, std::string_view password) : m_data(data.data()), m_size(data.size()), m_password(password) {}

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
        return m_size-1;
    }


};

template<FixedString str>
extern Embed embed;
