cmake_minimum_required(VERSION 4.0)
project(app)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC minigl)

add_custom_command(
        TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:minigl,SOURCE_DIR>/shader"
        "$<TARGET_PROPERTY:app,BINARY_DIR>/shader"
)