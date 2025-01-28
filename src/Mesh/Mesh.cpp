#include "Mesh.h"

#include <glad/glad.h>

void Mesh::Upload()
{
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.0f,  0.0f, -1.0f), vec2(0.0f, 0.0f));

 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.0f,  0.0f,  1.0f), vec2(0.0f, 0.0f));

 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));

 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f,  0.5f), vec3( 1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f, -0.5f), vec3( 1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f, -0.5f), vec3( 1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f, -0.5f), vec3( 1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f,  0.5f), vec3( 1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f,  0.5f), vec3( 1.0f,  0.0f,  0.0f), vec2(0.0f, 0.0f));

 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.0f, -1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f, -0.5f), vec3( 0.0f, -1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f,  0.5f), vec3( 0.0f, -1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f, -0.5f,  0.5f), vec3( 0.0f, -1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.0f, -1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.0f, -1.0f,  0.0f), vec2(0.0f, 0.0f));

 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec3( 0.0f,  1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f, -0.5f), vec3( 0.0f,  1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f,  0.5f), vec3( 0.0f,  1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3( 0.5f,  0.5f,  0.5f), vec3( 0.0f,  1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f,  0.5f), vec3( 0.0f,  1.0f,  0.0f), vec2(0.0f, 0.0f));
 //   m_vertices.emplace_back(vec3(-0.5f,  0.5f, -0.5f), vec3( 0.0f,  1.0f,  0.0f), vec2(0.0f, 0.0f));

	//m_indices.emplace_back(0);
	//m_indices.emplace_back(1);
	//m_indices.emplace_back(3);
	//m_indices.emplace_back(1);
	//m_indices.emplace_back(2);
	//m_indices.emplace_back(3);

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	// Upload vertex data
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	// Set vertex position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

    // Set vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(vec3)));
    glEnableVertexAttribArray(1);

    // Set vertex UV attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(vec3) * 2));
    glEnableVertexAttribArray(2);

	// Upload index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);  

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindVertexArray(0u);
}

void Mesh::BindVao() const
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void Mesh::Draw() const
{
    m_material.BindTextures();
    BindVao();

    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}
