#pragma once

#include "../Transform/Transform.h"
#include "../Camera/Camera.h"

#include <memory>

class Shader
{
public:
	Shader(const char* vertFilename, const char* fragFilename);

	void Use() const;
	void UploadMat4x4(const char* name, mat4x4 const& mat) const;

private:
	unsigned m_id;
};