#include <Texture.hpp>
#include <cassert>


Texture::Texture(uint32_t slot)
    : slot{ slot }
    , id{ 0 }
    , image{ nullptr }
    , border_color{ {0.f, 0.f, 0.f, 0.f} }
{
    init();
}

Texture::Texture(std::unique_ptr<Image> image, uint32_t slot)
    : slot{ slot }
    , id{ 0 }
    , image{ std::move(image) }
    , border_color{ {0.f, 0.f, 0.f, 0.f} }
{
    init();
    generate_texture(this->image->format);
}

Texture::~Texture() noexcept
{
    unbind();
    glDeleteTextures(1, &id);
}

void Texture::init()
{
    glGenTextures(/* ntexture_count */ 1, &id);
    activate_texture_unit(this->slot);
    bind();
}

void Texture::load_image(std::string_view const& path, GLenum format, bool do_vflip, int desired_channels)
{
    image = std::make_unique<Image>(path, desired_channels, do_vflip);
    generate_texture(format);
}

void Texture::generate_texture(GLenum format) const
{
    glTexImage2D(
        GL_TEXTURE_2D    /* target texture */, 
        0                /* level_of_detail number; 0 for base image level, n for nth mipmap reduction image */, 
        format           /* number of color components we want to store in texture */, 
        image->width     /* width of texture image */, 
        image->height    /* height of texture image */, 
        0                /* border; this value must be 0 */, 
        format           /* number of color components in source image */, 
        GL_UNSIGNED_BYTE /* data type of pixel data */, 
        image->ptr()     /* pointer to image data */ 
    ); // generate texture using image
    glGenerateMipmap(GL_TEXTURE_2D); // make opengl generate mipmaps level for currently bound texture

    set_wrap(AXIS::X, GL_REPEAT);
    set_wrap(AXIS::Y, GL_REPEAT);
    set_filter(ZOOM::IN, GL_LINEAR);
    set_filter(ZOOM::OUT, GL_LINEAR_MIPMAP_LINEAR);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::activate_texture_unit(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
}

void Texture::set_wrap(AXIS axis, GLenum value) const
{
    switch(axis)
    {
        case AXIS::X:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, value);
            break;
        case AXIS::Y:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, value);
            break;
    }
}

void Texture::set_border_color(std::array<float, 4> const& border_color)
{
    this->border_color = border_color;
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, this->border_color.data());
}

void Texture::set_filter(ZOOM zoom, GLenum value) const
{
    switch(zoom)
    {
        case ZOOM::OUT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, value);
            break;
        case ZOOM::IN:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, value);
            break;
    }
}

uint32_t Texture::current_slot() const
{ return slot; }

