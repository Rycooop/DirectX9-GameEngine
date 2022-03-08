#include "engine.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	GameEngine* Engine = new GameEngine(600, 600);
	if (!Engine)
		return 0;

	if (!Engine->Initialize())
	{
		return 0;
	}

	Engine->Run();

	Engine->Shutdown();
	delete Engine;
	Engine = 0;

	return 0;
}