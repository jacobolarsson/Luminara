#pragma once

#include "../Mesh/Mesh.h"
#include "../Material/Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

class Light;

class Model
{
public:
	Model(char const* path);

	Model(std::vector<Mesh> const& meshes) : m_meshes(meshes), m_directory("")
	{}

	void Load(char const* path);
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

	void ProcessAssimpNode(aiNode const* assimpNode, aiScene const* scene);
	void ProcessAssimpMesh(Mesh& mesh, aiMesh const* assimpMesh, aiScene const* scene);
	void ProcessAssimpMaterial(Material& material, aiMaterial const* assimpMat);
	std::shared_ptr<Texture> ProcessAssimpTexture(aiMaterial const* assimpMat, aiTextureType assimpTexType);

	std::vector<Mesh> m_meshes;
	std::string m_directory;
};