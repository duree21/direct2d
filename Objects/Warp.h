#pragma once
#include "Objects/Player.h"

class Warp
{
public:
	Warp(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Warp();

	void Update(D3DXMATRIX V, D3DXMATRIX & P);
	void Render();

	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() {return position;}

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void WarpPlayer(Player* player);

	Sprite* GetSprite();


private:
	Animation* animation;

	
	
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
};
