#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#endif

//Hold everything needed for DirectX9

class D3D
{
public:
	D3D();

	LPDIRECT3DDEVICE9 Initialize(HWND hwnd, int w, int h);
	bool InitGraphics();
	void BeginScene();
	void EndScene();
	void Shutdown();

public:
	float camX, camY, camZ;

public:
	LPDIRECT3D9					d3d;
	LPDIRECT3DDEVICE9			d3ddev;

	HWND m_hwnd;
	int screenWidth, screenHeight;

public:
	

};


