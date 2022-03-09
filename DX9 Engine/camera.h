#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#endif


//Will deal with everything matrix/camera related as well as transformations

class Camera
{
public:
	Camera();

	bool Initialize(LPDIRECT3DDEVICE9, int, int);

	D3DXMATRIX getViewMatrix();
	D3DXMATRIX getProjectionMatrix();

	void UpdateCam();

private:
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

	D3DXVECTOR3 vCam, vLook, vUp;

public:
	float camX, camY, camZ;
};

