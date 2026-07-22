#pragma once

#include <glm/glm.hpp>

// Thin aliases over GLM. Nothing in the rest of the codebase should
// #include <glm/...> directly outside of this header - if we ever need to
// swap the math library, this is the only file that changes.
namespace Engine::Math
{
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
    using Mat3 = glm::mat3;
    using Mat4 = glm::mat4;
}
