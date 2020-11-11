#include "MouseEventListener.h"
#include "../Core/Engine.h"

Engine* MouseEventListener::engineInstance = nullptr;
int MouseEventListener::mouseX = 0;
int MouseEventListener::mouseY = 0;
int MouseEventListener::prevMouseX = 0;
int MouseEventListener::prevMouseY = 0;
bool MouseEventListener::firstUpdate = true;


MouseEventListener::~MouseEventListener(){
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(Engine * engine_){
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e){
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePosition();
		NotifyOfMousePressed(e.button.button);
	}
	else if (e.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePosition();
		NotifyOfMouseReleased(e.button.button);
	}
	else if (e.type == SDL_MOUSEMOTION) {
		UpdateMousePosition();
		NotifyOfMouseMoved();
	}
	else if (e.type == SDL_MOUSEWHEEL) {
		UpdateMousePosition();
		NotifyOfMouseScroll(e.wheel.y);
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_){
	if (engineInstance) {
		engineInstance->NotifyOfMousePressed(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_){
	if (engineInstance) {
		engineInstance->NotifyOfMouseReleased(mouseX, mouseY, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_){
	if (engineInstance) {
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

void MouseEventListener::NotifyOfMouseMoved(){
	if (engineInstance) {
		engineInstance->NotifyOfMouseMoved(mouseX, mouseY);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition(){
	return glm::vec2(prevMouseX, prevMouseY);
}

glm::vec2 MouseEventListener::GetMousePosition(){
	return glm::vec2(mouseX, mouseY);
}

glm::vec2 MouseEventListener::GetMouseOffset(){
	return glm::vec2(mouseX - prevMouseX, prevMouseY - mouseY);
}

void MouseEventListener::UpdateMousePosition(){
	int tmpX, tmpY;
	SDL_GetMouseState(&tmpX, &tmpY);
	tmpY = engineInstance->GetScreenSize().y - tmpY;

	if (firstUpdate) {
		prevMouseX = mouseX = tmpX;
		prevMouseY = mouseY = tmpY;
		firstUpdate = false;
	}
	else if (tmpX != mouseX && tmpY != mouseY) {
		prevMouseX = mouseX;
		prevMouseY = mouseY;
		mouseX = tmpX;
		mouseY = tmpY;
	}
}

