#pragma once

#define CONCAT_(X1, X2) X1##X2 
#define CONCAT(X1, X2) CONCAT_(X1, X2)
#ifndef __INTELLISENSE__
#define CONSTRUCTOR(P, ...) static void __attribute__ ((constructor(P))) CONCAT(C, __LINE__)() { __VA_ARGS__ }
#define DESTRUCTOR(P, ...) static void __attribute__ ((destructor(P))) CONCAT(D, __LINE__)() { __VA_ARGS__ }
#else
#define CONSTRUCTOR(P, ...) 
#define DESTRUCTOR(P, ...)
#endif
