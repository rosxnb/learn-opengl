#pragma once

#include <glad/glad.h>

class VertexArray 
{
    public:
        explicit VertexArray();
        ~VertexArray() noexcept;

        void unbind() const;
        void bind() const;
        void set_buffer_attribute(unsigned int loc, int ncomponents, int stride, uint64_t offset_bytes) const;

    private:
        unsigned int m_id;
};
