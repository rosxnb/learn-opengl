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
    : width  { width }
    , height { height }
    , title  { title }
{
    GLFW::init();
    window = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> {
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), 
        [](GLFWwindow* win){ if (win) glfwDestroyWindow(win); }
    };
}

bool Window::operator() () const
{ return window != nullptr; }

void Window::activate() const
{
    assert( (window && "FAILED: GLFW window creation failed.") );
    glfwMakeContextCurrent(window.get());
    register_viewport_callback(width, height);
}

GLFWwindow* Window::ptr() const
{ return window.get(); }

bool Window::is_closed() const
{ return glfwWindowShouldClose(window.get()); }

void Window::swap_buffers() const
{ glfwSwapBuffers(window.get()); }

void Window::poll_events() const
{ glfwPollEvents(); }

void Window::register_viewport_callback(int width, int height) const
{ glfwSetFramebufferSizeCallback(window.get(), Window::resize_callback); }

void Window::resize_callback(GLFWwindow* window, int width, int height)
{ glViewport(0, 0, width, height); }

