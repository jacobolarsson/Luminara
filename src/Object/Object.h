#pragma once

#include "../Transform/Transform.h"
#include "../Model/Model.h"

#include <memory>

class Object
{
public:
	Object(Transform const& transform, std::shared_ptr<Model> model = nullptr)
		: m_transform(transform)
		, m_model(model)
	{}

	virtual ~Object() {}
	virtual void Update();

	inline Transform const& GetTransform() const { return m_transform; }
	inline std::shared_ptr<Model> GetModel() const { return m_model; }

	inline void SetTransform(Transform const& transform) { m_transform = transform; }
	inline void SetModel(std::shared_ptr<Model> model) { m_model = model; }

protected:
	Transform m_transform;
	std::shared_ptr<Model> m_model;
};
