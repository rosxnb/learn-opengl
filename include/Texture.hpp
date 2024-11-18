#pragma once

#include <glad/glad.h>
#include <stb_image.hpp>
#include <memory>
#include <array>
#include <Image.hpp>

class Texture 
{
public:
    enum class AXIS { X, Y };
    enum class ZOOM { IN, OUT };

public:
    explicit Texture(uint32_t slot = 0);
    Texture(std::unique_ptr<Image> image, uint32_t slot = 0);
    ~Texture() noexcept;

    void load_image(std::string_view const& path, GLenum format = GL_RGBA, bool do_vflip = true, int desired_channels = 0);

    void     activate_texture_unit(uint32_t slot) const;
    void     bind() const;
    void     unbind() const;
    void     set_filter(ZOOM zoom, GLenum value) const;
    void     set_wrap(AXIS axis, GLenum value) const;
    void     set_border_color(std::array<float, 4> const& border_color);
    uint32_t current_slot() const;

private:
    void init();
    void generate_texture(GLenum format) const;

private:
    uint32_t slot;
    uint32_t id;
    std::unique_ptr<Image> image;
    std::array<float, 4> border_color;
};

