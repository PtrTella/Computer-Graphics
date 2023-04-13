#version 150

in  vec3 in_Position;
uniform mat4 Rotx;
uniform mat4 Roty;
uniform mat4 Rotz;
in vec3 in_Color;
out	vec4 frag_color;

void main(void)
{
	frag_color = vec4(in_Color, 0.1f);
	gl_Position = vec4(in_Position, 1.0) * (Rotx * Rotz);
}
