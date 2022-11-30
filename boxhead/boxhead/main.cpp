#include "pch.hpp"
#include "Main.hpp"

constexpr int client_w{ 800 }, client_h{ 600 };
Framework MySystem{};

std::random_device seed{};
std::uniform_real_distribution<float> distr_color{ 0.0f, 1.0f };
std::default_random_engine random_engine{ seed() };

constexpr std::chrono::system_clock performance_clock{};
std::chrono::system_clock::time_point elapsed_timer{};
float elapsed_time{};

int main(int argc, char** argv)
{
	ogl::Awake(argc, argv);

	try
	{
		ogl::Ready("Shooter", client_w, client_h, 100, 100);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	ogl::SetRenderer(Render);
	ogl::SetViewportUpdater(UpdateView);
	ogl::SetKeyboardMethod(UpdateKeyboard);
	ogl::SetSpecialKeyboardMethod(UpdateSpecialKeyboard);
	ogl::SetMouseMethod(UpdateMouse);
	ogl::SetMouseMoverMethod(UpdateMouseMotion);
	ogl::SetTimer(UpdateFrames, 10);
	ogl::TurnOnOption(GL_DEPTH_TEST);
	ogl::TurnOnOption(GL_LINE_SMOOTH);
	ogl::TurnOnOption(GL_CULL_FACE);

	ogl::background_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	elapsed_timer = performance_clock.now();

	make_vertexShaders();
	make_fragmentShaders();
	shaderID = make_shaderProgram();

	try
	{
		MySystem.Awake();

		MySystem.Start();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	ogl::Start();
}

GLvoid Render(GLvoid)
{}

GLvoid drawScene()
{

	GLfloat rColor, gColor, bColor;

	rColor = gColor = bColor = 0.0;

	glClearColor(rColor, gColor, bColor, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다



	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid UpdateFrames(int value)
{
	using namespace std::chrono;
	const auto time_now = performance_clock.now();
	const auto time_between = time_now - elapsed_timer;
	const auto mill = duration_cast<milliseconds>(time_between);
	elapsed_time = static_cast<float>(mill.count()) / 1000.0f;

	MySystem.Update(elapsed_time);

	ogl::Refresh();
	ogl::SetTimer(10);

	elapsed_timer = time_now;
}

GLvoid UpdateView(const int w, const int h)
{
	ogl::gl_width = w;
	ogl::gl_height = h;

	glViewport(0, 0, w, h);
}

GLvoid UpdateKeyboard(const unsigned char key, const int x, const int y)
{
	//const auto movement = 10.0f * elapsed_time;
	const auto camera_movement = 20.0f * elapsed_time;

	switch (key)
	{
		case 'x':
		case 'X':
		{
		}
		break;

		case 'y':
		case 'Y':
		{
		}
		break;

		case 'a':
		case 'A':
		{
		}
		break;

		case 'd':
		case 'D':
		{
		}
		break;

		case 'w':
		case 'W':
		{
		}
		break;

		case 's':
		case 'S':
		{
		}
		break;

		case 'q':
		case 'Q':
		{
		}
		break;

		case 'e':
		case 'E':
		{
		}
		break;

		case 'c':
		case 'C':
		{
		}
		break;

		case 'r':
		case 'R':
		{
		}
		break;

		case 'h':
		case 'H':
		{
		}
		break;
	}

	ogl::Refresh();
}

GLvoid UpdateSpecialKeyboard(const int key, const int x, const int y)
{
	const auto movement = 20.0f * elapsed_time;
	const auto rotation = 15.0f * elapsed_time;

	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			
		}
		break;

		case GLUT_KEY_RIGHT:
		{
			
		}
		break;

		case GLUT_KEY_UP:
		{
			
		}
		break;

		case GLUT_KEY_DOWN:
		{
			
		}
		break;

		case GLUT_KEY_F12:
		{
			std::quick_exit(0);
		}
		break;
	}

	ogl::Refresh();
}

GLvoid UpdateMouse(const int button, const int state, const int sx, const int sy)
{
	if (ogl::IsMouseClicked(state))
	{
		if (ogl::IsLeftMouseButton(button))
		{
			ogl::background_color.r = RandomizeColour() * 0.5f;
			ogl::background_color.g = RandomizeColour() * 0.5f;
			ogl::background_color.b = RandomizeColour() * 0.5f;
		}
	}

	ogl::Refresh();
}

GLvoid UpdateMouseMotion(const int mx, const int my)
{
	ogl::Refresh();
}

float RandomizeColour()
{
	return distr_color(random_engine);
}
