#include "Light.h"
#include "../Time/Time.h"

#include <GLFW/glfw3.h>

Light::Light(Transform const& transform, LightType const& type, LightData const& data)
	: Object(transform)
	, m_type(type)
	, m_data(data)
    , m_timer(0.0f)
{
}

void Light::Update()
{
    //vec3 pos = m_transform.GetPosition();

    //vec3 rotationaxis = glm::cross(glm::cross(pos, glm::vec3(0.0f, 1.0f, 0.0f)), pos);
    //vec4 rotatedRadialVec = glm::rotate(glm::mat4(1.0f), -Time::GetDeltaTime(), rotationaxis) * glm::vec4(pos, 0.0f);

    //m_transform.SetPosition(glm::vec3(rotatedRadialVec));

    vec3 pos = m_transform.GetPosition();
    m_timer += Time::GetDeltaTime();
    
    m_transform.SetPosition(pos + vec3{ 0.04f, 0.0f, 0.0f } * glm::sin(m_timer));
}
