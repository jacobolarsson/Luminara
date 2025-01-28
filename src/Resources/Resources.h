#pragma once
#include "../Texture/Texture.h"
#include "../Shader/Shader.h"

#include <unordered_map>
#include <string>

class Resources
{
public:
	Resources() = delete;

	static Shader const& GetShader(std::string const& name);
	static std::shared_ptr<Texture> GetTexture(std::string const& path);

private:
	static std::unordered_map<std::string, Shader> m_shaders;
	static std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
};