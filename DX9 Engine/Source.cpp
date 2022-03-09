#include "engine.h"


//I made this engine as an intro into 3D game programming, material regarding Direct3D was mostly learned through
//DirectxTutorial.com so credit to the author. If there is anything inneficient or that you would change please submit
//a github request and ill take a look


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	//Credit our game engine with window size, default is 800 by 600 pixels through default constructor
	GameEngine* Engine = new GameEngine(800, 700);
	if (!Engine)
		return 0;

	if (!Engine->Initialize())
	{
		return 0;
	}

	//Loop that will run until the escape key is pressed
	Engine->Run();

	//Cleanup the engine
	Engine->Shutdown();
	delete Engine;
	Engine = 0;

	return 0;
}