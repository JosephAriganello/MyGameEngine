#include "Mesh.h"

//A mesh takes a vertexList.
Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) : vao(0), vbo(0){
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;

	//This will generate the buffers.
	GenerateBuffers();
}


Mesh::~Mesh() {

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	subMesh.vertexList.clear();
	subMesh.vertexList.shrink_to_fit();
}

void Mesh::GenerateBuffers() {

	//This is going to generate the Vertex Array Object.
	glGenVertexArrays(1, &vao);

	//This is going to generate the Vertex Buffer Object.
	glGenBuffers(1, &vbo);

	//This is going to bind the Vertex Array Object allowing us to use it.
	glBindVertexArray(vao);

	//This is going to bind the Vertex Buffer Object allowing us to use it.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//This is going to buffer the data in the vertex list, which is currently zero.
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	// POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// NORMALS
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	viewPositionLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColorLoc = glGetUniformLocation(shaderProgram, "light.lightColor");

	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininessLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLoc = glGetUniformLocation(shaderProgram, "material.specular");
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4> instances_) {

	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	glUniform1f(shininessLoc, subMesh.material.shininess);
	glUniform1f(transparencyLoc, subMesh.material.transparency);
	glUniform3f(ambientLoc, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(diffuseLoc, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(specularLoc, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);

	//setting up light information
	glUniform3f(viewPositionLoc, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z);
	glUniform3f(lightPosLoc, camera_->GetLightSources()[0]->GetPosition().x,
		camera_->GetLightSources()[0]->GetPosition().y, camera_->GetLightSources()[0]->GetPosition().z);
	glUniform1f(lightAmbientLoc, camera_->GetLightSources()[0]->GetAmbient());
	glUniform1f(lightDiffuseLoc, camera_->GetLightSources()[0]->GetDiffuse());
	glUniform3f(lightColorLoc, camera_->GetLightSources()[0]->GetLightColor().x,
		camera_->GetLightSources()[0]->GetLightColor().y, camera_->GetLightSources()[0]->GetLightColor().z);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glBindVertexArray(vao);

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}