#pragma once

#include <glad/glad.h>

class VertexBuffer 
{
    public:
        VertexBuffer();
        ~VertexBuffer() noexcept;

        void bind() const;
        void unbind() const;
        void update_data(float const* buffer, unsigned int nbytes) const;

    private:
        unsigned int m_id;
};

