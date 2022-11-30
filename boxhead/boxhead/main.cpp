#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "misc.h"
#include "shader.h"
#include "input.h"
#include "box.h"
#include "zombie.h"
#include "line.h"

#define W 800
#define H 600


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunc(int a);
void gmf(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
void SpecialInput(int key, int x, int y);


float _x, _y, _z;

Zombie* zombie;
Line* xyz_line[3];
Box* plain;


glm::vec3 cameraPos ; //--- 카메라 위치
glm::vec3 cameraDirection; //--- 카메라 바라보는 방향
glm::vec3 cameraUp;

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름)




	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	make_vertexShaders();
	make_fragmentShaders();
	shaderID = make_shaderProgram();
	
	cameraPos = glm::vec3(0.0f, 3.0f, 3.0f); //--- 카메라 위치
	cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향


	//init_buffer();
	plain = new Box(0,0,0);
	plain->set_size(2, -0.1, 2);

	zombie = new Zombie();


	for (int i = 0; i < 3; ++i)
		xyz_line[i] = new Line;

	xyz_line[1]->set_rotate_radian(0, 0, 90);
	xyz_line[2]->set_rotate_radian(0, 90, 0);

	glUseProgram(shaderID);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(gmf);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialInput);
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutTimerFunc(1000, TimerFunc, 1);
	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {

	GLfloat rColor, gColor, bColor;

	rColor = gColor = bColor = 0.0;

	glClearColor(rColor, gColor, bColor, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(shaderID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	//
	plain->draw();
	for (int i = 0; i < 3; ++i)
		xyz_line[i]->draw();

	zombie->draw();

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void TimerFunc(int a) {

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunc, 1);
}

void gmf(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}

	glutPostRedisplay();
}

void camera_rotate() {
	//glm::vec4 temp = {cameraPos, 0.0};
	//glm::mat4 rotate = glm::mat4(1.0);
	//rotate = glm::rotate(rotate, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));
	//cameraPos -= temp;
	//cameraPos = rotate * cameraPos;
}

GLvoid Keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'z':
		cameraPos += glm::vec3(0.0f, 0.0f, 0.1f);
		cameraDirection += glm::vec3(0.0f, 0.0f, 0.1f);
		break;
	case 'Z':
		cameraPos -= glm::vec3(0.0f, 0.0f, 0.1f);
		cameraDirection -= glm::vec3(0.0f, 0.0f, 0.1f);
		break;
	case 'x':
		cameraPos += glm::vec3(0.1f, 0.0f, 0.0f);
		cameraDirection += glm::vec3(0.1f, 0.0f, 0.0f);
		break;
	case 'X':
		cameraPos -= glm::vec3(0.1f, 0.0f, 0.0f);
		cameraDirection -= glm::vec3(0.1f, 0.0f, 0.0f);
		break;

	case 'y':
		camera_rotate();
		break;
	case 'Y':
		cameraPos -= glm::vec3(0.1f, 0.0f, 0.0f);
		cameraDirection -= glm::vec3(0.1f, 0.0f, 0.0f);
		break;
	}

	glutPostRedisplay();
}


void SpecialInput(int key, int x, int y){
	switch (key)
	{
	case GLUT_KEY_UP:

		break;

	case GLUT_KEY_DOWN:
		
		break;

	case GLUT_KEY_RIGHT:
		
		break;

	case GLUT_KEY_LEFT:
		
		break;
	}
}