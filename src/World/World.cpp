#include "World.h"
#include "../Renderer/Renderer.h"
#include "../Camera/Camera.h"
#include "../Light/Light.h"

std::unordered_set<std::shared_ptr<Object>> World::m_objects;

void World::Initialize()
{
	Transform trans;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->Upload();

	std::shared_ptr<Shader> litShader = std::make_shared<Shader>("data/shaders/lit.vert",
															     "data/shaders/lit.frag");

	std::shared_ptr<Texture> tex = std::make_shared<Texture>("data/textures/pepe.png");
	std::shared_ptr<Material> mat = std::make_shared<Material>(litShader, tex);

	std::shared_ptr<Object> obj = std::make_shared<Object>(trans, mesh, mat);

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

	std::shared_ptr<Shader> lightShader = std::make_shared<Shader>("data/shaders/light.vert",
															       "data/shaders/light.frag");
	std::shared_ptr<Material> lightMat = std::make_shared<Material>(lightShader);

	pointLight->SetMesh(mesh);
	pointLight->SetMaterial(lightMat);

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

	// Check if it's a light, add it to the renderer's lights container if it is
	std::shared_ptr<Light> lightPtr(std::dynamic_pointer_cast<Light>(obj));
	if (lightPtr) {
		Renderer::AddLightObject(lightPtr);
		renderObj = lightPtr->GetType() != LightType::DIR; // Don't render if it's directional
	}

	m_objects.insert(obj);

	if (renderObj) {
		Renderer::AddRenderObject(obj);
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
