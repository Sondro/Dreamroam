#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//Out:
layout (location = 0) out vec4 fColor;

void main() {
    fColor = vec4(1.0,0.0,0.0,1.0);
}
