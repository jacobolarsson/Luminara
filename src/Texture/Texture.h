#pragma once

class Texture
{
public:
	Texture(const char* filename);

	void Load(const char* filename);
	void Upload();
	void Bind() const;

private:
	unsigned char* m_data;
	unsigned m_id;
	int m_width;
	int m_height;
};