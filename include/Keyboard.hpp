#pragma once

#include <GLFW/glfw3.h>


class Keyboard
{
public:
    explicit Keyboard(GLFWwindow* window);
    void process_input() const;

private:
    GLFWwindow* window;
};

