cmake_minimum_required(VERSION 4.0)
project(minigl LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        73db193f853e2ee079bf3ca8a64aa2eaf6459043 #v2.0.8
        GIT_PROGRESS   TRUE
        SOURCE_SUBDIR  cmake
)

FetchContent_MakeAvailable(glad)

glad_add_library(glad_gl_core_43 STATIC REPRODUCIBLE LOADER API gl:core=4.3)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/icaven/glm.git
        GIT_TAG 	master
)

set(GLM_ENABLE_CXX_20 TRUE)

FetchContent_MakeAvailable(glm)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
        src/Window.cpp
        src/Shader.cpp
        src/VAO.cpp
        src/Texture.cpp
        src/Transformable.cpp
        src/Camera.cpp
        src/Cube.cpp
        include/minigl/Cube.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad_gl_core_43 glm)



