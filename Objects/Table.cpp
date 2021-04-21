#include "stdafx.h"
#include "Objects/Table.h"
// class Table //////////////////////////////
// 상하좌우에 따른 테이블 정지 에님
// 상하좌우에 따른 테이블 넘어지는 에님
// 상하좌우에 따른 테이블 피격 에님 
// 다 부서질 경우 에님 

Table::Table (D3DXVECTOR2 position, D3DXVECTOR2 scale)
{
	animation = new Animation();

	Clip* clip;
	
	wstring spriteFile = Textures + L"Stage/table.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	

	// idle
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 24, 488, 56, 510), 0.1f);
		animation->AddClip(clip);
	}

	// push w
	{
		clip = new Clip(PlayMode::End);
		clip->RotationDegree(0.0f, 0.0f, 90.0f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 235, 242, 267, 262), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 252, 495, 283, 509), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 192, 425, 224, 445), 0.1f);
		animation->AddClip(clip);
	}

	// push s
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 282, 255, 314, 274), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 235, 242, 267, 262), 0.1f);
		animation->AddClip(clip);
	}
	Position(position);
	Scale(scale);
	animation->Play(0);
}

Table::~Table()
{
	SafeDelete(animation);
}

void Table::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{     
	Position(position);
	Scale(scale);
	animation->Update(V, P);
}

void Table::Render()
{
	animation->Render();
}
