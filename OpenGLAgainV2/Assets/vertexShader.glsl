#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
out vec3 rColor ;
uniform vec2 uPan;
uniform float uZoom;

void main()
{
    vec2 pos = aPosition.xy * uZoom + uPan;
    gl_Position = vec4(pos, aPosition.z, 1.0);
    rColor = aColor;
}