#include <Camera.hpp>

Camera::Camera(glm::vec3 const& position, glm::vec3 const& target_position, glm::vec3 const& worldspace_up)
    : pitch{ 0.0f }, yaw{ -90.0f }, movement_speed{ 2.5f }, mouse_sensitivity{ 0.1f }, fov{ 45.f }
    , position{ position }, target_position{ target_position }, worldspace_up{ worldspace_up }
{ }

Camera::Camera(float pitch, float yaw, glm::vec3 const& position, glm::vec3 const& target_position, glm::vec3 const& worldspace_up)
    : pitch{ pitch }, yaw{ yaw }, movement_speed{ 2.5f }, mouse_sensitivity{ 0.1f }, fov{ 45.f }
    , position{ position }, target_position{ target_position }, worldspace_up{ worldspace_up }
{ }

glm::mat4 Camera::generate_view_space(bool use_glm) const
{
    // ensure target_position remains fixed dispite camera movement with keypress
    glm::vec3 target_position = this->target_position + position;

    if (use_glm)
        return glm::lookAt(position, target_position, worldspace_up);

    glm::vec3 direction_vector = glm::normalize(position - target_position);
    glm::vec3 right_vector     = glm::normalize(glm::cross(worldspace_up, direction_vector));
    glm::vec3 up_vector        = glm::cross(direction_vector, right_vector);

    glm::vec4 R{ right_vector, 0.f };
    glm::vec4 U{ up_vector, 0.f };
    glm::vec4 D{ direction_vector, 0.f };

    glm::vec4 W{ 0.f, 0.f, 0.f, 1.f };
    glm::mat4 axis_mat{ R, U, D, W };

    glm::mat4 translate_mat {
        glm::vec4{1.f, 0.f, 0.f, 0.f},
        glm::vec4{0.f, 1.f, 0.f, 0.f},
        glm::vec4{0.f, 0.f, 1.f, 0.f},
        glm::vec4{ -position, 1.f }
    };

    /*
                        ---        ---   ---       ---
                        | Rx Ry Rz 0 |   | 1 0 0 -Px |
        LookAt matrix = | Ux Uy Uz 0 | * | 0 1 0 -Py |
                        | Dx Dy Dz 0 |   | 0 0 1 -Pz |
                        | 0  0  0  1 |   | 0 0 0  1  |
                        ---        ---   ---       ---
    */
    return glm::transpose(axis_mat) * translate_mat;
}

void Camera::keyboard_callback(float delta_time, Camera::MOVEMENT direction)
{
    float velocity = movement_speed * delta_time;
    if( direction == MOVEMENT::FORWARD )
        position += velocity * target_position;
    if( direction == MOVEMENT::BACKWARD )
        position -= velocity * target_position;
    if( direction == MOVEMENT::LEFT )
        position -= velocity * glm::normalize(glm::cross(target_position, worldspace_up));
    if( direction == MOVEMENT::RIGHT )
        position += velocity * glm::normalize(glm::cross(target_position, worldspace_up));
}

void Camera::mouse_callback(float xoffset, float yoffset)
{
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if( pitch > 89.f )
        pitch = 89.f;
    if( pitch < -89.f )
        pitch = -89.f;

    glm::vec3 new_target_pos {
        std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch)),
        std::sin(glm::radians(pitch)),
        std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch))
    };
    target_position = glm::normalize(new_target_pos);
}

void Camera::scroll_callback(float xoffset, float yoffset)
{
    fov -= yoffset;
    if( fov < 10.f )
        fov = 10.f;
    if (fov > 45.f)
        fov = 45.f;
}

