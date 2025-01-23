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
	void UploadVec3(const char* name, vec3 const& vec) const;
	void UploadFloat(const char* name, float value) const;

private:
	unsigned m_id;
};