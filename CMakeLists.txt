cmake_minimum_required(VERSION 2.8.4)
project(OpenGL_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenGL REQUIRED)

add_subdirectory(libs)

include_directories(
    libs/glfw/include/
    libs/glm/
    libs/glew/include/
    libs/SOIL/
    .
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1120
    SOIL
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set(SOURCE_FILES src/main.cpp
                 src/engine/Res.cpp
                 src/engine/Res.hpp
                 src/engine/VAO.cpp
                 src/engine/VAO.hpp
                 src/engine/Shader.cpp
                 src/engine/Shader.hpp
                 src/engine/Window.hpp
                 src/engine/Window.cpp
                 src/engine/Texture.cpp
                 src/engine/Texture.hpp)
add_executable(OpenGL_Test ${SOURCE_FILES} src/engine/Mesh.cpp src/engine/Mesh.hpp)
target_link_libraries(OpenGL_Test ${ALL_LIBS})

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res"
    COMMENT "Copy res directory to build tree"
    VERBATIM)
add_dependencies(OpenGL_Test copy_shaders)
