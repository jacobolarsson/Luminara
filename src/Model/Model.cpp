#include "Model.h"
#include "../Light/Light.h"
#include "../Resources/Resources.h"

#include <iostream>
#include <glad/glad.h>

Model::Model(char const* path) : m_meshes({})
{
	Load(path);
}

void Model::Load(char const* path)
{
	// Store the directory of the given file
	std::string pathStr(path);
	m_directory = pathStr.substr(0, pathStr.find_last_of('/'));

	// read file via ASSIMP
	Assimp::Importer importer;
	unsigned flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | /*aiProcess_FlipUVs |*/ aiProcess_CalcTangentSpace;
	const aiScene* scene = importer.ReadFile(path, flags);

	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
		return;
	}

	ProcessAssimpNode(scene->mRootNode, scene);
}

void Model::Draw(Shader const& shader,
				 Transform const& transform,
				 std::shared_ptr<Camera> cam,
				 std::shared_ptr<Light> light) const
{
	shader.Use();
	UploadShaderData(shader, transform, cam, light);

	for (Mesh const& mesh : m_meshes) {
		mesh.Draw();
	}
}

void Model::UploadShaderData(Shader const& shader,
							 Transform const& transform,
							 std::shared_ptr<Camera> cam,
							 std::shared_ptr<Light> light) const
{
	UploadShaderMtxData(shader, transform, cam);
	if (light) {
		UploadShaderLightData(shader, cam, light);
	}
}

void Model::UploadShaderMtxData(Shader const& shader,
								Transform const& transform,
								std::shared_ptr<Camera> cam) const
{
	mat4x4 modelMtx = transform.GetModelMatrix();

	shader.UploadMat4x4("modelMtx", modelMtx);
	shader.UploadMat4x4("normalMtx", glm::transpose(glm::inverse(modelMtx)));
	shader.UploadMat4x4("viewMtx", cam->ViewMatrix());
	shader.UploadMat4x4("projectionMtx", cam->ProjectionMatrix());
}

void Model::UploadShaderLightData(Shader const& shader,
								  std::shared_ptr<Camera> cam,
								  std::shared_ptr<Light> light) const
{
	vec3 lightPos_world = light->GetTransform().GetPosition();

	shader.UploadVec3("lightPos_world", lightPos_world);
	shader.UploadVec3("lightColor", light->GetData().pointData.color);

	shader.UploadVec3("viewPos_world", cam->GetPosition());
		  
	shader.UploadFloat("constAtt", light->GetData().pointData.constAtt);
	shader.UploadFloat("linAtt", light->GetData().pointData.linAtt);
	shader.UploadFloat("quadAtt", light->GetData().pointData.quadAtt);

	shader.UploadInt("material.ambientTex", 0);
	shader.UploadInt("material.diffuseTex", 1);
	shader.UploadInt("material.specularTex", 2);
	shader.UploadInt("material.normalMap", 3);
}

/// <summary>
/// Process each mesh located at the current node and process all child
/// nodes recursively
/// </summary>
void Model::ProcessAssimpNode(aiNode const* assimpNode, aiScene const* scene)
{
	// Process meshes
	for (unsigned int i = 0; i < assimpNode->mNumMeshes; i++) {
		aiMesh* assimpMesh = scene->mMeshes[assimpNode->mMeshes[i]];
		Mesh mesh;
		m_meshes.push_back(mesh);

		ProcessAssimpMesh(m_meshes.at(m_meshes.size() - 1), assimpMesh, scene);
	}
	// Recursively process child nodes
	for (unsigned int i = 0; i < assimpNode->mNumChildren; i++) {
		ProcessAssimpNode(assimpNode->mChildren[i], scene);
	}
}

/// <summary>
/// Load mesh data from assimpMesh to our own Mesh data structure
/// </summary>
void Model::ProcessAssimpMesh(Mesh& mesh, aiMesh const* assimpMesh, aiScene const* scene)
{
	// Process vertices
	for (unsigned i = 0; i < assimpMesh->mNumVertices; i++) {
		vec3 pos(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z);
		vec3 norm(0.0f, 0.0f, 0.0f);
		vec3 tan(0.0f, 0.0f, 0.0f);
		vec3 bitan(0.0f, 0.0f, 0.0f);
		vec2 uv(0.0f, 0.0f);

		if (assimpMesh->HasNormals()) {
			norm = { assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z };
		}

		if (assimpMesh->mTextureCoords[0]) { // If the mesh has texture coordinates
			uv = { assimpMesh->mTextureCoords[0][i].x, assimpMesh->mTextureCoords[0][i].y };
			tan = { assimpMesh->mTangents[i].x, assimpMesh->mTangents[i].y, assimpMesh->mTangents[i].z };
			bitan = { assimpMesh->mBitangents[i].x, assimpMesh->mBitangents[i].y, assimpMesh->mBitangents[i].z };
		} 

		Vertex v(pos, norm, tan, bitan, uv);
		mesh.AddVertex(v);
	}

	// Process indices
	for (unsigned i = 0; i < assimpMesh->mNumFaces; i++) {
		aiFace assimpFace = assimpMesh->mFaces[i];
		for (unsigned j = 0; j < assimpFace.mNumIndices; j++) {
			mesh.AddIndex(assimpFace.mIndices[j]);
		}
	}

	// Process materials
	aiMaterial* assimpMaterial = scene->mMaterials[assimpMesh->mMaterialIndex];
	Material mat;
	ProcessAssimpMaterial(mat, assimpMaterial);
	mesh.SetMaterial(mat);

	mesh.Upload(); // Once we have all vertex data, send it to the GPU
}

void Model::ProcessAssimpMaterial(Material& material, aiMaterial const* assimpMat)
{
	std::vector<std::shared_ptr<Texture>> textures = {};

	aiString texFilename;
	std::string pathStr = "";

	textures.push_back(ProcessAssimpTexture(assimpMat, aiTextureType_AMBIENT));  // Load ambient texture
	textures.push_back(ProcessAssimpTexture(assimpMat, aiTextureType_DIFFUSE));  // Load diffuse texture
	textures.push_back(ProcessAssimpTexture(assimpMat, aiTextureType_SPECULAR)); // Load specular texture
	textures.push_back(ProcessAssimpTexture(assimpMat, aiTextureType_HEIGHT));   // Load normal map

	material.SetTextures(textures);
}

std::shared_ptr<Texture> Model::ProcessAssimpTexture(aiMaterial const* assimpMat, aiTextureType assimpTexType)
{
	aiString texFilename;
	assimpMat->GetTexture(assimpTexType, 0, &texFilename);

	std::string texFilenameStr(texFilename.C_Str());
	// Return null if the texture type could not be found
	if (texFilenameStr.empty()) { 
		return nullptr;
	}

	std::string pathStr = m_directory + '/' + texFilenameStr;

	return Resources::GetTexture(pathStr);
}