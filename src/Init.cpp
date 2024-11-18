#include <Init.hpp>
#include <cassert>


void init_glad()
{
    int status = gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );
    assert( (status != 0) && "FAILED: Glad initialization failed.");
}

