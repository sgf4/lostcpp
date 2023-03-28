#pragma once
#include <cstdio>

template<std::size_t S>
struct FixedString {
    char str[S+1] {};

    consteval FixedString(const char (&str_)[S+1]) {
        for (std::size_t i=0; i<S+1; i++) {
            str[i] = str_[i];
        }
    }

    consteval const char* data() const {
        return str;
    }

    consteval std::size_t size() const {
        return S;
    }

    operator const char*() const {
        return str;
    }

    template<std::size_t s1>
    consteval auto operator+(const FixedString<s1> str1) const {
        char newchar[s1+S+1] {};
        for (std::size_t i=0; i<S; i++) newchar[i] = str[i];
        for (std::size_t i=0; i<s1; i++) newchar[S+i] = str1[i];
        return FixedString<s1+S>(newchar);
    }

    template<std::size_t s1>
    consteval bool operator==(const FixedString<s1> str2) const {
        if (str2.size != S) { return false; }
        for (std::size_t i=0; i<str2.size;i++) {
            if (str2.str[i] != str[i]) {
                return false;
            }
        }
        return true;
    }

    template<std::size_t s1>
    consteval bool operator==(const char (&str2) [s1]) const {
        return (*this) == FixedString<s1-1>(str2);
    }

    consteval char operator[](std::size_t n) const {
        return str[n];
    }

};

template<std::size_t N> FixedString(const char (&) [N]) -> FixedString<N-1>;
template<std::size_t N> FixedString(char (&) [N]) -> FixedString<N-1>;


template<std::size_t s1, std::size_t s2>
consteval auto operator+(FixedString<s1> fs, const char (&str1) [s2]) {
    return fs + FixedString<s2-1>(str1);
}

template<std::size_t s1, std::size_t s2>
consteval auto operator+(const char (&str1) [s2], FixedString<s1> fs) {
    return FixedString<s2-1>(str1) + fs;
}