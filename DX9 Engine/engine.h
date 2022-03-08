#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "directx.h"
#include "input.h"


class GameEngine
{
public:
	GameEngine();
	GameEngine(int width, int height);

	bool Initialize();
	void Run();
	bool Frame();
	bool Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool InitializeWindow(HWND hwnd, int& screenWidth, int& screenHeight);
	bool ShutdownWindow();

private:
	D3D* DirectX;
	EngineInput* Input;

	HWND m_hwnd;
	HINSTANCE m_hinstance;
	int windowWidth, windowHeight;

};

static GameEngine* ApplicationHandle = 0;
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);