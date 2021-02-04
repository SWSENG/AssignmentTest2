#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

class Sprite
{
public:
	Sprite();
	Sprite(std::wstring fileName, float spriteXPos, float spriteYPos, float spriteWidth, float spriteHeight);

private:
	void SetSRVPointer(std::wstring fileName);
	void CalculateMatWorld();
	void CopyToSpritePool();
	ID3D10ShaderResourceView* CreateSRV(std::wstring fileName);
	ID3D10Texture2D* texture;
	float width;
	float height;
	float xPos;
	float yPos;
	D3DXMATRIX matWorld;

	static int numberOfSprites;
	static std::wstring SRVNames[5];
	static ID3D10ShaderResourceView* SRVPointers[5];
	ID3D10ShaderResourceView* pSpriteSRV;
};

int Sprite::numberOfSprites = 0;
std::wstring Sprite::SRVNames[5];
ID3D10ShaderResourceView* Sprite::SRVPointers[5];

Sprite::Sprite()
{
	width = 0;
	height = 0;
	xPos = 0;
	yPos = 0;
	pSpriteSRV = NULL;
}

Sprite::Sprite(std::wstring fileName, float spriteXPos, float spriteYPos, float spriteWidth, float spriteHeight)
{
	width = spriteWidth;
	height = spriteHeight;
	xPos = spriteXPos;
	yPos = spriteYPos;
	SetSRVPointer(fileName);
	CopyToSpritePool();
}

void Sprite::SetSRVPointer(std::wstring fileName)
{
	bool didNotFindSRV = true;

	// Look for a SRV in RVPointers by comparing fileName to RVNames
	for (int i = 0; i < numberOfSprites; ++i)
	{
		if (fileName.compare(SRVNames[i]) == 0)
		{
			pSpriteSRV = SRVPointers[i];
			didNotFindSRV = false;
		}
	}

	// If no SRV is found, create one
	if (didNotFindSRV)
		pSpriteSRV = CreateSRV(fileName);
}

void Sprite::CalculateMatWorld()
{
	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, xPos, (windowHeight - yPos), 0.1f);

	D3DXMATRIX matScaling;
	D3DXMatrixScaling(&matScaling, width, height, 1.0f);

	matWorld = (matScaling * matTranslation);
}

void Sprite::CopyToSpritePool()
{
	CalculateMatWorld();
	spritePool[numActiveSprites].pTexture = pSpriteSRV;
	spritePool[numActiveSprites].TexCoord.x = 0;
	spritePool[numActiveSprites].TexCoord.y = 0;
	spritePool[numActiveSprites].TexSize.x = 1.0f;
	spritePool[numActiveSprites].TexSize.y = 1.0f;
	spritePool[numActiveSprites].TextureIndex = 0;
	spritePool[numActiveSprites].ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	spritePool[numActiveSprites].matWorld = matWorld;
	numActiveSprites++;
}

ID3D10ShaderResourceView* Sprite::CreateSRV(std::wstring fileName)
{
	ID3D10ShaderResourceView* SRV = NULL;
	ID3D10Texture2D* texture = GetTexture2DFromFile(fileName.c_str());

	if (texture != NULL)
	{
		D3D10_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);
		D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		ZeroMemory(&SRVDesc, sizeof(SRVDesc));
		SRVDesc.Format = desc.Format;
		SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = desc.MipLevels;

		pD3DDevice->CreateShaderResourceView(texture, &SRVDesc, &SRV);
	}

	else
		MessageBox(NULL, L"Texture not valid", L"", MB_OK);

	texture->Release();


	SRVPointers[numberOfSprites] = SRV;
	SRVNames[numberOfSprites] = fileName;
	numberOfSprites++;

	return SRV;
}