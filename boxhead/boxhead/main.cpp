#include "pch.hpp"
#include "Main.hpp"
#include "MainScene.hpp"
#include "GameScene.hpp"

Framework MySystem{};

constexpr std::string_view TITLE = "Shooter";
const std::vector<wchar_t> WTITLE{ TITLE.cbegin(), TITLE.cend() };

std::random_device seed{};
std::uniform_real_distribution<float> distr_color{ 0.0f, 1.0f };
std::default_random_engine random_engine{ seed() };

int main(int argc, char** argv)
{
	try
	{
		ogl::Awake(argc, argv);

		ogl::Ready(TITLE, constants::CLIENT_W, constants::CLIENT_H, 30, 30);
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

	// 게임 초기화 부분
	// 나머지 게임 진행은 모두 Scene 클래스에서 수행
	try
	{
		auto game_scene0 = MySystem.AddScene<MainScene>();
		auto game_scene1 = MySystem.AddScene<GameScene>();
		auto game_scene2 = MySystem.AddScene<GameScene>();

		MySystem.Awake();

		MySystem.Start();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	WindowManager::Awake(TITLE.data());

	ogl::Start();
}

GLvoid UpdateFrames(int value)
{
	const auto inspect_timing = Timer::BeginInspection();

	MySystem.Update();

	ogl::Refresh();
	ogl::SetTimer(10);

	Timer::EndInspection(inspect_timing);
}

GLvoid UpdateView(const int w, const int h)
{
	MySystem.OnUpdateView(w, h);

	const auto fw = static_cast<float>(w);
	const auto fh = static_cast<float>(h);
	const auto ratio = fh / fw;

	if (ratio != constants::CLIENT_RATIO)
	{
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
			res_y = (h - res_h) / 2;
		}
		else // 너비가 높이보다 크다
		{
			// 높이 기준
			const auto hscale = constants::CLIENT_RATIO / ratio;

			res_w = int(fh / constants::CLIENT_RATIO);
			res_h = h;

			res_x = (w - res_w) / 2;
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
	MySystem.OnUpdateKeyboard(key, x, y);

	ogl::Refresh();
}

GLvoid UpdateSpecialKeyboard(const int key, const int x, const int y)
{
	MySystem.OnUpdateSpecialKey(key, x, y);

	ogl::Refresh();
}

GLvoid UpdateMouse(const int button, const int state, const int sx, const int sy)
{
	MySystem.OnUpdateMouse(button, state, sx, sy);

	ogl::Refresh();
}

GLvoid UpdateMouseMotion(const int mx, const int my)
{
	MySystem.OnUpdateMouseMotion(mx, my);

	ogl::Refresh();
}

GLvoid Render(GLvoid)
{
	MySystem.PrepareRendering();
	MySystem.Render();
}

float RandomizeColour()
{
	return distr_color(random_engine);
}
