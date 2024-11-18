#include <VertexArray.hpp>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
    bind();
}

VertexArray::~VertexArray() noexcept
{
    unbind();
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::set_buffer_attribute(unsigned int loc, int ncomponents, int stride, uint64_t offset_bytes) const
{
    glVertexAttribPointer(
        loc         /* varibale location */, 
        ncomponents /* components in each vertex */, 
        GL_FLOAT    /* vertex data type */, 
        GL_FALSE    /* normalization needed? */, 
        stride      /* bytes offeset between vertex */, 
        (void *) offset_bytes /* offset to reach first vertex */
    );
    glEnableVertexAttribArray(loc);
}

