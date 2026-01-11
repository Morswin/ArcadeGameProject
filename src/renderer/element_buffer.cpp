#include "element_buffer.hpp"

#include <cassert>
#include <glad/glad.h>
#include "renderer_utils.hpp"

ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    assert(sizeof(unsigned int) == sizeof(GLuint));  // Otherwise it will crash/stop working anyway. It would be wise to catch that early. It is unlikely though that those 2 types would be of different size.

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

ElementBuffer::~ElementBuffer() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void ElementBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void ElementBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


