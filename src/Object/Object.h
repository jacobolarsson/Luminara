#pragma once

#include "../Transform/Transform.h"
#include "../Mesh/Mesh.h"
#include "../Material/Material.h"

#include <memory>

class Object
{
public:
	Object(Transform const& transform, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
		: m_transform(transform)
		, m_mesh(mesh)
		, m_material(material)
	{}

	void LoadMesh();

	inline std::shared_ptr<Mesh> const& GetMesh() const { return m_mesh; }
	inline std::shared_ptr<Material> const& GetMaterial() const { return m_material; }

private:
	Transform m_transform;
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Material> m_material;
};
