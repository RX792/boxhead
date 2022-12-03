#pragma once

class WindowManager
{
public:
	WindowManager()
	{}

	static void Awake(std::string_view title)
	{
		windowHandle = FindWindowA(NULL, title.data());
		deviceContext = GetDC(windowHandle);
		renderingContext = wglGetCurrentContext();
	}

	static HWND windowHandle;
	static HDC deviceContext;
	static HGLRC renderingContext;
};
