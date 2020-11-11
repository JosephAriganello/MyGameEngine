#include "Core/Engine.h"
#include "../Game/Game1.h"

int main(int argc, char* args[]) {

	//Version 1
	//if (!Engine::GetInstance()->Initialization("GAME301 ENGINE", 800, 600)) {
	//	return 0;
	//}

	//Version 2
	Engine::GetInstance()->SetGameInterface(new Game1);
	Engine::GetInstance()->Initialization("GAME301 ENGINE", 800, 600);
	Engine::GetInstance()->Run();

	return 0;
}