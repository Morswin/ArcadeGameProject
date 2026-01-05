#ifndef RENDERER_H
#define RENDERER_H

// TODO - those utility macros and functions should find other file to be in, so I don't have to do that forward class thing below. It is kindo f correct, but it looks ugly in my opinion.
#include <glad/glad.h>

#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__, __LINE__)

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class VertexArray;
class ElementBuffer;
class Shader;

class Renderer {
public:
    void Clear() const;
    void Draw(const VertexArray& va, const ElementBuffer& eb, const Shader& shader) const;
};

#endif // RENDERER_H
