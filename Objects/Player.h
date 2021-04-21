#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing {
public:
	Player();
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;

	virtual void Position(float x, float y) { Position(D3DXVECTOR2(x, y)); }
	virtual void Position(D3DXVECTOR2 vec);
	D3DXVECTOR2 Position() { return animation->Position(); }
	
	// get function
	Sprite* GetSprite();
	Animation* GetPlayer() { return animation; }
	float GetHp() { return hp; }

	// set function
	void SetHp(float hp) { this->hp = hp; }

	// update & render
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	Animation* animation;
	Animation* eWAnimation;
	Animation* eSAnimation;
	
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 focusOffset;

	D3DXVECTOR2 mouseWorld;
	D3DXVECTOR2 mouseScreen;
	D3DXVECTOR2 animWorld;
	D3DXVECTOR2 animScreen;
	
	float hp;
	float moveSpeed;
};