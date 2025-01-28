#include "Material.h"
#include "../Light/Light.h"

#include <glad/glad.h>
#include <iostream>

void Material::BindTextures() const
{
	for (size_t i = 0; i < m_textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		m_textures.at(i)->Bind();
	}
}