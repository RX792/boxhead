#version 450
in vec3 a_Position;
in vec4 a_Color;

uniform float u_Time = 0.0f;

out vec2 v_TexCoords;

void main()
{
	gl_Position = vec4(a_Position, 1.0f);
	v_TexCoords = vec2(a_Position + 1.0f) * 0.5f;
}
