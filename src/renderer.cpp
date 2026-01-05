#include "renderer.h"

#include <iostream>
#include "vertex_array.h"
#include "element_buffer.h"
#include "shader.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

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
