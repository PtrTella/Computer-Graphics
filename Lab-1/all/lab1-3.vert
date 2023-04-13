#version 150

in  vec3 in_Position;
uniform	vec4 in_frag_color;
uniform mat4 myMatrix;
out	vec4 frag_color;

void main(void)
{
	frag_color = in_frag_color;
	gl_Position = vec4(in_Position, 1.0)*myMatrix;
}
