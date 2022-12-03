#pragma once
#include "pch.hpp"

using namespace std;

#ifndef __SHADERS__
#define __SHADERS__

static GLuint shaderID;
static GLuint vertexShader;
static GLuint fragmentShader;

char* filetobuf(const char* file);

void make_vertexShaders() {
	GLchar* vertexSource;

	vertexSource = filetobuf("vertex.glsl");

	cout << vertexSource << endl;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		printf("vertex 컴파일 실패\n");
	}
}

void make_fragmentShaders() {
	GLchar* fragmentSource;

	fragmentSource = filetobuf("fragment.glsl");

	cout << fragmentSource << endl;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		printf("fragment 컴파일 실패\n");
	}

}

void init_buffer() {

}

GLuint make_shaderProgram() {
	GLuint ShaderProgramID;
	ShaderProgramID = glCreateProgram();

	glAttachShader(ShaderProgramID, vertexShader);
	glAttachShader(ShaderProgramID, fragmentShader);

	glLinkProgram(ShaderProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLint result;

	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result);
	if (!result) {
		printf("shader 컴파일 실패\n");
		return false;

	}
	glUseProgram(ShaderProgramID);

	return ShaderProgramID;
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}

void ReadObj(FILE* objFile, float _vertex[], unsigned int _index[])
{
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[100];
	int vertexNum = 0;
	int faceNum = 0;
	memset(count, '\0', sizeof(count));

	while (!feof(objFile))
	{
		fscanf(objFile, "%s", count);

		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;

		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;

		memset(count, '\0', sizeof(count));
	}
	_vertex[1 * 3 + 0] = 1;

	int vertIndex = 0;
	int faceIndex = 0;
	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력

	fseek(objFile, 0, SEEK_SET);
	char bind[100];
	while (!feof(objFile))
	{
		memset(bind, '\0', sizeof(bind));

		fscanf(objFile, "%s", bind);

		if (bind[0] == 'v' && bind[1] == '\0')
		{
			fscanf(objFile, "%f %f %f", &_vertex[vertIndex * 3 + 0], &_vertex[vertIndex * 3 + 1], &_vertex[vertIndex * 3 + 2]);
			vertIndex++;
		}

		else if (bind[0] == 'f' && bind[1] == '\0')
		{
			float a, b, c;
			fscanf(objFile, "%f %f %f", &a, &b, &c);
			_index[faceIndex * 3 + 0] = a;
			_index[faceIndex * 3 + 1] = b;
			_index[faceIndex * 3 + 2] = c;
			faceIndex++;
		}

	}

	int a = 1;
}
#endif
