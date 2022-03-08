#include "engine.h"


GameEngine::GameEngine()
{
	this->DirectX = 0;
	this->Input = 0;
	this->m_hwnd = 0;
	this->m_hinstance = GetModuleHandle(NULL);
	this->windowWidth = 800;
	this->windowHeight = 600;
}

GameEngine::GameEngine(int width, int height)
{
	this->DirectX = 0;
	this->m_hwnd = 0;
	this->m_hinstance = GetModuleHandle(NULL);
	this->windowWidth = width;
	this->windowHeight = height;
}

bool GameEngine::Initialize()
{
	int screenWidth, screenHeight;
	bool result = this->InitializeWindow(this->m_hwnd, screenWidth, screenHeight);

	this->DirectX = new D3D;
	if (!DirectX)
		return false;

	if (!DirectX->Initialize(this->m_hwnd, this->windowWidth, this->windowHeight))
	{
		return false;
	}

	this->Input = new EngineInput;
	if (!Input)
		return false;

	if (!Input->Initialize())
	{
		return false;
	}
	
	return true;
}

void GameEngine::Run()
{
	bool running = true;
	MSG msg;

	while (running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			running = false;

		if (!this->Frame())
			running = false;
	}

	this->Shutdown();
}

bool GameEngine::Frame()
{
	//Handle key inputs
	if (Input->isKeyDown(VK_ESCAPE))
		return false;
	if (Input->isKeyDown(0x57))
		DirectX->camZ -= .5f;
	if (Input->isKeyDown(0x53))
		DirectX->camZ += .5f;
	if (Input->isKeyDown(VK_SPACE))
		DirectX->camY += .5f;
	if (Input->isKeyDown(VK_CONTROL))
		DirectX->camY -= .5f;

	DirectX->RenderFrame();
	return true;
}

bool GameEngine::Shutdown()
{
	delete DirectX;
	this->DirectX = 0;

	this->Input->Cleanup();
	delete Input;
	this->Input = 0;

	this->ShutdownWindow();

	return true;
}

bool GameEngine::InitializeWindow(HWND hwnd, int& screenWidth, int& screenHeight)
{
	ApplicationHandle = this;

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = this->m_hinstance;
	wc.lpszClassName = L"gameclass";
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(this->m_hinstance, IDC_CROSS);
	wc.lpfnWndProc = WindowProc;
	RegisterClassEx(&wc);

	int screenX = (GetSystemMetrics(SM_CXSCREEN) - this->windowWidth) / 2;
	int screenY = (GetSystemMetrics(SM_CYSCREEN) - this->windowHeight) / 2;

	this->m_hwnd = CreateWindowEx(NULL, L"gameclass", L"Game Engine", WS_POPUP, screenX, screenY, this->windowWidth, this->windowHeight, NULL, NULL, this->m_hinstance, NULL);

	ShowWindow(this->m_hwnd, SW_SHOW);
	screenWidth = this->windowWidth;
	screenHeight = this->windowHeight;

	return true;
}

bool GameEngine::ShutdownWindow()
{
	DestroyWindow(this->m_hwnd);
	m_hwnd = 0;

	return true;
}

LRESULT CALLBACK GameEngine::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			this->Input->keyDown((unsigned int)wParam);
			return 0;
		}
		case WM_KEYUP:
		{
			this->Input->keyUp((unsigned int)wParam);
			return 0;
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_QUIT:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return ApplicationHandle->MessageHandler(hwnd, message, wParam, lParam);
}