#include "directx.h"


D3D::D3D()
{
	this->m_hwnd = 0;
	this->camX = 0.f;
	this->camY = 8.f;
	this->camZ = 25.f;
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->d3d = nullptr;
	this->d3ddev = nullptr;
}

LPDIRECT3DDEVICE9 D3D::Initialize(HWND hwnd, int w, int h)
{
	this->m_hwnd = hwnd;
	this->screenWidth = w;
	this->screenHeight = h;

	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = this->m_hwnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = w;
	d3dpp.BackBufferHeight = h;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	
	HRESULT DevCreated = this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	if (DevCreated != S_OK)
		return 0;

	this->InitGraphics();
	
	return d3ddev;
}

bool D3D::InitGraphics()
{
	//settings for the 3D environment
	d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(100, 100, 100));
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	return true;
}

void D3D::BeginScene()
{
	//Setup back buffer to be ready for drawing
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->BeginScene();
}

void D3D::EndScene()
{
	//Present the back buffer
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void D3D::Shutdown()
{
	d3ddev->Release();
	d3d->Release();
}

