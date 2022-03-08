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

bool D3D::Initialize(HWND hwnd, int w, int h)
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
		return false;

	this->InitGraphics();
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	return true;
}

bool D3D::InitGraphics()
{
	CUSTOMVERTEX vertices[] =
	{
		 { -3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255), },    // vertex 0
		{ 3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 0), },     // vertex 1
		{ -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 0, 0), },   // 2
		{ 3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 255), },  // 3
		{ -3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(0, 0, 255), },     // ...
		{ 3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 0, 0), },
		{ -3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 255), },
	};

	// create a vertex buffer interface called v_buffer
	d3ddev->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vBuffer,
		NULL);

	VOID* pVoid;    // a void pointer

	// lock v_buffer and load the vertices into it
	vBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vBuffer->Unlock();

	CUSTOMVERTEX terrainVertices[] =
	{
		{-20.f, 0.f, -20.f, D3DCOLOR_XRGB(100, 200, 100), },
		{20.f, 0.f, -20.f, D3DCOLOR_XRGB(100, 200, 100), },
		{-20.f, 0.f, 20.f, D3DCOLOR_XRGB(100, 200, 100), },
		{20.f, 0.f, 20.f, D3DCOLOR_XRGB(100, 200, 100), },
	};

	VOID* tpVoid;
	d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &terrainBuffer, NULL);
	terrainBuffer->Lock(0, 0, (void**)&tpVoid, 0);
	memcpy(tpVoid, terrainVertices, sizeof(terrainVertices));
	terrainBuffer->Unlock();

	short indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	// create an index buffer interface called i_buffer
	d3ddev->CreateIndexBuffer(36 * sizeof(short),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&iBuffer,
		NULL);

	// lock i_buffer and load the indices into it
	iBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	iBuffer->Unlock();

	return true;
}

void D3D::RenderFrame()
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->BeginScene();

	d3ddev->SetFVF(CUSTOMFVF);

	D3DXVECTOR3 vCam = D3DXVECTOR3(this->camX, this->camY, this->camZ);
	D3DXVECTOR3 vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix,
		&vCam,    // the camera position
		&vLook,    // the look-at position
		&vUp);    // the up direction

	d3ddev->SetTransform(D3DTS_VIEW, &viewMatrix);    // set the view transform to matView


	D3DXMatrixPerspectiveFovLH(&projectionMatrix,
		D3DXToRadian(45),    // the horizontal field of view
		(FLOAT)screenWidth / (FLOAT)screenHeight, // aspect ratio
		1.0f,    // the near view-plane
		100.0f);    // the far view-plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &projectionMatrix);    // set the projection


	static float index = 0.0f; index += 0.05f;    // an ever-increasing float value
	// build a matrix to rotate the model based on the increasing float value
	D3DXMatrixRotationY(&matRotateX, 0);
	d3ddev->SetTransform(D3DTS_WORLD, &matRotateX);


	d3ddev->SetStreamSource(0, this->terrainBuffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// select the vertex buffer to display and draw
	d3ddev->SetStreamSource(0, this->vBuffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(iBuffer);

	D3DXMatrixRotationY(&matRotateX, index);
	d3ddev->SetTransform(D3DTS_WORLD, &matRotateX);
	
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void D3D::Shutdown()
{
	vBuffer->Release();
	iBuffer->Release();
	d3ddev->Release();
	d3d->Release();
}

void D3D::DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + w, y + h };
	d3ddev->Clear(1, &rect, D3DCLEAR_TARGET, color, 1.0f, 0);
}