
--VERT--

#version 330 core

layout(location = 0) in vec2 position;
layout (location = 1) in vec2 scale_v;
uniform float cx;
uniform float cz;
uniform float cd;

uniform float rotate;
out vec2 scale;
void main()
{
    mat3 rot = mat3(
    cos(rotate), sin(rotate), 0,
    -sin(rotate), cos(rotate),     0,
    0, 0, 1
    );
    mat3 rot2 = mat3(
    cos(cd), 0, sin(cd),
    0,       1,     0,
    -sin(cd), 0, cos(cd)
    );
    vec3 transform =  rot2*(rot*(vec3(position.x, position.y, 0))+vec3(cx,0,cz));
    gl_Position = vec4(transform.xy,transform.z/1000, transform.z);
    scale = scale_v;
    
}

--GMTR--

#version 330 core 

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;
in vec2 scale[];

out vec2 texture_position;
void main(){

    texture_position = vec2(0, 1);
    gl_Position = vec4(gl_in[0].gl_Position.xy + vec2(-scale[0].x, -scale[0].y), 0, 1);
    EmitVertex();
    texture_position = vec2(1, 1);
    gl_Position = vec4(gl_in[0].gl_Position.xy + vec2(scale[0].x, -scale[0].y), 0, 1);
    EmitVertex();
    texture_position = vec2(0, 0);
    gl_Position = vec4(gl_in[0].gl_Position.xy + vec2(-scale[0].x, scale[0].y), 0, 1);
    EmitVertex();
    texture_position = vec2(1, 0);
    gl_Position = vec4(gl_in[0].gl_Position.xy + vec2(scale[0].x, scale[0].y), 0, 1);
    EmitVertex();
    EndPrimitive();
 
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

