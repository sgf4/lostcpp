/*  Copyright (C) 2023 sgf4

This file is part of lostcpp.

lostcpp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

lostcpp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with lostcpp.  If not, see <http://www.gnu.org/licenses/>. */

#pragma once
#include <array>
#include <string_view>
#include <comptimestr.hpp>
#include <marble/integers.hpp>

struct Embed {
    ME::u8* data;
    std::size_t size;
    std::string_view password;

    template<std::size_t N>
    Embed(ME::u8 (&data)[N], std::string_view password) : data(data), size(N-1), password(password) {}

    class XorInstance {
        Embed& e;
    public:
        XorInstance(Embed& e) : e(e) {
            e.doXor();
        }

        operator ME::u8*() const {
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
        for (std::size_t i=0; i<size; i++) {
            data[i] ^= password[i % password.size()];
        }
        return *this;
    }


    operator const char*() const {
        return reinterpret_cast<const char*>(data);
    }

    operator ME::u8*() const {
        return data;
    }


};

template<CompTimeStr str>
extern Embed embed;

template<CompTimeStr str>
Embed::XorInstance getEmbed() {
    return embed<str>.newXorInstance();
}
