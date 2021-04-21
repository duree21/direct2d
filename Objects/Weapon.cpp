#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Weapon.h"

Weapon::Weapon(D3DXVECTOR2 position, int selWeapon)
{
	wstring spriteFileWeapon = Textures + L"weapon/weapon.png";
	wstring spriteFileHand = Textures + L"player/player.png";
	
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	
	switch (selWeapon)
	{
	case Weapon::PlayerWeapon:
	{
		weapon = new Sprite(spriteFileWeapon, shaderFile, 340, 684, 359, 695);
		weapon->Position(position);
		weapon->Scale(2, 2);

		hand = new Sprite(spriteFileHand, shaderFile, 389, 981, 393, 985);
		hand->Position(weapon->Position().x, weapon->Position().y);
		hand->Scale(3, 3);
	}
		break;
	case Weapon::MnormalWeapon:
	{
		weapon = new Sprite(spriteFileWeapon, shaderFile, 710, 703, 736, 712);
		weapon->Position(position);
		weapon->Scale(2, 2);

		hand = new Sprite(spriteFileHand, shaderFile, 389, 981, 393, 985);
		hand->Position(weapon->Position().x, weapon->Position().y);
		hand->Scale(3, 3);
	}
		break;
	case Weapon::MspecialWeapon:
		break;
	case Weapon::BossWeapon:
		break;
	default:
		break;
	}
}

Weapon::~Weapon()
{
	SafeDelete(weapon);
	SafeDelete(hand);
}

void Weapon::Update(D3DXMATRIX & V, D3DXMATRIX & P) 
{
	weapon->Update(V, P);
	hand->Update(V, P);

	positionWeapon = weapon->Position();
	scaleWeapon = weapon->Scale();
	positionHand = hand->Position();
	scaleHand = hand->Scale();
}

void Weapon::Render()
{
	weapon->Render();
	hand->Render();
}

void Weapon::PlayerWeaponUtil(Player* player)
{
	D3DXVECTOR2 mouse = Mouse->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;

	D3DXVECTOR2 mouseScreen = Mouse->Position();
	D3DXVECTOR2 mouseWorld = mouse + player->GetPlayer()->Position();
	D3DXVECTOR2	playerWorld = player->GetPlayer()->Position();
	D3DXVECTOR2 playerScreen = D3DXVECTOR2((float)Width * 0.5f, (float)Height * 0.5f);

	D3DXVECTOR2 mVec = playerWorld - mouseWorld;
	D3DXVec2Length(&mVec);
	D3DXVECTOR2 mVecN;
	D3DXVec2Normalize(&mVecN, &mVec);

	//// 플레이어 벡터
	//D3DXVECTOR2 pVec = animWorld - (animWorld - D3DXVECTOR2(0.0f, 2500.0f)); // ?
	//D3DXVec2Length(&pVec);
	//D3DXVECTOR2 pVecN;
	//D3DXVec2Normalize(&pVecN, &pVec);
	//
	//float theta = D3DXVec2Dot(&mVecN, &pVecN);
	//float forDegree = acos(theta);
	//float weaponRotation = forDegree * (180.0f / M_PI);

	if (playerScreen.x > mouseScreen.x)	// 왼쪽 
	{
		hand->Position(player->GetPlayer()->Position().x - player->GetPlayer()->TextureSize().x * 0.5f * player->GetPlayer()->Scale().x /*- hand->TextureSize().x * 0.5f * hand->Scale().x*/, player->GetPlayer()->Position().y - hand->TextureSize().y * hand->Scale().y);
		weapon->RotationDegree(0.0f, 0.0f, 0.0f);
		weapon->Position(player->GetPlayer()->Position().x - player->GetPlayer()->TextureSize().x * 0.5f * player->GetPlayer()->Scale().x - hand->TextureSize().x * 1.7f * hand->Scale().x, player->GetPlayer()->Position().y /*+ hand->TextureSize().y * hand->Scale().y*/);
	}
	else if (playerScreen.x < mouseScreen.x)	// 오른쪽
	{
		hand->Position(player->GetPlayer()->Position().x + player->GetPlayer()->TextureSize().x * 0.5f * player->GetPlayer()->Scale().x /*+ hand->TextureSize().x * 0.5f * hand->Scale().x*/, player->GetPlayer()->Position().y - hand->TextureSize().y * hand->Scale().y);
		weapon->RotationDegree(0.0f, 180.0f, 0.0f);
		weapon->Position(player->GetPlayer()->Position().x + player->GetPlayer()->TextureSize().x * 0.5f * player->GetPlayer()->Scale().x + hand->TextureSize().x * 1.7f * hand->Scale().x , player->GetPlayer()->Position().y /*+ hand->TextureSize().y * hand->Scale().y*/);
	}
}

void Weapon::MnormalWeaponUtil(Player* player, Mnormal * monster)
{
	D3DXVECTOR2 monsterWorld = monster->Position();
	D3DXVECTOR2 playerWorld = player->Position();

	D3DXVECTOR2 mPVec = monsterWorld - playerWorld;
	D3DXVec2Normalize(&mPVec, &mPVec); // 벡터의 크기는 정규화, 벡터의 방향정보만 남음

	if (mPVec.x > 0.0f) // 좌표 위치 공부
	{
		hand->Position(monster->GetMnormal()->Position().x - monster->GetMnormal()->TextureSize().x * 0.5f * monster->GetMnormal()->Scale().x /*- hand->TextureSize().x * 0.5f * hand->Scale().x*/, monster->GetMnormal()->Position().y - hand->TextureSize().y * hand->Scale().y);
		weapon->RotationDegree(0.0f, 0.0f, 0.0f);
		weapon->Position(monster->GetMnormal()->Position().x - monster->GetMnormal()->TextureSize().x * 0.5f * monster->GetMnormal()->Scale().x - hand->TextureSize().x * 1.7f * hand->Scale().x, monster->GetMnormal()->Position().y /*+ hand->TextureSize().y * hand->Scale().y*/);
	}
	else if (mPVec.x < 0.0f)
	{
		hand->Position(monster->GetMnormal()->Position().x + monster->GetMnormal()->TextureSize().x * 0.5f * monster->GetMnormal()->Scale().x /*+ hand->TextureSize().x * 0.5f * hand->Scale().x*/, monster->GetMnormal()->Position().y - hand->TextureSize().y * hand->Scale().y);
		weapon->RotationDegree(0.0f, 180.0f, 0.0f);
		weapon->Position(monster->GetMnormal()->Position().x + monster->GetMnormal()->TextureSize().x * 0.5f * monster->GetMnormal()->Scale().x + hand->TextureSize().x * 1.7f * hand->Scale().x, monster->GetMnormal()->Position().y /*+ hand->TextureSize().y * hand->Scale().y*/);
	}
}

void Weapon::MspecialWeaponUtil(Player* player, Mspecial* monster)
{
}

void Weapon::BossWeaponUtil(Player* player, Boss* boss)
{
}


