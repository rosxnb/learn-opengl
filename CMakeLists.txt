cmake_minimum_required(VERSION 3.30)

project(UltimateTicTacToe
    LANGUAGES CXX
    VERSION 0.1
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET_NAME OpenGLApp)
set(CMAKE_CXX_STANDARD 20)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wno-deprecated")

add_executable(${TARGET_NAME}
    src/dependencies/glad.cpp
    src/dependencies/stb_image.cpp

    src/Glfw.cpp
    src/Init.cpp
    src/Window.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/Shader.cpp
    src/Image.cpp
    src/Texture.cpp
    src/Camera.cpp
    src/main.cpp
    src/vertices.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE dependencies/include)
target_include_directories(${TARGET_NAME} PRIVATE include)

target_link_directories (${TARGET_NAME} PRIVATE dependencies/library)
target_link_libraries   (${TARGET_NAME} PRIVATE glfw.3.3.dylib)

if (APPLE)
    target_link_libraries(${TARGET_NAME} PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
    )
elseif(UNIX AND NOT APPLE)
    find_package(OpenGL)
    target_link_libraries(${TARGET_NAME} PRIVATE ${OPENGL_gl_LIBRARY})
endif()

