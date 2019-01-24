#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>
#include <vector>
#include "Mesh.h"



class Model
{
public:

	Model(string filepath);

	void render(const unsigned int shaderProgram);

	bool firstPerson;
	void setFirstPerson(bool firstperson);
	bool getFirstPerson();

	static unsigned int TextureFromFile(const char* filepath, const string& directory, bool gamma = false);

private:

	std::vector<Mesh> v_meshes;
	string directory;
	vector<Texture> v_textures;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
	                                     std::string typeName);
};
