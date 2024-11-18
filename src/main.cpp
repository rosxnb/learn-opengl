#include <Init.hpp>
#include <Window.hpp>
#include <Keyboard.hpp>
#include <VertexBuffer.hpp>
#include <VertexArray.hpp>
#include <IndexBuffer.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

int main()
{
    constexpr int w_width  = 1200;
    constexpr int w_height = 800;

    Window window(w_width, w_height, "OpenGL");
    window.activate();

    init_glad();
    Keyboard keyboard(window.ptr());
    VertexArray vao;

    float vertices[] = {
         // positions        // texture coordinates
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,    // position: bottom-left
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,    // position: bottom-right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,    // position: top-left
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f,    // position: top-right
    };
    VertexBuffer vbo;
    vbo.update_data(vertices, sizeof(vertices));
    vao.set_buffer_attribute(0, 3, 5 * sizeof(float), 0);
    vao.set_buffer_attribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));

    uint32_t indices[] = {
        0, 1, 2,
        1, 2, 3,
    };
    IndexBuffer ibo;
    ibo.update_indices(indices, sizeof(indices));


    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.activate();

    int texture_slot = 0;
    Texture wall_texture( texture_slot ); 
    wall_texture.load_image("assests/wall.jpg", GL_RGB);
    shader.set1("texture1", texture_slot++);

    std::unique_ptr<Image> awesomeface = std::make_unique<Image>("assests/awesomeface.png", GL_RGBA);
    Texture face_texture( std::move(awesomeface), texture_slot );
    shader.set1("texture2", texture_slot++);

    while (!window.is_closed())
    {
        keyboard.process_input();

        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(uint32_t), GL_UNSIGNED_INT, 0);

        window.poll_events();
        window.swap_buffers();
    }

    return 0;
}

