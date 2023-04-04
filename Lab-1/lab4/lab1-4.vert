#version 150

in  vec3 in_Position;
uniform mat4 myMatrix;
in vec3 in_Color;
out	vec4 frag_color;

void main(void)
{
	frag_color = vec4(in_Color, 0.8f);
	gl_Position = vec4(in_Position, 1.0);//*myMatrix;
}
