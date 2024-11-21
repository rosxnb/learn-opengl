#pragma once

/*
   class GLFW
        - sets up window creation configurations.
        - makes sure glfwTerminate() is called only once before exiting the app
          because glfwTerminate() destroys all opened windows when called.
*/
class GLFW
{
public:
    static void init();

private:
    GLFW();
    ~GLFW();
};

