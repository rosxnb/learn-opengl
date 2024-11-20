#include <Window.hpp>
#include <cassert>


GLFW::GLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__) && defined(__MACH__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // defined(__APPLE__) && defined(__MACH__)
}

GLFW::~GLFW()
{
    glfwTerminate();
}

void GLFW::init()
{
    static GLFW glfw_lifetime_obj;
}


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
    register_viewport_callback();
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

void Window::update_bgcolor(float r, float g, float b, float a) const
{ glClearColor(r, g, b, a); }

void Window::update_flags(uint64_t flags) const
{ glClear(flags); }

void Window::set_input_mode(uint32_t target, uint32_t mode)
{ glfwSetInputMode(window.get(), target, mode); }

void Window::register_camera(Camera* cam)
{
    glfwSetWindowUserPointer(window.get(), cam);
    has_camera = true;
}

void Window::remove_camera()
{ has_camera = false; }

void Window::register_viewport_callback() const
{
    glfwSetFramebufferSizeCallback(
        window.get(),
        [](GLFWwindow* win, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
    );
}

void Window::keyboard_events(std::function< void(GLFWwindow*) > const& f) const
{
    GLFWwindow* window{ this->window.get() };

    if( f )
        f(window);

    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS )
        glfwSetWindowShouldClose(window, true);
    if( glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if( glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Window::mouse_move_events() const
{
    assert( has_camera && "ERROR: camera not attached to the window.");

    glfwSetCursorPosCallback(
        window.get(),
        [](GLFWwindow* win, double xpos, double ypos)
        {
            auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(win));
            cam->mouse_callback(xpos, ypos);
        }
    );
}

void Window::mouse_scroll_events() const
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

