cmake_minimum_required(VERSION 3.20)
project(OpenGLBatchStyleCodingExample LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.0
)
FetchContent_MakeAvailable(imgui)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw-3.4 EXCLUDE_FROM_ALL)

add_library(glad STATIC
    libs/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    libs/glad/include
)

# ImGui ships no CMakeLists.txt for the library itself (only for its
# examples), so we list its sources directly. imgui_impl_opengl3 is told to
# use our already-loaded glad rather than picking its own GL loader.
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui PUBLIC glfw glad)

# Engine: the actual codebase being taught, one class at a time. Every
# compiled (non-header-only) class's .cpp is added here as it's built.
add_library(Engine STATIC
    src/Geometry/Mesh.cpp
    src/Tessellation/Tessellator.cpp
    src/Scene/Scene.cpp
    src/Buffers/BufferLayout.cpp
    src/Buffers/VertexBuffer.cpp
    src/Buffers/VertexArray.cpp
    src/Shaders/ShaderProgram.cpp
    src/Renderer/RenderCommand.cpp
    src/Renderer/RenderState.cpp
    src/Renderer/Renderer.cpp
    src/Batch/Batch.cpp
    src/Camera/Camera2D.cpp
    src/Core/Window.cpp
    src/Core/Application.cpp
)
target_include_directories(Engine PUBLIC src)
target_link_libraries(Engine PUBLIC
    glm::glm
    glad
    glfw
    opengl32
    imgui
)

# Sandbox: the running executable. Examples/ lives at the repo root (not
# under src/) since lessons aren't part of the reusable Engine library.
add_executable(Sandbox
    src/main.cpp
    Examples/01_SceneEditor/SceneEditorExample.cpp
)
target_include_directories(Sandbox PRIVATE Examples)
target_link_libraries(Sandbox PRIVATE Engine)

add_custom_command(
    TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
            "$<TARGET_FILE_DIR:Sandbox>/assets"
    COMMENT "Copying asset directory to build output..."
)
