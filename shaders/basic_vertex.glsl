#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec2 u_UVScale;
uniform vec2 u_UVOffset;

void main()
{
    // The View should be added between projection and model when it will be introduced.
    // The order of multiplication is important!
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
    v_TexCoord = a_TexCoord * u_UVScale + u_UVOffset ;
}
