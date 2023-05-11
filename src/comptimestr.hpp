#include <algorithm>

template<std::size_t N>
struct CompTimeStr {
    char data[N] {};

    consteval CompTimeStr(const char (&str)[N]) {
        std::copy_n(str, N, data);
    }

    consteval bool operator==(const CompTimeStr<N> str) const {
        return std::equal(str.data, str.data+N, data);
    }

    template<std::size_t N2>
    consteval bool operator==(const CompTimeStr<N2> s) const {
        return false;
    }

    template<std::size_t N2>
    consteval CompTimeStr<N+N2-1> operator+(const CompTimeStr<N2> str) const {
        char newchar[N+N2-1] {};
        std::copy_n(data, N-1, newchar);
        std::copy_n(str.data, N2, newchar+N-1);
        return newchar;
    }

    consteval char operator[](std::size_t n) const {
        return data[n];
    }

    consteval std::size_t size() const {
        return N-1;
    }
};

template<std::size_t s1, std::size_t s2>
consteval auto operator+(CompTimeStr<s1> fs, const char (&str) [s2]) {
    return fs + CompTimeStr<s2>(str);
}

template<std::size_t s1, std::size_t s2>
consteval auto operator+(const char (&str) [s2], CompTimeStr<s1> fs) {
    return CompTimeStr<s2>(str) + fs;
}

template<std::size_t s1, std::size_t s2>
consteval auto operator==(CompTimeStr<s1> fs, const char (&str) [s2]) {
    return fs == CompTimeStr<s2>(str);
}

template<std::size_t s1, std::size_t s2>
consteval auto operator==(const char (&str) [s2], CompTimeStr<s1> fs) {
    return CompTimeStr<s2>(str) == fs;
}
