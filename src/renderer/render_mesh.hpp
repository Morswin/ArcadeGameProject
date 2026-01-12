#ifndef RENDER_MESH_H
#define RENDER_MESH_H

#include <string>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "element_buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"

struct RenderMesh {
    VertexArray* vao;
    VertexBuffer* vbo;
    ElementBuffer* ebo;
    Shader* shader;
    Texture* texture;

    RenderMesh(const float* vertices, unsigned int verticesCount, const unsigned int* elements, unsigned int elementCount, const std::string& texturePath) {
        vao = new VertexArray();
        vbo = new VertexBuffer(vertices, sizeof(float) * verticesCount);
        ebo = new ElementBuffer(elements, elementCount);
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao->AddBuffer(*vbo, layout);
        shader = new Shader("shaders/basic.glsl");
        shader->Bind();
        std::string basePath = SDL_GetBasePath();
        std::string actualTexPath = basePath + texturePath;
        texture = new Texture(actualTexPath);
        texture->Bind();
        shader->SetUniform1i("u_Texture", 0);
        glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -1.0f, 1.0f);  // This could be declared somewhere else, but I beleive that haveing 1 consistent projection for all elements in this game will be good enough. I will leave it hard coded here. Sorry if that upsets you.
        shader->SetUniform1mat4("u_MVP", projection);
        vao->Unbind();
        vbo->Unbind();
        ebo->Unbind();
        shader->Unbind();
    }

    ~RenderMesh() {
        delete vao;
        delete vbo;
        delete ebo;
        delete shader;
        delete texture;
    }
};

#endif // RENDER_MESH_H
