
--VERT--

#version 330 core

layout(location = 0) in vec2 position;
layout (location = 1) in vec2 texture_position_v;
uniform float cx;
uniform float cz;
uniform float cd;
uniform float rotate;
out vec2 texture_position;

void main()
{
    mat3 rot = mat3(
    cos(rotate), 0, sin(rotate),
    0,       1,     0,
    -sin(rotate), 0, cos(rotate)
    );
    mat3 rot2 = mat3(
    cos(cd), 0, sin(cd),
    0,       1,     0,
    -sin(cd), 0, cos(cd)
    );
    vec3 transform =  rot2*(rot*(vec3(position.xy, 0))-vec3(cx,0,cz-1));
    gl_Position = vec4(transform.xy,transform.z/1000, transform.z);
    texture_position = texture_position_v;
    
}

--FRAG--

#version 330 core

layout(location = 0) out vec4 color;
uniform sampler2D tex; 
in vec2 texture_position;

void main()
{
    color = texture(tex, texture_position);

}
