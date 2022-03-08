
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


class D3D
{
public:
	D3D();

	bool Initialize(HWND hwnd, int w, int h);
	bool InitGraphics();
	void InitLights();
	void RenderFrame();
	void Shutdown();

public:
	void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color);

	float camX, camY, camZ;

private:
	LPDIRECT3D9					d3d;
	LPDIRECT3DDEVICE9			d3ddev;
	LPDIRECT3DVERTEXBUFFER9		vBuffer, terrainBuffer, pyramidBuffer;
	LPDIRECT3DINDEXBUFFER9		iBuffer, pyramidIndexBuffer;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX matTranslate;
	D3DXMATRIX matRotateX;
	D3DXMATRIX matScale;

	HWND m_hwnd;
	int screenWidth, screenHeight;

public:
	struct CUSTOMVERTEX
	{
		float x, y, z;
		D3DVECTOR NORMAL;
	};

};

const static D3D::CUSTOMVERTEX vertices[] =
{
{ -3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },    // side 1
{ 3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
{ -3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },
{ 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f, },

{ -3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },    // side 2
{ -3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
{ 3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },
{ 3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f, },

{ -3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },    // side 3
{ -3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },
{ 3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f, },
{ 3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f, },

{ -3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },    // side 4
{ 3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f, },
{ -3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },
{ 3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f, },

{ 3.0f, -3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },    // side 5
{ 3.0f, 3.0f, -3.0f, 1.0f, 0.0f, 0.0f, },
{ 3.0f, -3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },
{ 3.0f, 3.0f, 3.0f, 1.0f, 0.0f, 0.0f, },

{ -3.0f, -3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },    // side 6
{ -3.0f, -3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
{ -3.0f, 3.0f, -3.0f, -1.0f, 0.0f, 0.0f, },
{ -3.0f, 3.0f, 3.0f, -1.0f, 0.0f, 0.0f, },
};

const static D3D::CUSTOMVERTEX pyramidVertexBuffer[] =
{
	{-12.f, -3.f, -12.f, 0.f, 0.f, 0.f, },
	{-12.f, -3.f, -5.f, 1.f, 0.f, 0.f, },
	{-5.f, -3.f, -12.f, -1.f, 0.f, 0.f, },
	{-5.f, -3.f, -5.f, 0.f, 0.f, 0.f, },

	{-8.5f, 0.f, -8.5f, 0.f, 1.f, 0.f, }
};
