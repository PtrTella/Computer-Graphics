#version 150

in 	vec3 frag_color;
out vec4 out_Color;

void main(void)
{
	out_Color = vec4(frag_color, 0.8f);
}
