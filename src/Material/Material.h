#pragma once

#include "../Shader/Shader.h"
#include "../Transform/Transform.h"
#include "../Texture/Texture.h"

#include <memory>
#include <vector>

class Material
{
public:
	Material(std::vector<std::shared_ptr<Texture>> const& textures = {})
		: m_textures(textures)
	{}

	void BindTextures() const;

	inline void SetTextures(std::vector<std::shared_ptr<Texture>> textures) { m_textures = textures; }

private:
	std::vector<std::shared_ptr<Texture>> m_textures;
};