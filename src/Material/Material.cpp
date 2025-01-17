#include "Material.h"

#include <iostream>

void Material::Use() const
{
	if (m_shader) {
		m_shader->Use();
	} else {
		std::cerr << "Material shader not set" << std::endl;
	}
}
