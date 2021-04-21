#pragma once
#include "Objects/Player.h"
#include "Objects/Mnormal.h"
#include "Objects/Mspecial.h"
#include "Objects/Boss.h"

class Weapon 
{
public:
	Weapon(D3DXVECTOR2 position, int selWeapon);
	~Weapon();

	// position & scale
	void PositionWeapon(float x, float y)  { PositionWeapon(D3DXVECTOR2(x, y)); };
	void PositionWeapon(D3DXVECTOR2 vec) { positionWeapon = vec; weapon->Position(positionWeapon); }
	D3DXVECTOR2 PositionWeapon() { return positionWeapon; }
	void ScaleWeapon(float x, float y) { ScaleWeapon(D3DXVECTOR2(x, y)); };
	void ScaleWeapon(D3DXVECTOR2 vec) { scaleWeapon = vec; weapon->Scale(scaleWeapon); }
	D3DXVECTOR2 ScaleWeapon() { return scaleWeapon; }
	
	void PositionHand(float x, float y) { PositionHand(D3DXVECTOR2(x, y)); };
	void PositionHand(D3DXVECTOR2 vec) { positionHand = vec; hand->Position(positionHand); }
	D3DXVECTOR2 PositionHand() { return positionHand; }
	void ScaleHand(float x, float y) { ScaleHand(D3DXVECTOR2(x, y)); };
	void ScaleHand(D3DXVECTOR2 vec) { scaleHand = vec; hand->Scale(scaleHand); }
	D3DXVECTOR2 ScaleHand() { return scaleHand; }
	
	// get function
	Sprite* GetWeaponSprite() { return weapon; }

	// set function

	// this class utility
	void PlayerWeaponUtil(Player* player);
	void MnormalWeaponUtil(Player* player, Mnormal* monster);
	void MspecialWeaponUtil(Player* player, Mspecial* monster);
	void BossWeaponUtil(Player* player, Boss* boss);

	// update & render
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
	
private:
	enum eSelectWeapon
	{
		PlayerWeapon = 1, MnormalWeapon, MspecialWeapon, BossWeapon
	};

	Sprite* weapon;
	Sprite* hand;

	D3DXVECTOR2 positionWeapon;
	D3DXVECTOR2 positionHand;
	D3DXVECTOR2 scaleWeapon;
	D3DXVECTOR2 scaleHand;
};

