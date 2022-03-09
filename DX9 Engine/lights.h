#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#endif


//All lighting for the scenes done and initialized here

class Lights
{
public:
	Lights();

	void InitLights(LPDIRECT3DDEVICE9 devcon);
	void UpdateLights();
	void CleanupLights();

private:
	LPDIRECT3DDEVICE9 devcon;
	D3DLIGHT9 light, light1;

};


