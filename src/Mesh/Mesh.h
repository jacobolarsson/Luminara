#pragma once
#include "../Math/Math.h"

#include <vector>

struct Vertex 
{
	Vertex(vec3 p, vec2 uv) : position(p), UV(uv) {}

	vec3 position;
	vec2 UV;
};

class Mesh
{
public:
	Mesh() : m_vertices(), m_indices(), m_vao(0u), m_vbo(0u), m_ebo(0u) {}

	Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned> const& indices)
		: m_vertices(vertices)
		, m_indices(indices)
		, m_vao(0u)
		, m_vbo(0u)
		, m_ebo(0u)
	{}

	void Upload();
	void Bind() const;

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned> m_indices;

	unsigned m_vao;
	unsigned m_vbo;
	unsigned m_ebo;
};