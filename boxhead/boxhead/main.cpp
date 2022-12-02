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
{
	MySystem.PrepareRendering();
	MySystem.Render();
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
	const auto fw = static_cast<float>(w);
	const auto fh = static_cast<float>(h);
	const auto ratio = static_cast<float>(h) / static_cast<float>(w);

	float res_w, res_h;
	if (h < w)
	{
		// 높이 기준
		res_w = fh * constants::CLIENT_RATIO;
		res_h = fh;
	}
	else
	{
		// 너비 기준
		res_w = fw;
		res_h = fw * constants::CLIENT_RATIO;
	}

	ogl::gl_width = res_w;
	ogl::gl_height = res_h;

	glViewport(0, 0, res_w, res_h);
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
