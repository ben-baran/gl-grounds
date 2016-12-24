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

set(SOURCE_FILES #src/main.cpp
                 src/engine/util/Res.cpp
                 src/engine/util/Res.hpp
                 src/engine/render/VAO.cpp
                 src/engine/render/VAO.hpp
                 src/engine/render/Shader.cpp
                 src/engine/render/Shader.hpp
                 src/engine/util/Window.hpp
                 src/engine/util/Window.cpp
                 src/engine/render/Texture.cpp
                 src/engine/render/Texture.hpp
                 src/engine/render/SolidRectangle.cpp
                 src/engine/render/SolidRectangle.hpp
                 src/engine/anim/Transform.cpp
                 src/engine/anim/Transform.hpp
                 src/engine/util/KeyHandler.cpp
                 src/engine/util/KeyHandler.hpp
                 src/engine/util/MouseHandler.cpp
                 src/engine/util/MouseHandler.hpp
                 src/engine/Scene.cpp
                 src/engine/Scene.hpp
                 src/engine/Entity.cpp
                 src/engine/Entity.hpp
                 src/engine/Run.cpp
                 src/engine/Run.hpp
                 src/engine/render/Renderable.cpp
                 src/engine/render/Renderable.hpp
                 src/engine/physics/Collider.cpp
                 src/engine/physics/Collider.hpp
                 src/engine/physics/RectangleCollider.cpp
                 src/engine/physics/RectangleCollider.hpp
                 src/engine/render/Camera.cpp
                 src/engine/render/Camera.hpp

                 src/game/TestRunner.cpp
                 src/game/TestRunner.hpp

                 src/engine/anim/Ease.cpp
                 src/engine/anim/Ease.hpp

		         #src/game/Simple3D.cpp
		         #src/game/Simple3D.hpp
                 #src/engine/render/Triangle.cpp
                 #src/engine/render/Triangle.hpp

                 src/game/procedural/GridManip.cpp
                 src/game/procedural/GridManip.hpp
                 src/engine/render/SolidGrid.cpp
                 src/engine/render/SolidGrid.hpp
                 src/engine/physics/GridCollider.cpp
                 src/engine/physics/GridCollider.hpp
                 src/engine/render/SolidPolygon.cpp
                 src/engine/render/SolidPolygon.hpp
                 src/engine/physics/PolygonCollider.cpp
                 src/engine/physics/PolygonCollider.hpp
                 src/engine/render/SolidMarchingSquares.cpp
                 src/engine/render/SolidMarchingSquares.hpp
                 src/engine/physics/MarchingSquaresCollider.cpp
                 src/engine/physics/MarchingSquaresCollider.hpp
                 src/engine/render/TexturedRectangle.cpp
                 src/engine/render/TexturedRectangle.hpp
                 src/engine/render/TextRenderable.cpp
                 src/engine/render/TextRenderable.hpp
                 src/game/procedural/GridWalk.cpp
                 src/game/procedural/GridWalk.hpp
                 src/ui/UIC.cpp
                 src/ui/UIC.hpp
                 #src/game/UIRunner.cpp
                 #src/game/UIRunner.hpp
		         src/ui/UICLayout.cpp
                 src/ui/UICLayout.hpp
                 src/ui/ListLayout.cpp
                 src/ui/ListLayout.hpp
		         src/ui/SingleLayout.cpp
		         src/ui/SingleLayout.hpp)

add_executable(OpenGL_Test ${SOURCE_FILES})
target_link_libraries(OpenGL_Test ${ALL_LIBS})

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res"
    COMMENT "Copy res directory to build tree"
    VERBATIM)
add_dependencies(OpenGL_Test copy_shaders)
