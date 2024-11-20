#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
    enum class MOVEMENT
    { FORWARD, BACKWARD, LEFT, RIGHT };

    Camera(glm::vec3 const& position, glm::vec3 const& target_position, glm::vec3 const& worldspace_up);
    Camera(float pitch, float yaw, glm::vec3 const& position, glm::vec3 const& target_position, glm::vec3 const& worldspace_up);

    void keyboard_callback(float delta_time, GLFWwindow* window);
    void mouse_callback(float xpos, float ypos);
    void scroll_callback(float xoffset, float yoffset);
    glm::mat4 generate_view_space(bool use_glm = true) const;

public:
    float pitch, yaw;
    float movement_speed;
    float mouse_sensitivity;
    float fov;

    glm::vec3 position;
    glm::vec3 target_position;
    glm::vec3 worldspace_up;

    bool first_mouse = true;
    float last_x = 1. * 950 / 2;
    float last_y = 1. * 800 / 2;
};

