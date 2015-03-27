add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Load in GLFW

add_subdirectory(glfw)

include_directories(
    glfw/include/GLFW/
    glew/include/
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OPENGL_LIBRARY
        ${OPENGL_LIBRARY}
        -lGL -lGLU -lXrandr -lXext -lX11 -lrt
        ${CMAKE_DL_LIBS}
        ${GLFW_LIBRARIES}
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
        ${OPENGL_LIBRARY}
        ${CMAKE_DL_LIBS}
        ${GLFW_LIBRARIES}
    )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Load in GLEW

set(GLEW_SOURCE glew/src/glew.c)
set(GLEW_HEADERS)

add_library(
    GLEW_1120
    ${GLEW_SOURCE}
    ${GLEW_INCLUDE}
)

target_link_libraries(GLEW_1120
    ${OPENGL_LIBRARY}
    ${EXTRA_LIBS}
)

# Load in SOIL

set(SOIL_SOURCE
    SOIL/SOIL/image_DXT.c
    SOIL/SOIL/image_DXT.h
    SOIL/SOIL/image_helper.c
    SOIL/SOIL/image_helper.h
    SOIL/SOIL/SOIL.c
    SOIL/SOIL/SOIL.h
    SOIL/SOIL/stb_image_aug.c
    SOIL/SOIL/stb_image_aug.h
    SOIL/SOIL/stbi_DDS_aug.h
    SOIL/SOIL/stbi_DDS_aug_c.h
    SOIL/SOIL/original/stb_image-1.09.c
    SOIL/SOIL/original/stb_image-1.16.c
)

add_library(
    SOIL
    ${SOIL_SOURCE}
)