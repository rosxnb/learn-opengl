#include <Image.hpp>
#include <stdexcept>
#include <sstream>


Image::Image(std::string_view path, GLenum format, bool do_vflip, int desired_channels)
    : format{ format }
    , vflipped{ do_vflip }
    , img_path{ path }
{ init(desired_channels); }

Image::Image(Image const& other)
    : format{ other.format }
    , width{ other.width }
    , height{ other.height }
    , nchannels{ other.nchannels }
    , vflipped{ other.vflipped }
    , img_path{ other.img_path }
{ 
    buffer.reset();
    init(nchannels);
}

Image& Image::operator=(Image const& other)
{ 
    format = other.format;
    nchannels = other.nchannels;
    vflipped = other.vflipped;
    img_path = other.img_path;

    buffer.reset();
    init(nchannels);

    return *this;
}

void Image::init(int desired_channels)
{
    if (vflipped)
        stbi_set_flip_vertically_on_load(true);

    buffer = std::unique_ptr<uint8_t, std::function<void(uint8_t*)>> {
        stbi_load(img_path.data(), &width, &height, &nchannels, desired_channels),
        [](uint8_t* ptr){ if(ptr) stbi_image_free(ptr); }
    };

    if (!buffer)
    {
        std::ostringstream ss;
        ss << "FAILED: stb_image couldn't load image: ";
        ss << img_path << '.';

        throw std::runtime_error(ss.str());
    }
}

uint8_t* Image::ptr() const
{ return buffer.get(); }

