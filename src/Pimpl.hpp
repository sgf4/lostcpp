#pragma once 
#include "StdAfx.hpp"

template<typename T>
class Pimpl {
    T* m_pimpl {};

public:
    template<typename... Ts>
    Pimpl(Ts&&... ts) { 
        m_pimpl = new T(std::forward<Ts>(ts)...);
    }

    Pimpl(Pimpl&& other) {
        m_pimpl = other;
        other.m_pimpl = 0;
    }

    Pimpl& operator=(Pimpl&& other) {
        if (m_pimpl) delete m_pimpl;
        m_pimpl = other;
        other.m_pimpl = 0;
        return *this;
    }

    Pimpl(const Pimpl&) = delete;
    Pimpl& operator=(const Pimpl&) = delete;

    ~Pimpl() {
        delete m_pimpl;
    }

    operator T*() {
        return m_pimpl;
    }

    T* operator->() {
        return m_pimpl;
    }
};

#define PIMPL(NAME) class NAME##Impl; Pimpl<NAME##Impl> m_pimpl