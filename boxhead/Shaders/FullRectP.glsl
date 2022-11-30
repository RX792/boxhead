#version 450
layout(location=0) out vec4 FragColor;

in vec2 v_TexCoords;

uniform float u_Time = 0.0f;

const float PI = 3.141592f;

// ���� ���̴��� ���� ���̴� ������ ������
// ������ ������ ���� ���� ���� ������ ���� ���̴��� Ư���� ���� ����� ��Ÿ����.
// �׷��� ���� ���̴��� ���� Ƚ���� ���� ������ ����ȭ�� �� ����.
// ���� ���̴��� ��� ���� ���� ������ �ؾ� �Ѵ�.
// ���� ���̴��� �ε巴��.
void main()
{
	// ����!!!!!!!!!!!!!
	// y���� �� ���ؾ� �Ѵ�!!!!!
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
