#include <VertexBuffer.hpp>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_id);
    bind();
}

VertexBuffer::~VertexBuffer() noexcept
{
    unbind();
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::update_data(float const* buffer, unsigned int nbytes) const
{
    glBufferData(GL_ARRAY_BUFFER, nbytes, buffer, GL_STATIC_DRAW);
}

