#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

class ElementBuffer {
private:
    unsigned int m_RendererID;  // Relevant for the OpenGL
    unsigned int m_Count;
public:
    ElementBuffer(const unsigned int* data, unsigned int count);
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

#endif // ELEMENT_BUFFER_H

