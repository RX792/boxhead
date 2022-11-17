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

class Box {

public:
	float x, y, z;
	float rx, ry, rz;
	float mx, my, mz;
	float sx, sy, sz;

	float size = 0.3f;

	GLuint VAO;
	GLuint VBO_pos[2];
	GLuint EBO;

	float vertex[3 * 8];
	float colors[3 * 8] = { 0, };
	unsigned int index[3 * 12];

	



	Box(float _x, float _y, float _z) {

		set_random_color();
		
		x = y = z = 0;
		rx = ry = rz = 0;
		sx = sy = sz = 1.0;

		mx = _x;
		my = _y;
		mz = _z;

		FILE* file = fopen("cube.txt", "r");
		ReadObj(file, vertex, index);




		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		glGenBuffers(1, &VBO_pos[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);


		

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STREAM_DRAW);

		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

	}
	void set_random_color() {
		for (int i = 0; i < 3 * 8; ++i) {
			colors[i] = uid(dre) / 1000.0f;
		}

		glGenBuffers(1, &VBO_pos[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}

	void set_color(float r, float g, float b) {
		for (int i = 0; i < 8; ++i) {
			colors[i * 3] = r;
			colors[i * 3 + 1] = g;
			colors[i * 3 + 2] = b;
		}

		glGenBuffers(1, &VBO_pos[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_pos[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STREAM_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}

	void set_size(float x, float y, float z) {
		sx = x;
		sy = y;
		sz = z;
	}

	void add_rotate_radian(int x, int y, int z) {
		rx += x;
		ry += y;
		rz += z;
	}

	void add_translate_post(float _x, float _y, float _z) {
		x += _x;
		y += _y;
		z += _z;
	}

	void reset_to_init() {
		x = y = z = 0;
		rx = ry = rz = 0;
	}

	void draw() {
		//glEnable(GL_DEPTH_TEST);
		glBindVertexArray(VAO);

		glm::mat4 model = glm::mat4(1.0);

		glm::mat4 RTx = glm::mat4(1.0);
		glm::mat4 RTy = glm::mat4(1.0);
		glm::mat4 RTz = glm::mat4(1.0);
		glm::mat4 Scale = glm::mat4(1.0);
		glm::mat4 translate = glm::mat4(1.0);
		glm::mat4 translate_post_init = glm::mat4(1.0);



		RTx = glm::rotate(RTx, glm::radians(rx), glm::vec3(1.0, 0.0, 0.0));
		RTy = glm::rotate(RTy, glm::radians(ry), glm::vec3(0.0, 1.0, 0.0));
		RTz = glm::rotate(RTx, glm::radians(rz), glm::vec3(0.0, 0.0, 1.0));
		Scale = glm::scale(Scale, glm::vec3(sx, sy, sz));
		translate = glm::translate(translate, glm::vec3(mx, my, mz));
		translate_post_init = glm::translate(translate_post_init, glm::vec3(x, y, z));


		model = translate_post_init * translate * RTz * RTy * RTx  * Scale;

		unsigned int modelLocation = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		
		glEnable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);
		
	}
};