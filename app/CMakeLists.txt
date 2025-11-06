cmake_minimum_required(VERSION 3.30)
project(app)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE app_source ${PROJECT_SOURCE_DIR}/src *.cpp)

add_executable(${PROJECT_NAME} ${app_source})
target_link_libraries(${PROJECT_NAME} PUBLIC minigl)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:minigl,SOURCE_DIR>/shader"
        "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/shader"
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:app,SOURCE_DIR>/assets"
        "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/assets"
)