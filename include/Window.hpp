#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <functional>
#include <string>


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

    bool        operator() () const;
    void        activate() const;
    GLFWwindow* ptr() const;
    bool        is_closed() const;
    void        swap_buffers() const;
    void        poll_events() const;
    void        register_viewport_callback(int width, int height) const;
    void        set_input_mode(uint32_t target, uint32_t mode);

private:
    static void resize_callback(GLFWwindow* window, int width, int height);
    
private:
    int width, height;
    std::string title;
    std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};

