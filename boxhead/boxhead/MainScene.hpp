#pragma once
#include "Scene.hpp"

class MainScene : public Scene
{
public:
	MainScene(const size_t& id)
		: Scene(id)
	{
		SetName("MainScene");
	}

	void OnUpdateSpecialKey(const int& key, const int& x, const int& y) override
	{
		switch (key)
		{
			case GLFW_KEY_ENTER:
			{
				
			}
			break;

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

			case GLFW_KEY_ESCAPE:
			case GLUT_KEY_F4:
			{
				std::quick_exit(0);
			}
			break;
		}
	}
	
	void OnUpdateMouse(const int& button, const int& state, const int& x, const int& y) override
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
	}

	void PrepareRendering() override
	{}

	void Render() override
	{}
};
