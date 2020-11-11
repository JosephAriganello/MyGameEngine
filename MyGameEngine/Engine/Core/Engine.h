#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "../Camera/Camera.h"
#include "../Events/EventListener.h"
#include "../Rendering/SceneGraph.h"
#include <memory>

class Engine
{
public:
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&) = delete;

	bool Initialization(std::string name_, int width_, int height_);
	bool GetIsRunning();
	void SetGameInterface(GameInterface* gameInterface_);
	void Run();
	static Engine* GetInstance();

	glm::vec2 GetScreenSize() const;
	void NotifyOfMousePressed(int x_, int y_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMoved(int x_, int y_);
	void NotifyOfMouseScroll(int y_);

	void ExitGame();

private:

	Engine();
	~Engine();

	static std::unique_ptr<Engine> engineInstance;
	friend std::default_delete<Engine>;

	void Update(const float deltaTime);
	void Render();
	void Shutdown();

	Window* window;
	Timer timer;
	GameInterface* gameInterface;
	bool isRunning;
	unsigned int fps;
};

#endif //ENGINE_H