#include <iostream>

#include "main.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include<cmath>
int main()
{
    if (!InitWindow())
    {
        return -1;
    }
    ShaderProgram myProgram("assets/vertexShader.glsl","assets/fragmentShader.glsl");
    float verticies[] = 
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,   -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    VAO vao;
    VBO VBO(verticies,sizeof(verticies));

    // 2. Attribute'ları bağla
    // Pozisyon (Location = 0)
    vao.LinkAttribute(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // Renk (Location = 1)
    vao.LinkAttribute(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));    
    int zoomLocation = glGetUniformLocation(myProgram, "uZoom");

    while (!glfwWindowShouldClose(Window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float time = static_cast<float>(glfwGetTime());
        float green = (std::sin(time) + 1.0f) / 2.0f;
        float red = (std::cos(time) + 1.0f) / 2.5f;
        float blue = (std::sin(time) + 1.0f) / 1.5f;

        myProgram.Use();
        myProgram.setVec4("uColor",green,red,blue,1.0f);
        glUniform1f(zoomLocation, 1.0);

        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(Window);
        glfwPollEvents();
    };
    



    return 0;
}

bool InitWindow()
{
    if (!glfwInit())
    {
        std::cout << "Something happend when initializing GLFW" << std::endl;
        return false;
    }
    Window = glfwCreateWindow(800,600, "OpenGLAgainV2",nullptr,nullptr);
    if (Window == nullptr)
    {
        std::cout << "Something happend when initializing Window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(Window);

    if (!gladLoadGLLoader(
        reinterpret_cast<GLADloadproc>(glfwGetProcAddress)
    ))
    {
                std::cout << "Something happend when initializing GLAD" << std::endl;
        return false;
    }
    return true;


}