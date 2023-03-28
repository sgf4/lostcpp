#pragma once
#include <uuid_v4.h>

inline UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;

//std::string getUUID() {
//    return uuidGenerator.getUUID().bytes();
//}
//
//