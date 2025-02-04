#include "Material.h"
#include "../Light/Light.h"

#include <glad/glad.h>
#include <iostream>

void Material::BindTextures() const
{
	for (size_t i = 0; i < m_textures.size(); i++) {
		std::shared_ptr<Texture> tex = m_textures.at(i);
		if (!tex) { // Do not bind texture that was not set
			continue;
		}

		glActiveTexture(GL_TEXTURE0 + i);
		tex->Bind();
	}
}