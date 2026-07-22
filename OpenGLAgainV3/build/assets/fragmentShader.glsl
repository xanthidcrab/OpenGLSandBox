#version 330 core

out vec4 FragColor;
in vec3 rColor;
uniform vec4 uColor;

void main(){
    FragColor = uColor * vec4(rColor, 1.0);
}