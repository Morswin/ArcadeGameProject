#include "renderer.h"

#include <iostream>
#include <glad/glad.h>
#include "renderer_utils.h"

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader) const {
    shader.Bind();
    // uniform
    va.Bind();
    eb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, eb.GetCount(), GL_UNSIGNED_INT, nullptr));
}
