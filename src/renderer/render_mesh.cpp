#include "render_mesh.hpp"

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vertex_buffer_layout.hpp"

RenderMesh::RenderMesh(const float* vertices, unsigned int verticesCount, const unsigned int* elements, unsigned int elementCount, const std::string& texturePath, int spriteColumns, int spriteRows) {
    m_VAO = new VertexArray();
    m_VBO = new VertexBuffer(vertices, sizeof(float) * verticesCount);
    m_EBO = new ElementBuffer(elements, elementCount);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO, layout);
    m_Shader = new Shader("shaders/basic.glsl");
    m_Shader->Bind();
    std::string basePath = SDL_GetBasePath();
    std::string actualTexPath = basePath + texturePath;
    m_Texture = new Texture(actualTexPath);
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
    glm::mat4 projection = glm::ortho(-6.0f, 6.0f, -4.5f, 4.5f, -1.0f, 1.0f);  // This could be declared somewhere else, but I beleive that haveing 1 consistent projection for all elements in this game will be good enough. I will leave it hard coded here. Sorry if that upsets you.
    // Initially I thought that this is a good place to write the zoom in and out  functionality, but I figured out, that it won't work unless I put it into the GameElement class' display method. It works now, so I won't be messing with it around, unless necessary.
    m_Shader->SetUniform1mat4("u_Projection", projection);
    m_Shader->SetSpriteSize(spriteColumns, spriteRows);
    m_Shader->UpdateUV();
    m_VAO->Unbind();
    m_VBO->Unbind();
    m_EBO->Unbind();
    m_Shader->Unbind();
}

RenderMesh::~RenderMesh() {
    delete m_VAO;
    delete m_VBO;
    delete m_EBO;
    delete m_Shader;
    delete m_Texture;
}

void RenderMesh::SetSpriteCoodrdinate(int x, int y) {
    m_Shader->Bind();
    m_Shader->SetSpriteCoordinate(x, y);
    m_Shader->UpdateUV();
}

