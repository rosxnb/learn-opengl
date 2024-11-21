#include <Init.hpp>

#include <GLFW/glfw3.h>
#include <cassert>


void init_glad()
{
    int status = gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );
    assert( (status != 0) && "FAILED: Glad initialization failed.");
    glEnable(GL_DEPTH_TEST);
}

