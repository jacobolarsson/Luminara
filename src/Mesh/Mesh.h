#pragma once
#include "../Math/Math.h"
#include "../Material/Material.h"

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
	Mesh() : m_vertices({}), m_indices({}), m_vao(0u), m_vbo(0u), m_ebo(0u) {}

	Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned> const& indices)
		: m_vertices(vertices)
		, m_indices(indices)
		, m_vao(0u)
		, m_vbo(0u)
		, m_ebo(0u)
	{}

	void Upload();
	void BindVao() const;
	void Draw() const;

	inline size_t GetIdxCount() const { return m_indices.size(); }

	inline void SetMaterial(Material const& material) { m_material = material; }
	inline void AddVertex(Vertex const& vertex) { m_vertices.push_back(vertex); }
	inline void AddIndex(unsigned idx) { m_indices.push_back(idx); }

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned> m_indices;
	Material m_material;

	unsigned m_vao;
	unsigned m_vbo;
	unsigned m_ebo;
};