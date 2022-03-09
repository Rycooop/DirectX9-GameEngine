#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#endif

//Define Flexible Vertex Formats
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)
#define TEXTUREFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//Textures will be initialized through this class
#include "texture.h"


class Models
{
public:
	Models();

	void InitializeModels(LPDIRECT3DDEVICE9 devcon);

public:
	LPDIRECT3DVERTEXBUFFER9		vBuffer, terrainBuffer, pyramidBuffer;
	LPDIRECT3DINDEXBUFFER9		iBuffer, pyramidIndexBuffer;

	Texture* m_Textures;

	struct CUSTOMVERTEX
	{
		float x, y, z;
		D3DVECTOR NORMAL;
	};

private:

};

const static Texture::TEXTUREVERTEX terrainVertices[] =
{
	{-20.f, -10.f, -20.f, D3DCOLOR_XRGB(255, 255, 255), 0.f, 0.f, },
	{20.f, -10.f, -20.f, D3DCOLOR_XRGB(255, 255, 255), 1.f, 0.f, },
	{-20.f, -10.f, 20.f, D3DCOLOR_XRGB(255, 255, 255), 0.f, 1.f, },
	{20.f, -10.f, 20.f, D3DCOLOR_XRGB(255, 255, 255), 1.f, 1.f, },
};

const static Texture::TEXTUREVERTEX vertices[] =
{
{ -3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },    // side 1
{ 3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },
{ -3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f, },
{ 3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 1.0f, },

{ -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, -1.0f, },    // side 2
{ -3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, -1.0f, },
{ 3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, -1.0f, },
{ 3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, -1.0f, },

{ -3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },    // side 3
{ -3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },
{ 3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },
{ 3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },

{ -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 1.0f, },    // side 4
{ 3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },
{ -3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },
{ 3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0.0f, },

{ 3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },    // side 5
{ 3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },
{ 3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },
{ 3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },

{ -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },    // side 6
{ -3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },
{ -3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },
{ -3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0.0f, },
};

const static Models::CUSTOMVERTEX pyramidVertexBuffer[] =
{
	{-12.f, -3.f, -12.f, 0.f, 0.f, 0.f, },
	{-12.f, -3.f, -5.f, 1.f, 0.f, 0.f, },
	{-5.f, -3.f, -12.f, -1.f, 0.f, 0.f, },
	{-5.f, -3.f, -5.f, 0.f, 0.f, 0.f, },

	{-8.5f, 0.f, -8.5f, 0.f, 1.f, 0.f, }
};
