#include "pch.hpp"
#include "Main.hpp"
#include "GameScene.hpp"

Framework MySystem{};

std::random_device seed{};
std::uniform_real_distribution<float> distr_color{ 0.0f, 1.0f };
std::default_random_engine random_engine{ seed() };

constexpr std::chrono::system_clock performance_clock{};
std::chrono::system_clock::time_point elapsed_timer{};
float elapsed_time{};

int main(int argc, char** argv)
{
	try
	{
		ogl::Awake(argc, argv);

		ogl::Ready("Shooter", constants::CLIENT_W, constants::CLIENT_H, 100, 100);
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

	// 게임 초기화 부분
	// 나머지 게임 진행은 모두 Scene 클래스에서 수행함
	try
	{
		auto game_scene = MySystem.AddScene<GameScene>();

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
	const auto ratio = fh / fw;

	if (ratio != constants::CLIENT_RATIO)
	{
		const auto scale_w = fw / ogl::gl_width;
		const auto scale_h = fh / ogl::gl_height;

		// 뷰 포트 좌표
		int res_x, res_y;

		// 뷰 표트 크기
		int res_w, res_h;

		if (constants::CLIENT_RATIO < ratio) // 높이가 너비보다 크다
		{
			// 너비 기준
			const auto wscale = ratio / constants::CLIENT_RATIO;

			res_w = w;
			res_h = int(res_w * constants::CLIENT_RATIO);

			res_x = 0;
			res_y = int((fh - res_h) / 2.0f);
		}
		else // 너비가 높이보다 크다
		{
			// 높이 기준
			const auto hscale = constants::CLIENT_RATIO / ratio;

			res_w = int(fh / constants::CLIENT_RATIO);
			res_h = h;

			res_x = int((fw - res_w) / 2.0f);
			res_y = 0;
		}

		ogl::gl_width = res_w;
		ogl::gl_height = res_h;

		glViewport(res_x, res_y, res_w, res_h);
	}
	else
	{
		glViewport(0, 0, w, h);
	}
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
