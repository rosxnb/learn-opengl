#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <functional>
#include <string>

#include <Camera.hpp>


/*
   class GLFW
        - sets up window creation configurations
        - makes sure glfwTerminate() is called only once before exiting the app.
        - because glfwTerminate() destroys all opened window when called.
*/
class GLFW
{
public:
    static void init();

private:
    GLFW();
    ~GLFW();
};

class Window
{
public:
    Window(Window const& other)            = delete;
    Window& operator=(Window const& other) = delete;
    Window(Window&& other)                 = delete;
    Window& operator=(Window&& other)      = delete;

    Window(int width, int height, std::string const& title);
    ~Window() noexcept = default;
    operator bool() const;

    GLFWwindow* ptr() const;
    bool        is_closed() const;
    void        swap_buffers() const;
    void        poll_events() const;
    void        update_bgcolor(float r, float g, float b, float a) const;
    void        update_flags(uint64_t flags) const;

    void        register_viewport_callback() const;
    void        keyboard_events(std::function< void(GLFWwindow*) > const& f = nullptr) const;
    void        mouse_move_events() const;
    void        mouse_scroll_events() const;

    void        set_input_mode(uint32_t target, uint32_t mode);
    void        register_camera(Camera* cam);
    void        remove_camera();
    
private:
    int width, height;
    bool has_camera;
    std::string title;
    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};

