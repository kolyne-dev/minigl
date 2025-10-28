cmake_minimum_required(VERSION 4.0)
project(minigl LANGUAGES CXX)

function(export_headers TARGET HEADER_SOURCE_DIR HEADER_DEST_DIR)
    # Put all headers that are in the source directory into EXPORT_HEADERS variable
    file(GLOB_RECURSE EXPORT_HEADERS CONFIGURE_DEPENDS
            RELATIVE "${HEADER_SOURCE_DIR}"
            "${HEADER_SOURCE_DIR}/*.h"
    )
    # For each header that will be exported
    foreach(HEADER ${EXPORT_HEADERS})
        # Get the directory portion that needs to be created
        get_filename_component(HEADER_DIRECTORY "${HEADER}" DIRECTORY)
        # Create the directory
        add_custom_command(TARGET ${TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "${HEADER_DEST_DIR}/${HEADER_DIRECTORY}"
        )
        if (MSVC)
            # Make a hard link to the file
            add_custom_command(TARGET ${TARGET} POST_BUILD
                    COMMAND if not exist "${HEADER_DEST_DIR}/${HEADER}" \( mklink /h "${HEADER_DEST_DIR}/${HEADER}" "${HEADER_SOURCE_DIR}/${HEADER}" \)
            )
        else()
            # Make a symbolic link to the file
            add_custom_command(TARGET ${TARGET} POST_BUILD
                    COMMAND ln -sf "${HEADER_SOURCE_DIR}/${HEADER}" "${HEADER_DEST_DIR}/${HEADER}"
            )
        endif()
    endforeach(HEADER)
endfunction()

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

FetchContent_MakeAvailable(glm)

set(CMAKE_CXX_STANDARD 20)



add_library(${PROJECT_NAME} STATIC
        src/Window.cpp
        src/Shader.cpp
        src/VAO.cpp)
export_headers(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include/minigl)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad_gl_core_43 glm)



