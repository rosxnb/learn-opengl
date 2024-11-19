#include <Init.hpp>
#include <Window.hpp>
#include <Keyboard.hpp>
#include <VertexBuffer.hpp>
#include <VertexArray.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    constexpr int w_width  = 950;
    constexpr int w_height = 800;

    Window window(w_width, w_height, "OpenGL");
    window.activate();
    window.set_input_mode(GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    init_glad();
    Keyboard keyboard(window.ptr());

    VertexArray vao;
    VertexBuffer vbo;
    extern std::vector<float> deep_vertices;

    vbo.update_data(deep_vertices.data(), sizeof(float) * deep_vertices.size());
    vao.set_buffer_attribute(0, 3, 5 * sizeof(float), 0);
    vao.set_buffer_attribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.activate();

    int texture_slot = 0;
    Texture wall_texture( texture_slot ); 
    wall_texture.load_image("assests/wall.jpg", GL_RGB);
    shader.set1("texture1", texture_slot++);

    std::unique_ptr<Image> awesomeface = std::make_unique<Image>("assests/awesomeface.png", GL_RGBA);
    Texture face_texture( std::move(awesomeface), texture_slot );
    shader.set1("texture2", texture_slot++);

    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)w_width/w_height, 0.1f, 100.f);

    glm::vec3 cube_positions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    while (!window.is_closed())
    {
        keyboard.process_input();
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view(1.f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));


        for (int i = 0; i < 10; ++i)
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

