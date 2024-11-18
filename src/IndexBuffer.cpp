#include <IndexBuffer.hpp>

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_id);
    bind();
}

IndexBuffer::~IndexBuffer() noexcept
{
    unbind();
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::update_indices(unsigned int* buffer, uint32_t nbytes) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbytes, buffer, GL_STATIC_DRAW);
}

