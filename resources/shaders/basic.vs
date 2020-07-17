#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 normal;
out vec3 frag_pos;
out vec2 tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 object_colour;
uniform vec3 light_colour;

uniform vec3 light_pos;

void main()
{
   gl_Position =  projection * view * model * vec4(aPos, 1.0);

   frag_pos = vec3(model * vec4(aPos, 1.0));
   normal = aNormal;
   tex_coord = tex_coord;
}
