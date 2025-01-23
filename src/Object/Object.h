#pragma once

#include "../Transform/Transform.h"
#include "../Mesh/Mesh.h"
#include "../Material/Material.h"

#include <memory>

class Object
{
public:
	Object(Transform const& transform, std::shared_ptr<Mesh> mesh = nullptr, std::shared_ptr<Material> material = nullptr)
		: m_transform(transform)
		, m_mesh(mesh)
		, m_material(material)
	{}
	virtual ~Object() {}
	virtual void Update();

	inline Transform const& GetTransform() const { return m_transform; }
	inline std::shared_ptr<Mesh> const& GetMesh() const { return m_mesh; }
	inline std::shared_ptr<Material> const& GetMaterial() const { return m_material; }

	inline void SetTransform(Transform const& transform) { m_transform = transform; }
	inline void SetMesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }
	inline void SetMaterial(std::shared_ptr<Material> material) { m_material = material; }

protected:
	Transform m_transform;
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Material> m_material;
};
