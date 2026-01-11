#ifndef RENDERER_H
#define RENDERER_H

#include "vertex_array.hpp"
#include "element_buffer.hpp"
#include "shader.hpp"

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader) const;
};

#endif // RENDERER_H
