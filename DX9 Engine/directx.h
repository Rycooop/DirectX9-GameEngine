#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

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
	void RenderFrame();
	void Shutdown();

public:
	void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color);

	float camX, camY, camZ;

private:
	LPDIRECT3D9					d3d;
	LPDIRECT3DDEVICE9			d3ddev;
	LPDIRECT3DVERTEXBUFFER9		vBuffer, terrainBuffer;
	LPDIRECT3DINDEXBUFFER9		iBuffer;
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
		DWORD color;
	};
};

