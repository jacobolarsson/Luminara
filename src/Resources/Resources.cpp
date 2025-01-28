#include "Resources.h"

std::unordered_map<std::string, Shader> Resources::m_shaders;
std::unordered_map<std::string, std::shared_ptr<Texture>> Resources::m_textures;

Shader const& Resources::GetShader(std::string const& name)
{
	if (m_shaders.find(name) != m_shaders.end()) {
		return m_shaders.at(name);
	}

	std::string shaderDir = "data/shaders/";
	std::string vertFilename = shaderDir + name + ".vert";
	std::string fragFilename = shaderDir + name + ".frag";

	// If the given shader was not found, create and insert it
	m_shaders.insert({ name, Shader(vertFilename, fragFilename) });

	return m_shaders.at(name);
}

std::shared_ptr<Texture> Resources::GetTexture(std::string const& path)
{
	if (m_textures.find(path) != m_textures.end()) {
		return m_textures.at(path);
	}

	// If the given texture was not found, create and insert it
	m_textures.insert({ path, std::make_shared<Texture>(path.c_str()) });

	return m_textures.at(path);
}
