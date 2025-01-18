#pragma once

struct MouseData
{
	bool firstMouse = false;
	float lastX = 0.0f;
	float lastY = 0.0f;
};

class Input
{
public:
	Input() = delete;

	static void Initialize();
	static void Update();

	inline static MouseData const& GetMouseData() { return m_mouseData; }
	inline static void SetMouseData(MouseData const& mouseData) { m_mouseData = mouseData; }

private:
	static void UpdateCamera();
	static MouseData m_mouseData;
};