#include "texture.h"


Texture::Texture()
{
	this->brickTexture = 0;
	this->grassTexture = 0;
}

bool Texture::CreateTextures(LPDIRECT3DDEVICE9 devcon)
{
	HRESULT TextureCreated = D3DXCreateTextureFromFile(devcon, L"bricktex.PNG", &this->brickTexture);
	TextureCreated = D3DXCreateTextureFromFile(devcon, L"grasstex.JFIF", &this->grassTexture);

	return true;
}