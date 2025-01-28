#pragma once

#include "../Transform/Transform.h"
#include "../Camera/Camera.h"

#include <memory>
#include <unordered_map>
#include <string>

class Shader
{
public:
	Shader(std::string const& vertFilename, std::string const& fragFilename);

	void Use() const;
	void UploadMat4x4(const char* name, mat4x4 const& mat) const;
	void UploadVec3(const char* name, vec3 const& vec) const;
	void UploadFloat(const char* name, float value) const;
	void UploadInt(const char* name, int value) const;
private:
	unsigned m_id;
};