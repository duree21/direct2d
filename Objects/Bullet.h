#pragma once
#include "Objects/Player.h"
#include "Objects/Weapon.h"
#include "Objects/Mnormal.h"
#include "Objects/Mself.h"
#include "Objects/Mspecial.h"

class Bullet
{
public:
	Bullet(D3DXVECTOR2 position, D3DXVECTOR2 scale, int selBullet);
	~Bullet();

	void Position(float x, float y) { Position(D3DXVECTOR2(x, y)); };
	void Position(D3DXVECTOR2 vec) { position = vec; bullet->Position(position); }
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y) { Scale(D3DXVECTOR2(x, y)); };
	void Scale(D3DXVECTOR2 vec) { scale = vec; bullet->Scale(scale); }
	D3DXVECTOR2 Scale() { return scale; }

	// this class utility
	void PlayerBulletUtil(Player* player, Weapon* weapon);
	void MnormalBulletUtil(Sprite* room, Mnormal* monster, Player* player);
	void MspecialBulletUtil(Sprite* room, Mspecial* monster, Player* player);

	// get function
	Sprite* GetBulletSprite() { return bullet; }
	Animation* GetBulletAnim() { return bulletAnim; }
	float GetBulletDamage() { return damage; }
	
	// update & render
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	enum eSelectBullet
	{
		PlayerBullet = 1, GigiBullet, SmileyBullet
	};
	int selBullet;

	Sprite* bullet;
	Animation* bulletAnim;
	Animation* HitEffect;

	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 scale;

	float damage;
};

