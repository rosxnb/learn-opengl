#pragma once

#include <glad/glad.h>

class IndexBuffer 
{
    public:
        explicit IndexBuffer();
        ~IndexBuffer() noexcept;

        void bind() const;
        void unbind() const;
        void update_indices(unsigned int* buffer, uint32_t nbytes) const;

    private:
        unsigned int m_id;
};
