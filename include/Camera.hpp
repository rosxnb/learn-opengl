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

    void keyboard_callback(float delta_time, Camera::MOVEMENT direction);
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
};

