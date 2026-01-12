#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include <string>
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "element_buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"

class RenderMesh {
private:
    VertexArray* m_VAO;
    VertexBuffer* m_VBO;
    ElementBuffer* m_EBO;
    Shader* m_Shader;
    Texture* m_Texture;
public:
    RenderMesh(const float* vertices, unsigned int verticesCount, const unsigned int* elements, unsigned int elementCount, const std::string& texturePath);
    ~RenderMesh();

    inline Shader* GetShader() const { return m_Shader; }
    inline VertexArray* GetVAO() const { return m_VAO; }
    inline ElementBuffer* GetEBO() const { return m_EBO; }
};

#endif // RENDER_MESH_H
