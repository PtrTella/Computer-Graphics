#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec3 in_Color;

uniform mat4 Rotx;
uniform mat4 Roty;
uniform mat4 Rotz;

out	vec3 frag_color;

void main(void)
{
	frag_color = vec3(0.2, 0.3, 0.7) + in_Normal;
	gl_Position = vec4(in_Position, 1.0) * (Rotx * Rotz);
}
