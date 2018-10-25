#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCords;

out vec2 pass_textureCords;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
    pass_textureCords = textureCords;
}