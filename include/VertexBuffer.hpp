#pragma once

#include <glad/glad.h>

class VertexBuffer 
{
    public:
        VertexBuffer();
        ~VertexBuffer() noexcept;

        void unbind() const;
        void bind() const;
        void update_data(float const* buffer, unsigned int nbytes) const;

    private:
        unsigned int m_id;
};

