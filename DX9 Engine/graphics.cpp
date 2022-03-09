#include "graphics.h"


EngineGraphics::EngineGraphics()
{
	this->DirectX = 0;
	this->Lighting = 0;
	this->Cam = 0;
	this->g_devcon = 0;
	this->g_models = 0;
	this->g_hwnd = 0;
	this->windowWidth = 0;
	this->windowHeight = 0;
}

bool EngineGraphics::InitializeGraphics(HWND hwnd, int w, int h)
{
	this->g_hwnd = hwnd;
	this->windowWidth = w;
	this->windowHeight = h;

	this->DirectX = new D3D();
	if (!DirectX)
		return false;

	this->g_devcon = this->DirectX->Initialize(hwnd, w, h);

	if (!this->g_devcon)
		return false;

	this->g_models = new Models();
	if (!g_models)
		return false;

	g_models->InitializeModels(g_devcon);

	this->Cam = new Camera();
	Cam->Initialize(g_devcon, this->windowWidth, this->windowHeight);

	this->Lighting = new Lights();
	if (!Lighting)
		return false;

	Lighting->InitLights(this->g_devcon);
	
	return true;
}

void EngineGraphics::Shutdown()
{
	delete this->g_models;
	this->g_models = 0;

	this->Lighting->CleanupLights();
	delete this->Lighting;
	this->Lighting = 0;

	delete this->Cam;
	this->Cam = 0;

	this->DirectX->Shutdown();
	delete DirectX;
	DirectX = 0;
}

bool EngineGraphics::Render()
{
	//For a rotating cube
	static float index = 0.0f; index += 0.003f;

	DirectX->BeginScene();
	g_devcon->SetFVF(CUSTOMFVF);

	//Update the camera and transform the 3D environment
	Cam->UpdateCam();
	this->viewMatrix = Cam->getViewMatrix();
	this->projectionMatrix = Cam->getProjectionMatrix();
	g_devcon->SetTransform(D3DTS_VIEW, &this->viewMatrix);
	g_devcon->SetTransform(D3DTS_PROJECTION, &this->projectionMatrix);

	//Terrain
	g_devcon->SetStreamSource(0, g_models->terrainBuffer, 0, sizeof(Models::CUSTOMVERTEX));
	g_devcon->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Cube
	g_devcon->SetFVF(TEXTUREFVF);
	g_devcon->SetTexture(0, g_models->m_Textures->brickTexture);

	//Rotate cube
	D3DXMATRIX matRotate;
	D3DXMatrixRotationY(&matRotate, index);
	g_devcon->SetTransform(D3DTS_WORLD, &matRotate);

	g_devcon->SetStreamSource(0, g_models->vBuffer, 0, sizeof(Texture::TEXTUREVERTEX));
	g_devcon->SetIndices(g_models->iBuffer);
	g_devcon->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//Reset texture and rotation
	D3DXMatrixRotationY(&matRotate, 0);
	g_devcon->SetTransform(D3DTS_WORLD, &matRotate);
	g_devcon->SetTexture(0, NULL);
	g_devcon->SetFVF(CUSTOMFVF);

	//Pyramid
	g_devcon->SetStreamSource(0, g_models->pyramidBuffer, 0, sizeof(Models::CUSTOMVERTEX));
	g_devcon->SetIndices(g_models->pyramidIndexBuffer);
	g_devcon->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 6);

	DirectX->EndScene();
	return true;
}

