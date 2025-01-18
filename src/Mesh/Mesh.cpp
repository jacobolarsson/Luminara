#include "Mesh.h"

#include <glad/glad.h>

void Mesh::Upload()
{
    //m_vertices.emplace_back(0.5f, 0.5f, 0.0f);
    //m_vertices.emplace_back(0.5f, -0.5f, 0.0f);
    //m_vertices.emplace_back(-0.5f, -0.5f, 0.0f);
    //m_vertices.emplace_back(-0.5f, 0.5f, 0.0f);

    m_vertices.emplace_back(-0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f, -0.5f);
    m_vertices.emplace_back(-0.5f,  0.5f, -0.5f);
    m_vertices.emplace_back(-0.5f, -0.5f, -0.5f);

    m_vertices.emplace_back(-0.5f, -0.5f,  0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f,  0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f, -0.5f,  0.5f);

    m_vertices.emplace_back(-0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f,  0.5f, -0.5f);
    m_vertices.emplace_back(-0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back(-0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back(-0.5f, -0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f,  0.5f,  0.5f);

    m_vertices.emplace_back( 0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f,  0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f,  0.5f);

    m_vertices.emplace_back(-0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f,  0.5f);
    m_vertices.emplace_back( 0.5f, -0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f, -0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f, -0.5f, -0.5f);

    m_vertices.emplace_back(-0.5f,  0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f, -0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back( 0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f,  0.5f,  0.5f);
    m_vertices.emplace_back(-0.5f,  0.5f, -0.5f);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	//// Upload index data
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	glBindVertexArray(0u);
}

void Mesh::Bind() const
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}
