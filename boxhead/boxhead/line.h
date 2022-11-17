#pragma once
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include "misc.h"
#include "shader.h"

class Line {

public:
	GLfloat p[9] =
	{
		-1,0,0,
		1,0,0,
		1,1,1
	};

	GLfloat p_c[9] =
	{
		1,0,0,
		1,0,0,
		1,0,0
	};

	GLuint VAO;
	GLuint VBO[2];
	float rx, ry, rz;

	Line()
	{
		rx = ry = rz = 0;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		glGenBuffers(1, &VBO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), p, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


		glGenBuffers(1, &VBO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), p_c, GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	void set_rotate_radian(float x, float y, float z)
	{
		rx = x;
		ry = y;
		rz = z;
	}

	void draw()
	{
		//glEnable(GL_DEPTH_TEST);
		glBindVertexArray(VAO);

		glm::mat4 model = glm::mat4(1.0);

		glm::mat4 RTx = glm::mat4(1.0);
		glm::mat4 RTy = glm::mat4(1.0);
		glm::mat4 RTz = glm::mat4(1.0);
		glm::mat4 Scale = glm::mat4(1.0);


		RTx = glm::rotate(RTx, glm::radians(rx), glm::vec3(1.0, 0.0, 0.0));
		RTy = glm::rotate(RTy, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
		RTz = glm::rotate(RTx, glm::radians(rz), glm::vec3(0.0, 0.0, 1.0));

		Scale = glm::scale(Scale, glm::vec3(1.0f, 1.0f, 1.0f));

		model = RTz * RTy * RTx * Scale;

		unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_LINE_LOOP, 0, 2);

	}
};