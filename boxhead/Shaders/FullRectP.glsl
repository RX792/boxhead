#version 450
layout(location=0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform float u_Time = 0.0f;

const float PI = 3.141592f;

// 정점 쉐이더와 조각 쉐이더 구현의 차이점
// 정점을 무한히 만들 수는 없기 때문에 정점 쉐이더는 특유의 각진 모양이 나타난다.
// 그러나 정점 쉐이더는 연산 횟수가 적기 때문에 최적화가 더 좋다.
// 조각 쉐이더는 모든 점에 대해 연산을 해야 한다.
// 조각 쉐이더는 부드럽다.
void main()
{
	// 시험!!!!!!!!!!!!!
	// y값도 잘 구해야 한다!!!!!
	int polar_count = 4;

	float height = sin(u_Time + polar_count * v_TexCoords.x * 2.0f * PI);

	float width = 0.05;
	float next = v_TexCoords.y * 2.0f - 1.0f;

	if (next < height && height < next + width)
	{
		FragColor = vec4(v_TexCoords, height, 1.0f);
	}
	else
	{
		FragColor = vec4(v_TexCoords * 0.1f, 0.0f, 1.0f);
	}
}
