#include <iostream>

#include "main.h"
#include "ShaderProgram.h"
#include<cmath>
int main()
{
    if (!InitWindow())
    {
        return -1;
    };
    ShaderProgram myProgram("Assets/vertexShader.glsl","Assets/fragmentShader.glsl");

     float verticies[] = 
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,   -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(verticies),
        verticies,
        GL_STATIC_DRAW
    );
     glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6*sizeof(float),
        reinterpret_cast<void*>(0)
    );
  glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6*sizeof(float),
        reinterpret_cast<void*>(3*sizeof(float))
    );
     glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);


  int colorLocation = glGetUniformLocation(myProgram.getProgramID(), "uColor");

    int panLocation = glGetUniformLocation(myProgram.getProgramID(), "uPan");
    int zoomLocation = glGetUniformLocation(myProgram.getProgramID(), "uZoom");

    while (!glfwWindowShouldClose(Window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

            float time = static_cast<float>(glfwGetTime());
            float green = (std::sin(time) + 1.0f) / 2.0f;
            float red = (std::cos(time) + 1.0f) / 2.5f;
            float blue = (std::sin(time) + 1.0f) / 1.5f;
                      glUniform4f(colorLocation, red, green,blue, 1.0f);

            glUniform1f(zoomLocation, 1.0);

        myProgram.Use();
            glBindVertexArray(VAO);
               glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
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