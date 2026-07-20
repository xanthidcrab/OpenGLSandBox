cmake_minimum_required(VERSION 3.15)
project(OpenGL_Project VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

 
add_subdirectory(libs/glfw-3.4 EXCLUDE_FROM_ALL)
 
add_library(glad STATIC 
    libs/glad/src/glad.c
)
target_include_directories(glad PUBLIC 
    libs/glad/include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    include/main.h    # Klasör yolunu belirterek buraya ekleyebilirsiniz
)

# Klasörün aranacağını yine de belirtiyoruz (Kodun derlenebilmesi için şart)
target_include_directories(${PROJECT_NAME} PRIVATE 
    include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    opengl32
    glfw
    glad
)