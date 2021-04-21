#include "stdafx.h"
#include "Sprite.h"

//-----------------------------------------------------------------------------
// Sprite
//-----------------------------------------------------------------------------
Sprite::Sprite(wstring textureFile, wstring shaderFile)
{
	Initialize(textureFile, shaderFile, 0, 0, 0, 0);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float endX, float endY)
{
	Initialize(textureFile, shaderFile, 0, 0, endX, endY);
}

Sprite::Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	Initialize(textureFile, shaderFile, startX, startY, endX, endY);
}

void Sprite::Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY)
{
	bDrawBound = false;
	bDrawCollision = false;
	textureFile = spriteFile;

	shader = new Shader(shaderFile);
	boundShader = new Shader(Shaders + L"015_Bounding.fx");
	
	srv = Sprites::Load(spriteFile);
	shader->AsShaderResource("Map")->SetResource(srv);

	Position(0, 0);
	Scale(1, 1);
	Rotation(0, 0, 0);

	HRESULT hr;
	D3DX11_IMAGE_INFO info;
	hr = D3DX11GetImageInfoFromFile(spriteFile.c_str(), NULL, &info, NULL);
	assert(SUCCEEDED(hr));

	startX = (startX > 0) ? startX / (float)info.Width : 0.0f;
	startY = (startY > 0) ? startY / (float)info.Height : 0.0f;

	endX = (endX > 0) ? endX / (float)info.Width : 1.0f;
	endY = (endY > 0) ? endY / (float)info.Height : 1.0f;

	Vertex vertices[6];

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = D3DXVECTOR2(startX, endY);
	vertices[1].Uv = D3DXVECTOR2(startX, startY);
	vertices[2].Uv = D3DXVECTOR2(endX, endY);
	vertices[3].Uv = D3DXVECTOR2(endX, endY);
	vertices[4].Uv = D3DXVECTOR2(startX, startY);
	vertices[5].Uv = D3DXVECTOR2(endX, startY);
	
	float sizeX = (endX > 0) ? endX * (float)info.Width : (float)info.Width;
	sizeX -= startX * (float)info.Width;
	 
	float sizeY = (endY > 0) ? endY * (float)info.Height : (float)info.Height;
	sizeY -= startY * (float)info.Height;

	textureSize = D3DXVECTOR2(sizeX, sizeY);

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	CreateBound();
}

Sprite::~Sprite()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);

	Sprites::Remove(textureFile);
}


void Sprite::Update(D3DXMATRIX& V, D3DXMATRIX& P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	boundShader->AsMatrix("View")->SetMatrix(V);
	boundShader->AsMatrix("Projection")->SetMatrix(P);


	D3DXMATRIX S, R, T;

	D3DXMatrixScaling(&S, scale.x * textureSize.x, scale.y * textureSize.y, 1.0f);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x + scale.x * 0.5f, position.y + scale.y * 0.5f, 0.0f);

	world = S * R * T;

	shader->AsMatrix("World")->SetMatrix(world);
	boundShader->AsMatrix("World")->SetMatrix(world);
}

void Sprite::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->Draw(0, 0, 6);

	if (bDrawBound == true)
	{
		stride = sizeof(BoundVertex);
		offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &boundVertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		boundShader->Draw(0, bDrawCollision ? 1 : 0, 5);
	}
}

bool Sprite::Aabb(D3DXVECTOR2 & position)
{
	return Aabb(this, position);
}

bool Sprite::Aabb(Sprite * b)
{
	return Aabb(this, b);
}

bool Sprite::Obb(Sprite * b)
{
	return Obb(this,b);
}

bool Sprite::Aabb(Sprite * a, D3DXVECTOR2 & position)
{
	float xScale = a->scale.x * a->TextureSize().x * 0.5f;
	float yScale = a->scale.y * a->TextureSize().y * 0.5f;

	float left = a->position.x - xScale;
	float right = a->position.x + xScale;
	float bottom = a->position.y - yScale;
	float top = a->position.y + yScale;

	bool b = true;
	b &= position.x > left;
	b &= position.x <= right;
	b &= position.y > bottom;
	b &= position.y <= top;

	return b;
}

bool Sprite::Aabb(Sprite * a, Sprite * b)
{
	float xScale = a->scale.x * a->TextureSize().x * 0.5f;
	float yScale = a->scale.y * a->TextureSize().y * 0.5f;

	float leftA = a->position.x - xScale;
	float rightA = a->position.x + xScale;
	float bottomA = a->position.y - yScale;
	float topA = a->position.y + yScale;

	xScale = b->scale.x * b->TextureSize().x * 0.5f;
	yScale = b->scale.y * b->TextureSize().y * 0.5f;

	float leftB = b->position.x - xScale;
	float rightB = b->position.x + xScale;
	float bottomB = b->position.y - yScale;
	float topB = b->position.y + yScale;

	bool bCheck = true;
	bCheck &= leftA < rightB;
	bCheck &= topA > bottomB;
	bCheck &= rightA > leftB;
	bCheck &= bottomA < topB;

	return bCheck;
}

bool Sprite::Obb(Sprite * a, Sprite * b)
{
	ObbDesc obbA, obbB;
	float xScale, yScale;

	D3DXVECTOR2 lengthA = D3DXVECTOR2(a->world._11, a->world._22) * 0.5f;
	CreateObb(&obbA, a->position, a->world, lengthA);

	D3DXVECTOR2 lengthB = D3DXVECTOR2(b->world._11, b->world._22) * 0.5f;
	CreateObb(&obbB, b->position, b->world, lengthB);

	return CheckObb(obbA,obbB);
}

void Sprite::CreateObb(OUT ObbDesc * out, D3DXVECTOR2 & position, D3DXMATRIX & world, D3DXVECTOR2 & length)
{
	out->Position = position;

	out->Length[0] = length.x;
	out->Length[1] = length.y;

	out->Direction[0] = D3DXVECTOR2(world._11, world._12);
	out->Direction[1] = D3DXVECTOR2(world._21, world._22);

	D3DXVec2Normalize(&out->Direction[0], &out->Direction[0]);
	D3DXVec2Normalize(&out->Direction[1], &out->Direction[1]);
}

float Sprite::SeperateAxis(D3DXVECTOR2 & seperate, D3DXVECTOR2 & e1, D3DXVECTOR2 & e2)
{
	float r1 = fabsf(D3DXVec2Dot(&seperate, &e1));
	float r2 = fabsf(D3DXVec2Dot(&seperate, &e2));

	return r1 + r2;
}

bool Sprite::CheckObb(ObbDesc & obbA, ObbDesc & obbB)
{
	D3DXVECTOR2 nea1 = obbA.Direction[0], ea1 = nea1 * obbA.Length[0];
	D3DXVECTOR2 nea2 = obbA.Direction[1], ea2 = nea2 * obbA.Length[1];
	D3DXVECTOR2 neb1 = obbB.Direction[0], eb1 = neb1 * obbB.Length[0];
	D3DXVECTOR2 neb2 = obbB.Direction[1], eb2 = neb2 * obbB.Length[1];
	D3DXVECTOR2 direction = obbA.Position - obbB.Position;

	float lengthA = 0.0f, lengthB = 0.0f, length = 0.0f;

	lengthA = D3DXVec2Length(&ea1);
	lengthB = SeperateAxis(nea1, eb1, eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea1));
	if (length > lengthA + lengthB)
		return false;

	lengthA = D3DXVec2Length(&ea2);
	lengthB = SeperateAxis(nea2, eb1, eb2);
	length = fabsf(D3DXVec2Dot(&direction, &nea2));
	if (length > lengthA + lengthB)
		return false;


	lengthA = SeperateAxis(neb1, ea1, ea2);
	lengthB = D3DXVec2Length(&eb1);
	length = fabsf(D3DXVec2Dot(&direction, &neb1));
	if (length > lengthA + lengthB)
		return false;

	lengthA = SeperateAxis(neb2, ea1, ea2);
	lengthB = D3DXVec2Length(&eb2);
	length = fabsf(D3DXVec2Dot(&direction, &neb2));
	if (length > lengthA + lengthB)
		return false;

	return true;
}

void Sprite::CreateBound()
{
	BoundVertex vertices[5];

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	
	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(BoundVertex) * 5;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &boundVertexBuffer);
		assert(SUCCEEDED(hr));
	}
}

void Sprite::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Sprite::Position(D3DXVECTOR2 & vec)
{
	position = vec;
}

void Sprite::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Sprite::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;
}

void Sprite::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Sprite::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;
}

void Sprite::RotationDegree(float x, float y, float z)
{
	RotationDegree(D3DXVECTOR3(x, y, z));
}

void Sprite::RotationDegree(D3DXVECTOR3 & vec)
{
	vec.x = Math::ToRadian(vec.x);
	vec.y = Math::ToRadian(vec.y);
	vec.z = Math::ToRadian(vec.z);

	Rotation(vec);
}

D3DXVECTOR3 Sprite::RotationDegree()
{
	D3DXVECTOR3 vec;
	vec.x = Math::ToDegree(rotation.x);
	vec.y = Math::ToDegree(rotation.y);
	vec.z = Math::ToDegree(rotation.z);

	return vec;
}

//-----------------------------------------------------------------------------
// Sprites
//-----------------------------------------------------------------------------
map<wstring, Sprites::SpriteDesc> Sprites::spriteMap;

ID3D11ShaderResourceView * Sprites::Load(wstring file)
{
	if (spriteMap.count(file) > 0)
	{
		spriteMap[file].RefCount++;

		return spriteMap[file].SRV;
	}

	HRESULT hr;
	ID3D11ShaderResourceView* srv;
	hr = D3DX11CreateShaderResourceViewFromFile
	(
		Device, file.c_str(), NULL, NULL, &srv, NULL
	);
	assert(SUCCEEDED(hr));

	SpriteDesc desc;
	desc.RefCount++;
	desc.SRV = srv;
	spriteMap[file] = desc;


	return desc.SRV;
}

void Sprites::Remove(wstring file)
{
	UINT count = spriteMap.count(file);
	assert(count > 0);

	spriteMap[file].RefCount--;
	if (spriteMap[file].RefCount < 1)
	{
		SafeRelease(spriteMap[file].SRV);

		spriteMap.erase(file);
	}

}
