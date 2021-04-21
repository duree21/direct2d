#include "stdafx.h"
#include "Objects/Warp.h"

Warp::Warp(D3DXVECTOR2 position, D3DXVECTOR2 scale)
{
	animation = new Animation();
	Clip* clip;

	wstring spriteFile = Textures + L"Stage/warp.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 39 , 247, 251), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 301, 36, 516, 250), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 852, 36, 1067, 250), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 32, 318, 246, 535), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 304, 318, 518, 531), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 577, 318, 789, 528), 0.1f);
		animation->AddClip(clip);
	}

	Position(position);
	Scale(scale);
	animation->Play(0);
}

Warp::~Warp()
{
	SafeDelete(animation);
}

void Warp::Update(D3DXMATRIX V, D3DXMATRIX & P)
{
	animation->Update(V, P);
}

void Warp::Render()
{
	animation->Render();
}

void Warp::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Warp::Position(D3DXVECTOR2 & vec)
{
	position = vec;
	animation->Position(vec);
}

void Warp::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Warp::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;
	animation->Scale(scale);
}

void Warp::WarpPlayer(Player* player)
{
	player->Position(position);
}

Sprite * Warp::GetSprite()
{
	return animation->GetSprite();
}