cmake_minimum_required(VERSION 3.15)
project(OpenGLAgainV2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(
    libs/glfw-3.4 EXCLUDE_FROM_ALL
)
add_library(
    glad STATIC
    libs/glad/src/glad.c
)
target_include_directories(
    glad PUBLIC
    libs/glad/include
)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/ShaderProgram.cpp
    src/File.cpp
    include/main.h
    include/File.h
    include/ShaderProgram.h
)
target_include_directories(${PROJECT_NAME} PRIVATE
    include
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    opengl32
    glfw
    glad

)
add_custom_command(
    TARGET OpenGLAgainV2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
            "$<TARGET_FILE_DIR:OpenGLAgainV2>/assets"
    COMMENT "Asset dizini build klasorune kopyalaniyor..."
)