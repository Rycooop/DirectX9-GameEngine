#include "texture.h"


Texture::Texture()
{
	this->brickTexture = 0;
}

bool Texture::CreateTextures(LPDIRECT3DDEVICE9 devcon)
{
	HRESULT TextureCreated = D3DXCreateTextureFromFile(devcon, L"bricktex.PNG", &this->brickTexture);

	return true;
}