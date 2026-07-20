#pragma once
void CheckShaderCompile(unsigned int shader);
void CheckProgramLink(unsigned int program);
void InitWindow();
float panX = 0.0f;
float panY = 0.0f;
float pressPanX = 0.0f;
float pressPanY = 0.0f;
float zoom = 1.0f;
float mouseX = 0.0f;
bool isPressed;
float FirstX, FirstY;
float wHeight, wWidth;

float mouseY = 0.0f;
static const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
out vec3 rColor;
uniform vec2 uPan;
uniform float uZoom;


void main()
{
    vec2 pos = aPosition.xy * uZoom + uPan;

    gl_Position = vec4(pos, aPosition.z, 1.0);
    rColor = aColor;
}
)";

static const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;
in vec3 rColor;
uniform vec4 uColor;

void main()
{
    FragColor = uColor * vec4(rColor, 1.0);
}
)";



