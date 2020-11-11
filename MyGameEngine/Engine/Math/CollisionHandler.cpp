#include "CollisionHandler.h"
#include "../Core/Engine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler(){

}

CollisionHandler::~CollisionHandler(){
	delete scenePartition;
	scenePartition = nullptr;
}

CollisionHandler* CollisionHandler::GetInstance(){
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}

	return collisionInstance.get();
}

void CollisionHandler::Initialize(float worldSize_){
	previousCollisions.clear();
	previousCollisions.shrink_to_fit();

	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* go_){
	scenePartition->AddObject(go_);
}

void CollisionHandler::Update(glm::vec2 mousePos_, int buttonType_){
	Ray ray = CollisionDetection::ScreenToWorldRay(mousePos_, Engine::GetInstance()->GetScreenSize());
	GameObject* result = scenePartition->GetCollision(ray);

	for (auto c : previousCollisions) {
		if (result != c && c != nullptr)
			c->SetHit(false, buttonType_);
		
	}

	previousCollisions.clear();

	if (result)
		result->SetHit(true, buttonType_);
}
