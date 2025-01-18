#pragma once

class Time
{
public:
	Time() = delete;

	static void Initialize();
	static void Update();

	inline static float GetDeltaTime() { return m_deltaTime; }
private:
	static float m_deltaTime;
	static double m_timeSinceStart;
};