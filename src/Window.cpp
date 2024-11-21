#include <Window.hpp>
#include <Glfw.hpp>
#include <cassert>


Window::Window(int width, int height, std::string const& title)
    : width{ width }, height{ height }, has_camera{ false }
    , title{ title }, window{ nullptr }
{
    GLFW::init();
    window = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> {
        glfwCreateWindow(
            this->width,
            this->height,
            this->title.c_str(),
            nullptr,
            nullptr
        ), 
        [](GLFWwindow* win){ if (win) glfwDestroyWindow(win); }
    };
    assert( (window && "FAILED: GLFW window wasn't created.") );

    glfwMakeContextCurrent(window.get());
    handle_viewport_resize();
}

Window::operator bool() const
{ return window != nullptr; }

GLFWwindow* Window::ptr() const
{ return window.get(); }

bool Window::is_closed() const
{ return glfwWindowShouldClose(window.get()); }

void Window::swap_buffers() const
{ glfwSwapBuffers(window.get()); }

void Window::poll_events() const
{ glfwPollEvents(); }

void Window::update_flags(uint64_t flags) const
{ glClear(flags); }

void Window::update_bgcolor(float r, float g, float b, float a) const
{ glClearColor(r, g, b, a); }

void Window::set_input_mode(uint32_t target, uint32_t mode) const
{ glfwSetInputMode(window.get(), target, mode); }

void Window::handle_viewport_resize() const
{
    glfwSetFramebufferSizeCallback(
        window.get(),
        [](GLFWwindow* win, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    );
}

void Window::handle_mouse_movements() const
{
    assert( has_camera && "ERROR: camera not attached to the window.");

    glfwSetCursorPosCallback(
        window.get(),
        [](GLFWwindow* win, double xpos, double ypos)
        {
            static bool first_mouse = true;
            static float last_x, last_y;

            if( first_mouse )
            {
                last_x = xpos;
                last_y = ypos;
                first_mouse = false;
            }

            float xoffset = xpos - last_x;
            float yoffset = last_y - ypos;
            last_x = xpos;
            last_y = ypos;

            auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
            cam->mouse_callback(xoffset, yoffset);
        }
    );
}

void Window::handle_mouse_scroll() const
{
    assert( has_camera && "ERROR: camera not attached to the window.");

    glfwSetScrollCallback(
        window.get(),
        [](GLFWwindow* win, double xoffset, double yoffset)
        {
            auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
            cam->scroll_callback(xoffset, yoffset);
        }
    );
}

void Window::process_keypress(std::function< void(Camera::MOVEMENT) > const& cam_keyboard_callback) const
{
    GLFWwindow* window{ this->window.get() };

    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS )
        glfwSetWindowShouldClose(window, true);
    if( glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if( glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if( cam_keyboard_callback )
    {
        if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
            cam_keyboard_callback( Camera::MOVEMENT::FORWARD );
        if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
            cam_keyboard_callback( Camera::MOVEMENT::BACKWARD );
        if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
            cam_keyboard_callback( Camera::MOVEMENT::LEFT );
        if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
            cam_keyboard_callback( Camera::MOVEMENT::RIGHT );
    }
}

void Window::register_camera(Camera* cam)
{
    glfwSetWindowUserPointer(window.get(), cam);
    has_camera = true;
}

void Window::remove_camera()
{ has_camera = false; }

