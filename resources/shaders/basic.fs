#version 330 core

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coord;

out vec4 FragColor;

uniform vec3 object_colour;
uniform vec3 light_colour;
uniform vec3 light_pos;
uniform vec3 view_pos;

uniform sampler2D floor_texture;
uniform bool is_floor;

void main()
{
  float ambient_strength = 0.1;
  vec3 ambient = ambient_strength * light_colour;

  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(light_pos - frag_pos);
  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * light_colour;

  float specular_strength = 0.5;
  vec3 view_dir = normalize(view_pos - frag_pos);
  vec3 reflect_dir = reflect(-light_dir, norm);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
  vec3 specular = specular_strength * spec * light_colour;

  vec3 result;
  if (!is_floor) {
    result= (diffuse + ambient + specular) * object_colour;
  }
  else {
    vec3 obj_tex_colour = texture(floor_texture, tex_coord).xyz;
    result = (diffuse + ambient + specular) * obj_tex_colour;
  }

  FragColor = vec4(result, 1.0);
}
