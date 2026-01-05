#ifndef RENDERER_H
#define RENDERER_H

#include "vertex_array.h"
#include "element_buffer.h"
#include "shader.h"

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader) const;
};

#endif // RENDERER_H
