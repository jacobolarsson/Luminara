#include "Material.h"
#include "../Light/Light.h"

#include <glad/glad.h>
#include <iostream>

void Material::UploadTextures() const
{
	for (std::shared_ptr<Texture> tex : m_textures) {
		tex->Upload();
	}
}

void Material::BindTextures() const
{
	for (std::shared_ptr<Texture> tex : m_textures) {
		tex->Bind();
	}
}