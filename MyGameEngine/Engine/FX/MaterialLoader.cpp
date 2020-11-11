#include "MaterialLoader.h"

void MaterialLoader::LoadMaterial(std::string file_) {
	std::ifstream in(file_, std::ios::in);

	if (!in) {
		Debug::Error("Cannot open MTL file" + file_, __FILE__, __LINE__);
		return;
	}

	Material m = Material();
	std::string matName = "";
	std::string line;

	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(matName, m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
		}
		//Ns = shininess
		else if (line.substr(0, 4) == "\tNs ") {
			std::istringstream Ns(line.substr(4));
			Ns >> m.shininess;
		}

		//d = transparency
		else if (line.substr(0, 3) == "\td ") {
			std::istringstream d(line.substr(3));
			d >> m.transparency;
		}

		//Ka = ambient
		else if (line.substr(0, 4) == "\tKa ") {
			std::istringstream Ka(line.substr(4));
			Ka >> m.ambient.x >> m.ambient.y >> m.ambient.z;
		}

		//Kd = diffuse
		else if (line.substr(0, 4) == "\tKd ") {
			std::istringstream Kd(line.substr(4));
			Kd >> m.diffuse.x >> m.diffuse.y >> m.diffuse.y;
		}

		//Ks = specular
		else if (line.substr(0, 4) == "\tKs ") {
			std::istringstream Ks(line.substr(4));
			Ks >> m.specular.x >> m.specular.y >> m.specular.z;
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(matName, m);
	}
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}