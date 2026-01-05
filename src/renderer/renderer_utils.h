#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include <glad/glad.h>

#define GLCall(x) GLClearError();\
x;\
GLLogCall(#x, __FILE__, __LINE__)

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif // RENDERER_UTILS_H
