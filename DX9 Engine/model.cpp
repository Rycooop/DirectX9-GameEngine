#include "model.h"


Models::Models()
{
	this->m_Textures = 0;
}

void Models::InitializeModels(LPDIRECT3DDEVICE9 devcon)
{
	VOID* pVoid;

	//Create all vertex buffers for our 3D objects
	devcon->CreateVertexBuffer(20 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &pyramidBuffer, NULL);
	pyramidBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, pyramidVertexBuffer, sizeof(pyramidVertexBuffer));
	pyramidBuffer->Unlock();

	devcon->CreateVertexBuffer(24 * sizeof(Texture::TEXTUREVERTEX), 0, TEXTUREFVF, D3DPOOL_MANAGED, &vBuffer, NULL);
	vBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	vBuffer->Unlock();

	devcon->CreateVertexBuffer(4 * sizeof(Texture::TEXTUREVERTEX), 0, TEXTUREFVF, D3DPOOL_MANAGED, &terrainBuffer, NULL);
	terrainBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, terrainVertices, sizeof(terrainVertices));
	terrainBuffer->Unlock();

	//Create index buffers
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

	devcon->CreateIndexBuffer(36 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &iBuffer, NULL);
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

	devcon->CreateIndexBuffer(15 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pyramidIndexBuffer, NULL);
	pyramidIndexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, pIndices, sizeof(pIndices));
	pyramidIndexBuffer->Unlock();

	m_Textures = new Texture();
	if (!m_Textures)
		return;

	m_Textures->CreateTextures(devcon);
}