#pragma once
#include "Objects/Player.h"

class Mnormal
{
public:
	Mnormal(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Mnormal();

	// position 변수, scale 변수를 따로 할당 해주어야 하는 문제, 반환값을 위해서 함수를 따로 선언 및 정의
	void Position(float x, float y) { Position(D3DXVECTOR2(x, y)); }
	void Position(D3DXVECTOR2& vec) { position = vec; animation->Position(position); }
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y) { Scale(D3DXVECTOR2(x, y)); }
	void Scale(D3DXVECTOR2& vec) { scale = vec; animation->Scale(scale); }
	D3DXVECTOR2 Scale() { return scale; }

	// this class utility
	void MnormalUtil(Sprite* room, Player* player);

	// get function
	Sprite* GetMnormal() { return animation->GetSprite(); }
	float GetHp() { return hp; }

	// set function
	void SetHp(float hp) { this->hp = hp; }

	// update & render
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	Animation* animation;
	
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 velocity;
	float hp;

};

