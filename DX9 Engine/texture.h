#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#endif


//All texturing done through here

class Texture
{
public:
	Texture();

	bool CreateTextures(LPDIRECT3DDEVICE9 devcon);

public:
	LPDIRECT3DTEXTURE9 brickTexture;

	struct TEXTUREVERTEX
	{
		FLOAT x, y, z;
		DWORD color;
		FLOAT tx, ty;
	};

};

