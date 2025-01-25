#include "Model.h"
#include "../Light/Light.h"

#include <iostream>
#include <glad/glad.h>

Model::Model(const char* path) : m_meshes({})
{
	Load(path);
}

void Model::Load(const char* path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	unsigned flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
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
	UploadShaderData(shader, transform, cam, light);
	shader.Use();

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
	mat4x4 modelMtx = transform.ModelMatrix();
	mat4x4 modelToViewMtx = cam->ViewMatrix() * modelMtx;

	shader.UploadMat4x4("modelMtx", modelMtx);
	shader.UploadMat4x4("normalMtx", glm::transpose(glm::inverse(modelToViewMtx)));
	shader.UploadMat4x4("viewMtx", cam->ViewMatrix());
	shader.UploadMat4x4("projectionMtx", cam->ProjectionMatrix());
}

void Model::UploadShaderLightData(Shader const& shader,
								  std::shared_ptr<Camera> cam,
								  std::shared_ptr<Light> light) const
{
	vec3 lightPos_world = light->GetTransform().GetPosition();

	shader.UploadVec3("lightPos_view", cam->ViewMatrix() * vec4(lightPos_world, 1.0f));
	shader.UploadVec3("lightColor", light->GetData().pointData.color);
		  
	shader.UploadFloat("constAtt", light->GetData().pointData.constAtt);
	shader.UploadFloat("linAtt", light->GetData().pointData.linAtt);
	shader.UploadFloat("quadAtt", light->GetData().pointData.quadAtt);
}

/// <summary>
/// Process each mesh located at the current node and process all child
/// nodes recursively
/// </summary>
void Model::ProcessAssimpNode(aiNode* assimpNode, const aiScene* scene)
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
void Model::ProcessAssimpMesh(Mesh& mesh, aiMesh* assimpMesh, const aiScene* scene)
{
	// Process vertices
	for (unsigned i = 0; i < assimpMesh->mNumVertices; i++) {
		vec3 pos(assimpMesh->mVertices[i].x, assimpMesh->mVertices[i].y, assimpMesh->mVertices[i].z);
		vec3 norm(0.0f, 0.0f, 0.0f);
		vec2 uv(0.0f, 0.0f);

		if (assimpMesh->HasNormals()) {
			norm = { assimpMesh->mNormals[i].x, assimpMesh->mNormals[i].y, assimpMesh->mNormals[i].z };
		}

		if (assimpMesh->mTextureCoords[0]) { // If the mesh has texture coordinates
			uv = { assimpMesh->mTextureCoords[0]->x, assimpMesh->mTextureCoords[0]->y };
		}

		Vertex v(pos, norm, uv);
		mesh.AddVertex(v);
	}
	// Process indices
	for (unsigned i = 0; i < assimpMesh->mNumFaces; i++) {
		aiFace assimpFace = assimpMesh->mFaces[i];
		for (unsigned j = 0; j < assimpFace.mNumIndices; j++) {
			mesh.AddIndex(assimpFace.mIndices[j]);
		}
	}
	mesh.Upload(); // Once we have all vertex data, send it to the GPU
}
