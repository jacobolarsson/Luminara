#pragma once

struct GLFWwindow;

struct WindowData
{
	int width;
	int height;
	const char* title;
};

class Window
{
public:
	Window() = delete;

	static void Initialize();
	static bool ShouldClose();
	static void SwapBuffers();

	inline static GLFWwindow* GetWindow() { return m_window; }

private:
	static GLFWwindow* m_window;
	static WindowData m_data;
};