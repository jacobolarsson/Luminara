#include "Light.h"

Light::Light(Transform const& transform, LightType const& type, LightData const& data)
	: Object(transform)
	, m_type(type)
	, m_data(data)
{
}

void Light::Update()
{
}
