#include "Triangle.hpp"
#include "../Camera.hpp"
#include "../World.hpp"
#include <glm/vec3.hpp>

#include "../Component/Transform.hpp"
#include "../Component/Shader.hpp"

static constexpr std::initializer_list<float> vertices {
    -0.5f,-0.5f,    1.f, 1.f, 0.f,
    0.5f, -0.5f,   0.f, 1.f, 1.f,
    0.0f,  0.5f,   1.f, 0.f, 1.f
};

Triangle::Loader::Loader() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.begin(), GL_DYNAMIC_DRAW);
    
    glBindVertexArray(vao);
    glVertexAttribPointer(APOS, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, NULL);
    glEnableVertexAttribArray(APOS);
    glVertexAttribPointer(ACOLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(ACOLOR);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::Loader::update() {
    CAMERA.updateUniforms(shader);
    WORLD.updateUniforms(shader);
}


Triangle::Triangle(float x, float y, float z) {
    addComponent<Transform>(glm::vec3{x, y, z});
    addComponent<Shader>(loader->shader);
}

void Triangle::update() {
    Entity::update();

    glBindVertexArray(loader->vao);
    glUseProgram(loader->shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);

    if (WINDOW.getKey(KEY_RIGHT)) TRANSFORM.rotation.z += 500 * WTIME.getDelta();
    if (WINDOW.getKey(KEY_LEFT)) TRANSFORM.rotation.z -= 500 * WTIME.getDelta();
    if (WINDOW.getKey(KEY_UP)) TRANSFORM.rotation.x += 500 * WTIME.getDelta();
    if (WINDOW.getKey(KEY_DOWN)) TRANSFORM.rotation.x -= 500 * WTIME.getDelta();
}