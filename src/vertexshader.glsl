#version 330 core

layout(location = 0) in vec2 position;
layout (location = 1) in vec2 texture_position_v;
out vec2 texture_position;

void main()
{
    gl_Position = vec4(position.xy, 0, 1);
    texture_position = texture_position_v;
    
}
