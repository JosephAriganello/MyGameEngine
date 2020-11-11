#include "LoadObjModel.h"

LoadObjModel::LoadObjModel() : currentMaterial(Material()) {

}


LoadObjModel::~LoadObjModel() {
	vertices.clear();
	vertices.shrink_to_fit();
	normals.clear();
	normals.shrink_to_fit();
	textureCoords.clear();
	textureCoords.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();
	normalIndices.clear();
	normalIndices.shrink_to_fit();
	textureIndices.clear();
	textureIndices.shrink_to_fit();
	meshVertices.clear();
	meshVertices.shrink_to_fit();
	meshes.clear();
	meshes.shrink_to_fit();
}

void LoadObjModel::LoadModel(const std::string & fileName_) {
	std::ifstream in(fileName_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file " + fileName_, __FILE__, __LINE__);
		return;
	}
	else {

		glm::vec3 min = glm::vec3(100000.0f, 100000.0f, 100000.0f);
		glm::vec3 max = glm::vec3(-100000.0f, -100000.0f, -100000.0f);

		std::string line;
		while (std::getline(in, line)) {

			//VERTEX DATA
			if (line.substr(0, 2) == "v ") {
				std::istringstream v(line.substr(2));
				double x, y, z;
				v >> x >> y >> z;

				if (min.x > x) {
					min.x = x;
				}
				if (max.x < x) {
					max.x = x;
				}
				if (min.y > y) {
					min.y = y;
				}
				if (max.y < y) {
					max.y = y;
				}
				if (min.z > z) {
					min.z = z;
				}
				if (max.z < z) {
					max.z = z;
				}

				boundingBox.minVert = min;
				boundingBox.maxVert = max;

				vertices.push_back(glm::vec3(x, y, z));
			}

			//NORMAL DATA
			else if (line.substr(0, 3) == "vn ") {
				std::istringstream vn(line.substr(3));
				double vx, vy, vz;
				vn >> vx >> vy >> vz;
				normals.push_back(glm::vec3(vx, vy, vz));
			}

			//TEXTURE COORDINATE DATA
			else if (line.substr(0, 3) == "vt ") {
				std::istringstream vt(line.substr(3));
				double vtx, vty;
				vt >> vtx >> vty;
				textureCoords.push_back(glm::vec2(vtx, vty));
			}
			
			//FACE DATA
			///vertex index/normal index/texture coordinate index
			else if (line.substr(0, 2) == "f ") {

				int i, t, n;
				char c;
				std::istringstream f(line.substr(2));

				f >> i >> c >> t >> c >> n;
				i--;
				t--;
				n--;

				indices.push_back(i);
				textureIndices.push_back(t);
				normalIndices.push_back(n);

				f >> i >> c >> t >> c >> n;
				i--;
				t--;
				n--;

				indices.push_back(i);
				textureIndices.push_back(t);
				normalIndices.push_back(n);

				f >> i >> c >> t >> c >> n;
				i--;
				t--;
				n--;

				indices.push_back(i);
				textureIndices.push_back(t);
				normalIndices.push_back(n);
			}

			//NEW MATERIAL
			else if (line.substr(0, 7) == "usemtl ") {
				if (indices.size() > 0) {
					PostProcessing();
				}
				LoadMaterial(line.substr(7));
			}
		}
		PostProcessing();
	}
}

void LoadObjModel::LoadModel(const std::string & fileName_, const std::string & matName_) {
	LoadMaterialLibrary(matName_);
	LoadModel(fileName_);
}

std::vector<Vertex> LoadObjModel::GetVerts() {
	return meshVertices;
}

std::vector<GLuint> LoadObjModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadObjModel::GetMeshes() {
	return meshes;
}

BoundingBox LoadObjModel::GetBoundingBox()
{
	return boundingBox;
}

void LoadObjModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;
	meshes.push_back(mesh);

	indices.clear();
	indices.shrink_to_fit();

	normalIndices.clear();
	normalIndices.shrink_to_fit();

	textureIndices.clear();
	textureIndices.shrink_to_fit();

	meshVertices.clear();
	meshVertices.shrink_to_fit();

	currentMaterial = Material();
}

void LoadObjModel::LoadMaterial(const std::string & fileName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadObjModel::LoadMaterialLibrary(const std::string & matName_) {
	MaterialLoader::LoadMaterial(matName_);
}
