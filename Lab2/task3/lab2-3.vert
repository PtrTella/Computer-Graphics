#version 150

in 	vec3 in_Normal;
in  vec3 in_Position;
in vec2 inTexCoord;
uniform mat4 uniTransform;
uniform float uniTime;
uniform mat4 uniProjection;
uniform mat4 uniTotal;
out vec3 frag_color;
out vec2 texCoord;

void main(void)
{
	gl_Position = uniProjection * uniTotal * uniTransform * vec4(in_Position, 1.0);
	//out_color = vec3(0.0f,0.5f,0.0f);
	frag_color = vec3(vec3(0.5f,1.0f,0.8f)- in_Normal);
	texCoord = inTexCoord;
}
