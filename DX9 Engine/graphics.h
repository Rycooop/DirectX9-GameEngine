//Create a Pre-processor directive
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "directx.h"
#include "lights.h"
#include "model.h"
#include "camera.h"


//Everything visual will be done through this class

class EngineGraphics
{
public:
	EngineGraphics();

	bool InitializeGraphics(HWND, int, int);
	void Shutdown();
	bool Render();

public:
	D3D* DirectX;
	Camera* Cam;

private:
	Lights* Lighting;
	Models* g_models;

	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;

	LPDIRECT3DDEVICE9 g_devcon;
	HWND g_hwnd;
	int windowWidth, windowHeight;
};

#endif