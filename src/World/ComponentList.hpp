#pragma once 
#include "Component.hpp"

class Transform;
class Physics;

using ComponentList = std::tuple<
    Transform,
    Physics
>;
