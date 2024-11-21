#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Camera.hpp>
#include <functional>


class Window
{
public:
    Window(Window const& other)            = delete;
    Window& operator=(Window const& other) = delete;
    Window(Window&& other)                 = delete;
    Window& operator=(Window&& other)      = delete;

    ~Window() noexcept                     = default;

    Window(int width, int height, std::string const& title);
    operator bool() const;

    GLFWwindow* ptr() const;
    bool        is_closed() const;
    void        swap_buffers() const;
    void        poll_events() const;
    void        update_flags(uint64_t flags) const;
    void        update_bgcolor(float r, float g, float b, float a) const;
    void        set_input_mode(uint32_t target, uint32_t mode) const;

    void        handle_viewport_resize() const;
    void        handle_mouse_movements() const;
    void        handle_mouse_scroll() const;
    void        process_keypress(std::function< void(Camera::MOVEMENT) > const& cam_keyboard_callback) const;

    void        register_camera(Camera* cam);
    void        remove_camera();
    
private:
    int width, height;
    bool has_camera;
    std::string title;
    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};

