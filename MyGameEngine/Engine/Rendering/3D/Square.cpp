#include "Square.h"

Square::Square(GLuint shaderProgram_, GLuint textureID_) : Model(shaderProgram_){

	//Create a Vertex and a vertexList.
	Vertex v;
	std::vector<Vertex> vertexList;
	
	///Triangle 1
	//Top Left
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	//Bottom Right
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	//Bottom Left x(0.3f)
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	
	///Triangle 2
	//Top Right x(0.3f)
	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	//Top Left
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	//Bottom Left x(0.3f)
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	//Add the vertexList to the meshes.
	AddMesh(new Mesh(&vertexList, textureID_, shaderProgram_));
}


Square::~Square(){

}
