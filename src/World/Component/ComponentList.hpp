#pragma once 
#include <Meta.hpp>

class Transform;
class Transform2D;
class Physics;
class Shader;
class Texture;
class Texture2D;

using ComponentList = std::tuple<
    Transform,
    Transform2D,
    Physics,
    Shader,
    Texture,
    Texture2D
>;

constexpr u32 NComponents = TupleSize<ComponentList>;