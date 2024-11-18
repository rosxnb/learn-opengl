#include <Keyboard.hpp>


Keyboard::Keyboard(GLFWwindow* window)
    : window(window)
{ }

void Keyboard::process_input() const
{
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS )
        glfwSetWindowShouldClose(window, true);
    if( glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if( glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS )
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return ;
}

