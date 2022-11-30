#include "pch.hpp"
#include "Main.hpp"

std::random_device seed{};
std::uniform_real_distribution<float> distr_color{ 0.0f, 1.0f };
std::default_random_engine random_engine{ seed() };

constexpr std::chrono::system_clock performance_clock{};
std::chrono::system_clock::time_point elapsed_timer{};
float elapsed_time{};

constexpr int client_w{ 800 }, client_h{ 600 };

TankShow my_system{};
bool flag_culling = true;

bool flag_rot_head = false;
bool flag_rot_arms = false;
float body_rot = 0.0f;
float head_rot_y = 0.0f;
float arms_rot_z = 0.0f;
float arms_loop_dir = 0.0f;

float camera_x, camera_y, camera_z;
float camera_rot_x, camera_rot_y, camera_rot_z;
bool flag_camera_rot_y = false;
bool flag_camera_rot_axis = false;


int main(int argc, char** argv)
{
	ogl::Awake(argc, argv);

	try
	{
		ogl::Ready("Practice 18", client_w, client_h, 100, 100);
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
		my_system.Awake();

		my_system.Start();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	ogl::Start();
}

GLvoid UpdateFrames(int value)
{
	using namespace std::chrono;
	const auto time_now = performance_clock.now();
	const auto time_between = time_now - elapsed_timer;
	const auto mill = duration_cast<milliseconds>(time_between);
	elapsed_time = static_cast<float>(mill.count()) / 1000.0f;

	const auto rotation = glm::radians(65.0f) * elapsed_time;
	
	if (flag_rot_head)
	{
		const auto head_rotation = glm::radians(55.0f) * elapsed_time;

		head_rot_y += head_rotation;
		my_system.HeadRotate(head_rot_y);
	}

	if (flag_rot_arms)
	{
		const auto arms_rotation = glm::radians(80.0f) * elapsed_time;

		arms_loop_dir += arms_rotation;

		constexpr auto pi = glm::pi<float>();
		arms_rot_z = glm::sin(arms_loop_dir) * pi / 2;
		my_system.ArmsRotate(arms_rot_z);
	}

	if (flag_camera_rot_y)
	{
		camera_rot_y += rotation;
		my_system.CameraRotate(0.0f, rotation, 0.0f);
	}

	ogl::Refresh();
	ogl::SetTimer(10);

	elapsed_timer = time_now;
}

GLvoid Render()
{
	my_system.PrepareRendering();
	my_system.DrawScreens();
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
		// 머리 회전
		case 'm':
		case 'M':
		{
			flag_rot_head = !flag_rot_head;
		}
		break;

		// 팔 회전
		case 'n':
		case 'N':
		{
			flag_rot_arms = !flag_rot_arms;
		}
		break;

		case 'x':
		case 'X':
		{
			flag_camera_rot_axis = !flag_camera_rot_axis;
		}
		break;

		case 'y':
		case 'Y':
		{
			flag_camera_rot_y = !flag_camera_rot_y;
		}
		break;

		case 'a':
		case 'A':
		{
			camera_x += camera_movement;
			my_system.CameraMove(+camera_movement, 0.0f, 0.0f);
		}
		break;

		case 'd':
		case 'D':
		{
			camera_x -= camera_movement;
			my_system.CameraMove(-camera_movement, 0.0f, 0.0f);
		}
		break;

		case 'w':
		case 'W':
		{
			camera_z += camera_movement;
			my_system.CameraMove(0.0f, 0.0f, +camera_movement);
		}
		break;

		case 's':
		case 'S':
		{
			camera_z -= camera_movement;
			my_system.CameraMove(0.0f, 0.0f, -camera_movement);
		}
		break;

		case 'q':
		case 'Q':
		{
			camera_y += camera_movement * 0.6f;
			my_system.CameraMove(0.0f, +camera_movement, 0.0f);
		}
		break;

		case 'e':
		case 'E':
		{
			camera_y -= camera_movement * 0.6f;
			my_system.CameraMove(0.0f, -camera_movement, 0.0f);
		}
		break;

		case 'c':
		case 'C':
		{
			flag_camera_rot_y = false;
			flag_camera_rot_axis = false;
		}
		break;

		case 'r':
		case 'R':
		{
			body_rot = 0.0f;

			my_system.JumpTo(0.0f, 0.0f, 0.0f);
			my_system.Rotate(0.0f, 0.0f, 0.0f);
			
			camera_rot_y = 0.0f;
			camera_x = 0.0f;
			camera_y = 0.0f;
			camera_z = 0.0f;
			my_system.ResetCamera();

			flag_camera_rot_y = false;
			flag_camera_rot_axis = false;
		}
		break;

		case 'h':
		case 'H':
		{
			flag_culling = !flag_culling;
			if (flag_culling)
			{
				ogl::TurnOnOption(GL_CULL_FACE);
			}
			else
			{
				ogl::TurnOffOption(GL_CULL_FACE);
			}
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
			body_rot += rotation;

			my_system.Rotate(0.0f, body_rot, 0.0f);
		}
		break;

		case GLUT_KEY_RIGHT:
		{
			body_rot -= rotation;

			my_system.Rotate(0.0f, body_rot, 0.0f);
		}
		break;

		case GLUT_KEY_UP:
		{
			my_system.Move(0.0f, 0.0f, -movement);
		}
		break;

		case GLUT_KEY_DOWN:
		{
			my_system.Move(0.0f, 0.0f, +movement);
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
