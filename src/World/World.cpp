#include "World.h"
#include "../Renderer/Renderer.h"
#include "../Camera/Camera.h"
#include "../Light/Light.h"

std::unordered_set<std::shared_ptr<Object>> World::m_objects;

void World::Initialize()
{
	Transform trans;
	Mesh mesh;
	mesh.Upload();

	std::vector<Mesh> meshes{ mesh };

	Shader litShader("Lit", "data/shaders/lit.vert", "data/shaders/lit.frag");
	Shader lightShader("Light", "data/shaders/light.vert", "data/shaders/light.frag");

	std::shared_ptr<Model> model = std::make_shared<Model>(meshes);
	std::shared_ptr<Object> obj = std::make_shared<Object>(trans, model);

	AddObject(obj);

	std::shared_ptr<Camera> cam = std::make_shared<Camera>();
	Camera::SetActiveCamera(cam);

	LightData pointLightData;
	pointLightData.pointData.constAtt = 1.0f;
	pointLightData.pointData.linAtt = 0.09f;
	pointLightData.pointData.quadAtt = 0.032f;
	pointLightData.pointData.color = { 1.0f, 1.0f, 1.0f };

	Transform pointLightTrans({ -3.0f, 0.0f, 0.0f }, {0.0f, 0.0f, 0.0f}, {0.1f, 0.1f, 0.1f});

	std::shared_ptr<Object> pointLight = std::make_shared<Light>(pointLightTrans,
																 LightType::POINT,
																 pointLightData);
	pointLight->SetModel(model);

	AddObject(pointLight);
}

void World::Update()
{
	for (std::shared_ptr<Object> obj : m_objects) {
		obj->Update();
	}
}

void World::AddObject(std::shared_ptr<Object> obj)
{
	// If object is already present
	if (m_objects.find(obj) != m_objects.end()) {
		return;
	}

	bool renderObj = true;
	const char* shaderName = "Lit";

	// Check if it's a light, add it to the renderer's lights container if it is
	std::shared_ptr<Light> lightPtr(std::dynamic_pointer_cast<Light>(obj));
	if (lightPtr) {
		Renderer::AddLightObject(lightPtr);
		renderObj = lightPtr->GetType() != LightType::DIR; // Don't render if it's directional
		shaderName = "Light";
	}

	m_objects.insert(obj);

	if (renderObj) {
		Renderer::AddRenderObject(RenderObject{ obj, shaderName });
	}
}

void World::RemoveObject(std::shared_ptr<Object> obj)
{
	// If object not is present
	if (m_objects.find(obj) == m_objects.end()) {
		return;
	}

	m_objects.erase(obj);
}
