#pragma once

#include <glad/glad.h>
#include <stb_image.hpp>
#include <string_view>
#include <memory>
#include <functional>

class Image
{
public:
    Image(Image&&)              = default;
    Image& operator=(Image&&)   = default;
    ~Image() noexcept           = default;

    explicit Image(std::string_view path, GLenum format = GL_RGBA, bool do_vflip = true, int desired_channels = 0);
    Image(Image const&);
    Image& operator=(Image const&);

    uint8_t* ptr() const;

private:
    void init(int desired_channels);

public:
    GLenum format;
    int width, height, nchannels;

private:
    bool vflipped;
    std::string img_path;
    std::unique_ptr<uint8_t, std::function<void(uint8_t*)>> buffer;
};

