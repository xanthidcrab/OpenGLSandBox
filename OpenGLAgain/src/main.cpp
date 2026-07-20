#include <iostream>
#include "main.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    wWidth = width;
    wHeight = height;
    std::cout << "Resize: "
              << width << " x "
              << height << std::endl;
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    mouseX = static_cast<float>(xpos);
    mouseY = static_cast<float>(ypos);
    if (isPressed)
    {
        const float halfWidth = wWidth / 2;
        const float halfHeight = wHeight / 2;
        panX = pressPanX + (mouseX - FirstX) / halfWidth;
        panY = pressPanY - (mouseY - FirstY) / halfHeight;
    }

}
void ScrollCallback(GLFWwindow* window,
                    double xoffset,
                    double yoffset)
{
    zoom += static_cast<float>(yoffset) * 0.1f;
    if (zoom < 0.1f)
    {
        zoom = 0.1f;
    }
}
void MouseButtonCallback(GLFWwindow* window,
                         int button,
                         int action,
                         int mods)
{
    if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if (action == GLFW_PRESS)
        {
            isPressed = true;
            FirstX = mouseX;
            FirstY = mouseY;
            pressPanX = panX;
            pressPanY = panY;
            std::cout<< "isspressed : TRUE" << std::endl;
        }
        else if (action == GLFW_RELEASE)
        {
            isPressed = false;
            std::cout<< "isspressed : FALSE" << std::endl;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT &&
        action == GLFW_RELEASE)
    {
        std::cout << "Left Release\n";
    }
}
int main()
{

    InitWindow();
    GLFWwindow* window = glfwCreateWindow(800,600, "opengl",nullptr,nullptr);
    wHeight = 600;
    wWidth = 800;
    if (window == nullptr)
    {
        std::cout << "THERE IS A PROBLEM OCCURED WHEN WINDOW INITILIZITION"<< std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    if (!gladLoadGLLoader(
        reinterpret_cast<GLADloadproc>(glfwGetProcAddress)
    ))
    {
        std::cout << "Glad baslatilamadi" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0,0,800,600);
    
    //Vertex shader oluşturuluyor
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Shader source atanıyor 
    // 1. değer unsigned int(buna shader numarası diyebiliriz) 
    // 2. değer sayısı count değeri
    // 3. *char yani shader sourcesinin string değeri 
    // 4. GLint olarak uzunluk değeri
    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        nullptr
    );
 
    //Shaderin Compile edilmesi.
    glCompileShader(vertexShader);
    //Compile result check.
    CheckShaderCompile(vertexShader);

    //Fragment shaderin oluşturulması 
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //fragment shader sourcenin atanması...
    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        nullptr
    );

    glCompileShader(fragmentShader);
    CheckShaderCompile(fragmentShader);

    //Shader programının oluşturulması
    unsigned int shaderProgram = glCreateProgram();

    //bu programa vertex ve fragment shaderi bağlama.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    CheckProgramLink(shaderProgram);
    //program oluşturulduktan sonra shaderler silinir zaten artık elimizde program var durmasın memoryde
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    float verticies[] = 
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,   -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    float innerTriangleLines[] =
        {
            // A-B
            -0.20f, -0.15f, 0.0f,
            0.20f, -0.15f, 0.0f,

            // B-C
            0.20f, -0.15f, 0.0f,
            0.00f,  0.20f, 0.0f,

            // C-A
            0.00f,  0.20f, 0.0f,
            -0.20f, -0.15f, 0.0f
        };
 
    //VAO ve VBO oluşturmak

    unsigned int VAO, VBO, lineVAO, lineVBO;

    //VAO ve VBO oluşturmak
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&lineVAO);
    glGenBuffers(1,&lineVBO);

    // --- Dış üçgen (dolu, renkli) ---
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //burada noktalarımız atanıyor.
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

   // --- İç üçgen (sadece çizgilerle) ---
   glBindVertexArray(lineVAO);
   glBindBuffer(GL_ARRAY_BUFFER, lineVBO);

   glBufferData(
       GL_ARRAY_BUFFER,
       sizeof(innerTriangleLines),
       innerTriangleLines,
       GL_STATIC_DRAW
   );

   glVertexAttribPointer(
       0,
       3,
       GL_FLOAT,
       GL_FALSE,
       3*sizeof(float),
       reinterpret_cast<void*>(0)
   );
   glEnableVertexAttribArray(0);

   // location 1 (renk) için per-vertex veri yok; sabit bir renk kullanıyoruz.
   glVertexAttrib3f(1, 1.0f, 1.0f, 1.0f);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);

   int colorLocation = glGetUniformLocation(shaderProgram, "uColor");

    int panLocation = glGetUniformLocation(shaderProgram, "uPan");
    int zoomLocation = glGetUniformLocation(shaderProgram, "uZoom");
    while (!glfwWindowShouldClose(window))
    {
       glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time = static_cast<float>(glfwGetTime());
        float green =
            (std::sin(time) + 1.0f) / 2.0f;
       float r = mouseX / 800.0f;
    float g = mouseY / 600.0f;
    float b = mouseY / 300.0f;
        glUseProgram(shaderProgram);
 
          glUniform4f(colorLocation, r, g,b, 1.0f);
        glUniform2f(panLocation, panX, panY);
        glUniform1f(zoomLocation, zoom);

        glBindVertexArray(VAO);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );

        glBindVertexArray(lineVAO);
        glDrawArrays(GL_LINES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &lineVAO);
    glDeleteBuffers(1, &lineVBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    


    return 0;
}

void InitWindow()
{
    if (!glfwInit())
    {
        std::cout << "GLFW INITIALITION FAILED" << std::endl;
        
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    
}

void CheckShaderCompile(unsigned int shader)
{
    int success;
    char infolog[1024];
    glGetShaderiv(shader,GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(
            shader,
            sizeof(infolog),
            nullptr,
            infolog
        );
        std::cout << "Shader Compile Hatası:" << infolog << std::endl;
    }


}

void CheckProgramLink(unsigned int program)
{
    int success;
    char infolog[1024];
    glGetProgramiv(program,GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(
            program,
            sizeof(infolog),
            nullptr,
            infolog
        );
        std::cout << "Program Link Hatası:" << infolog << std::endl;
    }


}
