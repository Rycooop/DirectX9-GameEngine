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
	this->InitLights();
	d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3ddev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	return true;
}

bool D3D::InitGraphics()
{
	VOID* pVoid;

	d3ddev->CreateVertexBuffer(20 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &pyramidBuffer, NULL);
	pyramidBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, pyramidVertexBuffer, sizeof(pyramidVertexBuffer));
	pyramidBuffer->Unlock();
	
	d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vBuffer,
		NULL);


	// lock v_buffer and load the vertices into it
	vBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vBuffer->Unlock();

	CUSTOMVERTEX terrainVertices[] =
	{
		{-20.f, -10.f, -20.f, 0.f, 1.f, 0.f, },
		{20.f, -10.f, -20.f, 0.f, 1.f, 0.f, },
		{-20.f, -10.f, 20.f, 0.f, 1.f, 0.f, },
		{20.f, -10.f, 20.f, 0.f, 1.f, 0.f, },
	};

	d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &terrainBuffer, NULL);
	terrainBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, terrainVertices, sizeof(terrainVertices));
	terrainBuffer->Unlock();

	short indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 5, 6,    // side 2
		6, 5, 7,
		8, 9, 10,    // side 3
		10, 9, 11,
		12, 13, 14,    // side 4
		14, 13, 15,
		16, 17, 18,    // side 5
		18, 17, 19,
		20, 21, 22,    // side 6
		22, 21, 23,
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

	short pIndices[] =
	{
		0, 1, 2,
		1, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
	};

	d3ddev->CreateIndexBuffer(15 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pyramidIndexBuffer, NULL);
	pyramidIndexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, pIndices, sizeof(pIndices));
	pyramidIndexBuffer->Unlock();

	return true;
}

void D3D::InitLights()
{
	D3DLIGHT9 light, light1;
	D3DMATERIAL9 material;

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
	light.Direction = D3DXVECTOR3(1.0f, -.3f, -1.0f);
	ZeroMemory(&light1, sizeof(D3DLIGHT9));
	light1.Type = D3DLIGHT_POINT;
	light1.Diffuse = D3DXCOLOR(0.f, 1.f, 0.5f, 1.0f);    // set the light's color
	light.Position = D3DXVECTOR3(20.0f, 0.0f, -1.0f);
	light.Range = 100.0f;    // a range of 100
	light.Attenuation0 = 0.0f;    // no constant inverse attenuation
	light.Attenuation1 = 0.125f;    // only .125 inverse attenuation
	light.Attenuation2 = 0.0f;

	//d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
	d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
	d3ddev->LightEnable(0, TRUE);    // turn on light #0

	ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

	d3ddev->SetMaterial(&material);
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


	static float index = 0.0f; index += 0.003f; 


	//Terrain
	D3DXMatrixRotationY(&matRotateX, 0);
	d3ddev->SetTransform(D3DTS_WORLD, &matRotateX);

	d3ddev->SetStreamSource(0, this->terrainBuffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	
	//Cube
	d3ddev->SetStreamSource(0, this->vBuffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(iBuffer);

	D3DXMatrixRotationY(&matRotateX, index);
	d3ddev->SetTransform(D3DTS_WORLD, &matRotateX);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);


	//Pyramid
	D3DXMatrixScaling(&matScale, index, index, index);
	D3DXMatrixRotationY(&matRotateX, 0);
	D3DXMatrixRotationX(&matRotateX, index);
	D3DXMATRIX finalMatrix = matScale * matRotateX;
	d3ddev->SetTransform(D3DTS_WORLD, &finalMatrix);

	d3ddev->SetStreamSource(0, this->pyramidBuffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(pyramidIndexBuffer);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 6);

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