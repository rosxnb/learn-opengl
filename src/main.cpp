#include <Init.hpp>
#include <Window.hpp>
#include <VertexBuffer.hpp>
#include <VertexArray.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <Texture.hpp>
#include <Camera.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    constexpr int w_width  = 950;
    constexpr int w_height = 800;

    Window window(w_width, w_height, "OpenGL");
    window.set_input_mode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    init_glad();

    VertexArray vao;
    VertexBuffer vbo;
    extern std::vector<float> deep_vertices;
    extern std::vector<glm::vec3> cube_positions;

    vbo.update_data(deep_vertices.data(), sizeof(float) * deep_vertices.size());
    vao.set_buffer_attribute(0, 3, 5 * sizeof(float), 0);
    vao.set_buffer_attribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.activate();

    Texture wall_texture; 
    wall_texture.load_image("assests/wall.jpg", GL_RGB);

    Texture face_texture( 1 );
    face_texture.load_image("assests/awesomeface.png", GL_RGBA);
    shader.set1("texture2", 1);

    Camera cam{ glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.f, 1.f, 0.f) };
    window.register_camera(&cam);
    window.mouse_move_events();
    window.mouse_scroll_events();

    float delta_time{ 0.f };
    float last_frame{ 0.f };
    while (!window.is_closed())
    {
        window.update_bgcolor(0.2f, 0.3f, 0.3f, 0.1f);
        window.update_flags(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float current_frame = glfwGetTime();
        delta_time          = current_frame - last_frame;
        last_frame          = current_frame;

        window.keyboard_events( std::bind_front(&Camera::keyboard_callback, &cam, delta_time) );

        glm::mat4 projection{ glm::perspective(glm::radians(cam.fov), (float)w_width/w_height, 0.1f, 100.f) };
        glm::mat4 view{ cam.generate_view_space() };

        for (int i = 0; i < cube_positions.size(); ++i)
        {
            glm::mat4 model(1.f);
            model = glm::translate(model, cube_positions[i]);

            model = (i == 0)
                ? glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f))
                : glm::rotate(model, glm::radians(20.0f * i), glm::vec3(0.5f, 1.0f, 0.0f));
            shader.set4x4("transform", projection * view * model);

            glDrawArrays(GL_TRIANGLES, 0, deep_vertices.size());
        }

        window.poll_events();
        window.swap_buffers();
    }

    return 0;
}

