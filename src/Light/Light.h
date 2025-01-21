#pragma once
#include "../Object/Object.h"
#include "LightTypes.h"

class Light : public Object
{
public:
	Light(Transform const& transform, LightType const& type, LightData const& data);
	~Light() override {}

	void Update() override;

	inline LightType GetType() const { return m_type; }
	inline LightData GetData() const { return m_data; }

private:
	LightType m_type;
	LightData m_data;
};