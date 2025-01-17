#pragma once
#include "../Math/Math.h"

#include <vector>

class Mesh
{
public:
	Mesh() : m_vertices(), m_indices(), m_vao(0u), m_vbo(0u), m_ebo(0u) {}

	Mesh(std::vector<vec3> const& vertices, std::vector<unsigned> const& indices)
		: m_vertices(vertices)
		, m_indices(indices)
		, m_vao(0u)
		, m_vbo(0u)
		, m_ebo(0u)
	{}

	void Load();
	void Bind() const;

private:
	std::vector<vec3> m_vertices;
	std::vector<unsigned> m_indices;

	unsigned m_vao;
	unsigned m_vbo;
	unsigned m_ebo;
};