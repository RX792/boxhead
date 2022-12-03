#pragma once
#include "Framework.hpp"
#include "WindowManager.hpp"
#include "Constants.hpp"

GLvoid Render(GLvoid);
GLvoid UpdateView(const int w, const int h);
GLvoid UpdateKeyboard(const unsigned char key, const int x, const int y);
GLvoid UpdateSpecialKeyboard(const int key, const int x, const int y);
GLvoid UpdateMouse(const int button, const int state, const int x, const int y);
GLvoid UpdateMouseMotion(const int x, const int y);
GLvoid UpdateFrames(const int delta_time);

Framework* Framework::Instance = nullptr;
HWND WindowManager::windowHandle = nullptr;
HDC WindowManager::deviceContext = nullptr;
HGLRC WindowManager::renderingContext = nullptr;
