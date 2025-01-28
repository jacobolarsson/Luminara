#pragma once

class Texture
{
public:
	Texture(char const* path);

	void Load(char const* path);
	void Bind() const;

private:
	unsigned m_id;
};