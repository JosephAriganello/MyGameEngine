#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 lightColor_){
	SetPosition(position_);
	SetAmbient(ambient_);
	SetDiffuse(diffuse_);
	SetLightColor(lightColor_);
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const {
	return position;
}

float LightSource::GetAmbient() const {
	return ambient;
}

float LightSource::GetDiffuse() const {
	return diffuse;
}

glm::vec3 LightSource::GetLightColor() const {
	return lightColor;
}

void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::SetAmbient(float ambient_) {
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_) {
	diffuse = diffuse_;
}

void LightSource::SetLightColor(glm::vec3 lightColor_) {
	lightColor = lightColor_;
}