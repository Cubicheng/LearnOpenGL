#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shaders.h"
#include "mesh.h"

class Model {
public:
	Model(const char* path) {
		loadModel(path);
	}
	void Draw(const Shader &shader);
private:
	std::vector<Texture> textures_loaded;

	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
};