#pragma once

#include "../Mesh/Mesh.h"
#include "../Material/Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class Light;

class Model
{
public:
	Model(const char* path);

	Model(std::vector<Mesh> const& meshes) : m_meshes(meshes)
	{}

	void Load(const char* path);
	void Draw(Shader const& shader,
			  Transform const& transform,
			  std::shared_ptr<Camera> cam,
			  std::shared_ptr<Light> light) const;

	void UploadShaderData(Shader const& shader,
						  Transform const& transform,
						  std::shared_ptr<Camera> cam,
						  std::shared_ptr<Light> light) const;

	inline std::vector<Mesh> const& GetMeshes() const { return m_meshes; }

	inline void SetMeshes(std::vector<Mesh> const& meshes) { m_meshes = meshes; }

private:
	void UploadShaderMtxData(Shader const& shader,
							 Transform const& transform,
							 std::shared_ptr<Camera> cam) const;

	void UploadShaderLightData(Shader const& shader,
							   std::shared_ptr<Camera> cam,
							   std::shared_ptr<Light> light) const;

	void ProcessAssimpNode(aiNode* assimpNode, const aiScene* scene);
	void ProcessAssimpMesh(Mesh& mesh, aiMesh* assimpMesh, const aiScene* scene);

	std::vector<Mesh> m_meshes;
};