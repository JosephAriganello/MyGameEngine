#ifndef LoadOBJMODEL_H
#define LoadOBJMODEL_H

#include "Mesh.h"
#include "../../FX/MaterialLoader.h"
#include "../../Math/BoundingBox.h"

class LoadObjModel{
public:
	LoadObjModel();
	~LoadObjModel();

	void LoadModel(const std::string& fileName_);
	void LoadModel(const std::string& fileName_, const std::string& matName_);
	std::vector<Vertex> GetVerts();
	std::vector<GLuint> GetIndices();
	std::vector<SubMesh> GetMeshes();
	BoundingBox GetBoundingBox();
	
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<GLuint> indices;
	std::vector<GLuint> normalIndices;
	std::vector<GLuint> textureIndices;
	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> meshes;
	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void LoadMaterialLibrary(const std::string& matName_);
	Material currentMaterial;
	BoundingBox boundingBox;
};

#endif //!LoadOBJMODEL_H