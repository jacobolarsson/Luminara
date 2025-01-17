#pragma once

class Shader
{
public:
	Shader(const char* vertFilename, const char* fragFilename);

	void Use() const;

private:
	unsigned m_id;
};