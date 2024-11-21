#include <Glfw.hpp>
#include <GLFW/glfw3.h>

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

void GLFW::init()
{
    static GLFW glfw_lifetime_obj;
}

GLFW::~GLFW()
{
    glfwTerminate();
}

