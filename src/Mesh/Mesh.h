#pragma once
#include "../Math/Math.h"

#include <vector>

struct Vertex 
{
	Vertex(vec3 pos, vec3 norm, vec2 uv) : position(pos), normal(norm), UV(uv) {}

	vec3 position;
	vec3 normal;
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

	inline size_t GetIdxCount() const { return m_indices.size(); }

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned> m_indices;

	unsigned m_vao;
	unsigned m_vbo;
	unsigned m_ebo;
};