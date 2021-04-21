#include "stdafx.h"
#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
//////////////////////////////////////////////////////////////////////
// move ¼Õ ¾ø´Â °É·Î ¹Ù²ã¾ßµÊ
Player::Player()
{
}

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale) :
	focusOffset(-180, -120), hp(120.0f), moveSpeed(275.0f)
{
	animation = new Animation();
	eWAnimation = new Animation();
	eSAnimation = new Animation();

	wstring spriteFile = Textures + L"player/player.png";
	wstring eWSpriteFile = Textures + L"Effect/Eplayer_foot.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	Clip* eWClip;
	Clip* eSClip;
	
	// animation////////////////////////////////////////////////////////////////////////////////////////
	{
		// Move////////////////////////////////////////////////////////////////////////////////////////
		// bMoveW 0
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 303, 521, 319, 541), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 87, 520, 104, 540), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 494, 48, 514), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 357, 521, 373, 541), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 222, 774, 238, 794), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 249, 524, 264, 544), 0.1f);
			animation->AddClip(clip);
		}

		// bMoveS 1
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 6, 491, 21, 511), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 141, 494, 157, 514), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 168, 496, 183, 517), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 5, 519, 21, 539), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 167, 522, 182, 542), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 276, 496, 291, 516), 0.1f);
			animation->AddClip(clip);
		}

		// bMoveA & bMoveD & bMoveSA & bMoveSD 2
		{		
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 87, 855, 101, 874), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 195, 886, 209, 905), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 142, 861, 155, 880), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 417, 913, 430, 932), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 412, 887, 425, 906), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 444, 916, 456, 935), 0.1f);
			animation->AddClip(clip);
		}

		// bMoveWA & bMoveWD 3
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 201, 916, 214, 935), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 254, 913, 268, 933), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 227, 915, 241, 933), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 60, 885, 74, 906), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 88, 912, 102, 932), 0.1f);
			animation->AddClip(clip);
		}

		// Look ////////////////////////////////////////////////////////////////////////////////////////
		// bLookW 4
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 195, 720, 210, 740), 0.3f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 222, 721, 237, 740), 0.3f);
			animation->AddClip(clip);
		}
		
		// bLookS 5
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 87, 688, 102, 711), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 6, 690, 21, 711), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 60, 691, 75, 711), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 141, 693, 156, 713), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 60, 691, 75, 711), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 6, 690, 21, 711), 0.15f);
			animation->AddClip(clip);
		}

		// bLookA & bLookD 6
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 331, 859, 344, 880), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 277, 861, 290, 880), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 223, 860, 235, 880), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 466, 835, 479, 855), 0.15f);
			animation->AddClip(clip);
		}

		//bLookWA & bLookWD 7
		{
			clip = new Clip(PlayMode::End);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 466, 470, 480, 491), 0.1f);
			animation->AddClip(clip);
		}

		//bIdleSA & bLookSD 8
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 331, 859, 344, 880), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 277, 861, 290, 880), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 223, 860, 235, 880), 0.15f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 466, 835, 479, 855), 0.15f);
			animation->AddClip(clip);
		}

		// dash////////////////////////////////////////////////////////////////////////////////////////
		// bDashW 9
		{
			clip = new Clip(PlayMode::Loop);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 250, 836, 263, 851), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 250, 887, 263, 901), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 7, 887, 20, 898), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 390, 918, 403, 934), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 169, 897, 182, 909), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 277, 843, 290, 853), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 304, 842, 317, 852), 0.1f);
			clip->AddFrame(new Sprite(spriteFile, shaderFile, 331, 840, 344, 851), 0.1f);
			animation->AddClip(clip);
		}

		// bDashS 10
		{

		}

		// bDashA & bDashD 11
		{
		
		}

		// bDashA & bDashD & bDashSA & bDashSD 12
		{

		}
	}
	
	// eWAnimation////////////////////////////////////////////////////////////////////////////////////////
	{
		//walkEffect_Idle 0
		{
			eWClip = new Clip(PlayMode::End);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 0, 2, 2, 5), 0.1f);
			eWAnimation->AddClip(eWClip);
		}

		// walkEffect_act 1
		{
			eWClip = new Clip(PlayMode::Loop);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 6, 9, 22, 25), 0.1f);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 29, 6, 51, 26), 0.1f);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 54, 3, 81, 28), 0.1f);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 83, 4, 107, 28), 0.1f);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 108, 4, 133, 25), 0.1f);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 137, 5, 160, 23), 0.1f);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 164, 3, 186, 21), 0.1f);
			eWClip->AddFrame(new Sprite(eWSpriteFile, shaderFile, 193, 2, 211, 17), 0.1f);
			eWAnimation->AddClip(eWClip);
		}
	}
	
	// eSAnimation////////////////////////////////////////////////////////////////////////////////////////
	{
		// shadowEffect0
		{
			eSClip = new Clip(PlayMode::End);
			eSClip->AddFrame(new Sprite(spriteFile, shaderFile, 389, 988, 401, 993), 0.1f);
			eSAnimation->AddClip(eSClip);
		}
	}

	Position(position);
	animation->Scale(scale); 
	animation->Play(0);
	
	eWAnimation->Scale(0.65f, 0.65f);
	eWAnimation->Play(0);

	eSAnimation->Scale(scale);
	eSAnimation->Play(0);

	animation->DrawBound(true);
	eWAnimation->DrawBound(true);
	eSAnimation->DrawBound(true);
}

Player::~Player()
{
	SafeDelete(animation);
	SafeDelete(eWAnimation);
	SafeDelete(eSAnimation);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->Position();
	
	D3DXVECTOR2 mouse = Mouse->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;
	
	D3DXVECTOR2 mouseScreen = Mouse->Position();
	D3DXVECTOR2 mouseWorld = mouse + animation->Position();
	D3DXVECTOR2	animWorld = animation->Position();
	D3DXVECTOR2 animScreen = D3DXVECTOR2((float)Width * 0.5f, (float)Height * 0.5f);
	
	this->mouseWorld = mouseWorld;
	this->mouseScreen = mouseScreen;
	this->animWorld = animWorld;
	this->animScreen = animScreen;

	bool bStop = true;
	
	bool bMoveW = false;
	bool bMoveS = false;
	bool bMoveA = false;
	bool bMoveD = false;
	bool bMoveWA = false;
	bool bMoveWD = false;
	bool bMoveSA = false;
	bool bMoveSD = false;

	bool bDashW = false;
	bool bDashS = false;
	bool bDashA = false;
	bool bDashD = false;
	bool bDashWA = false;
	bool bDashWD = false;
	bool bDashSA = false;
	bool bDashSD = false;
	
	bool bLookW = false;
	bool bLookWrev = false;	
	bool bLookS = false;
	bool bLookSrev = false;  
	bool bLookA = false;
	bool bLookD = false;
	bool bLookWA = false;
	bool bLookWD = false;
	bool bLookSA = false;
	bool bLookSD = false;
	
	eSAnimation->Position(position.x, position.y - 40.0f);
	
	// keyboard controll
	{
		// w
		if (Key->Press('W'))
		{
			bStop = false;
			bMoveW = true;
			position.y += moveSpeed * Timer->Elapsed();

			if (Key->Press('D'))
			{
				bMoveW = false;
				bMoveWD = true;
			}

			if (Key->Press('A'))
			{
				bMoveW = false;
				bMoveWA = true;
			}

			if (Mouse->Down(1))
			{
				bMoveW = false;
				bDashW = true;
			}
		}

		// s
		if (Key->Press('S'))
		{
			bStop = false;
			bMoveS = true;
			position.y -= moveSpeed * Timer->Elapsed();

			if (Key->Press('D'))
			{
				bMoveS = false;
				bMoveSD = true;
			}

			if (Key->Press('A'))
			{
				bMoveS = false;
				bMoveSA = true;
			}
		}

		// a
		if (Key->Press('A')) 
		{
			bStop = false;
			bMoveA = true;
			position.x -= moveSpeed * Timer->Elapsed();

			if (Key->Press('W'))
			{
				bMoveA = false;
				bMoveWA = true;
			}

			if (Key->Press('S'))
			{
				bMoveA = false;
				bMoveSA = true;
			}
		}

		// d
		if (Key->Press('D'))
		{
			bStop = false;
			bMoveD = true;
			position.x += moveSpeed * Timer->Elapsed();

			if (Key->Press('W'))
			{
				bMoveD = false;
				bMoveWD = true;
			}

			if (Key->Press('S'))
			{
				bMoveD = false;
				bMoveSD = true;
			}
		}
	}
	// animation 
	{
		if (bStop)
		{
			D3DXVECTOR2 mVec = animWorld - mouseWorld;
			D3DXVec2Length(&mVec);
			D3DXVECTOR2 mVecN;
			D3DXVec2Normalize(&mVecN, &mVec);

			D3DXVECTOR2 pVec = animWorld - (animWorld - D3DXVECTOR2(0.0f, 2500.0f));
			D3DXVec2Length(&pVec);
			D3DXVECTOR2 pVecN;
			D3DXVec2Normalize(&pVecN, &pVec);

			float theta = D3DXVec2Dot(&mVecN, &pVecN);
			float forDegree = acos(theta);
			float animView = forDegree * (180.0f / M_PI);

			if (animScreen.x < mouseScreen.x)
			{
				if (animView > 0.0f && animView < 30.0f)
					bLookSrev = true;
				if (animView >= 30.0f && animView < 60.0f)
					bLookSD = true;
				if (animView >= 60.0f && animView < 120.0f)
					bLookD = true;
				if (animView >= 120.0f && animView < 150.0f)
					bLookWD = true;
				if (animView >= 150.0f && animView < 180.0f)
					bLookW = true;
			}
			else if (animScreen.x > mouseScreen.x)
			{
				if (animView > 0.0f && animView < 30.0f)
					bLookS = true;
				if (animView >= 30.0f && animView < 60.0f)
					bLookSA = true;
				if (animView >= 60.0f && animView < 120.0f)
					bLookA = true;
				if (animView >= 120.0f && animView < 150.0f)
					bLookWA = true;
				if (animView >= 150.0f && animView <= 180.0f)
					bLookWrev = true;
			}
		}

		if (!bStop)
		{
			if (abs(eWAnimation->Position().x - animation->Position().x) >= 100.0f ||
				abs(eWAnimation->Position().y - animation->Position().y) >= 100.0f) 
			{
				eWAnimation->Position(position.x, position.y - 30.0f);
				if (bMoveS)
				{
					eWAnimation->Position(position.x, position.y + 30.0f);
				}
				eWAnimation->Play(1);
			}
		}
		else
		{
			eWAnimation->Position(position.x, position.y - 30.0f);
			eWAnimation->Play(0);
		}

		if (bMoveW)
		{
			animation->Play(0);
		}

		if (bMoveS)
		{
			animation->Play(1);
		}

		if (bMoveA)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(2);
		}

		if (bMoveD)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(2);
		}

		if (bMoveWA)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(3);
		}

		if (bMoveWD)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(3);
		}

		if (bMoveSA)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(2);
		}

		if (bMoveSD)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(2);
		}

		if (bDashW)
		{
			
		}

		if (bDashS)
		{

		}

		if (bDashA)
		{

		}

		if (bDashD)
		{

		}

		if (bDashWA)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(7);
		}

		if (bDashWD)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(7);
		}

		if (bDashSA)
		{

		}

		if (bDashSD)
		{

		}

		if (bLookW)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(4);
		}

		if (bLookWrev)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(4);
		}

		if (bLookS)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(5);
		}

		if (bLookSrev)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(5);
		}

		if (bLookA)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(6);
		}

		if (bLookD)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(6);
		}

		if (bLookWA)
		{

		}

		if (bLookWD)
		{

		}

		if (bLookSA)
		{

		}

		if (bLookSD)
		{

		}
			
		Position(position);
		animation->Update(V, P);
		eWAnimation->Update(V, P);
		eSAnimation->Update(V, P);
	}
}

void Player::Render()
{
	ImGui::SliderFloat("MoveSpeed", &moveSpeed, 50, 400);
	ImGui::LabelText("ScreenMousePos", "%.0f, %.0f", Mouse->Position().x, Mouse->Position().y);
	ImGui::LabelText("worldMousePos", "%.0f, %.0f", mouseWorld.x, mouseWorld.y);
	ImGui::LabelText("screenAnimPos", "%.0f, %.0f", animScreen.x, animScreen.y);
	ImGui::LabelText("worldAnimPos", "%.0f, %.0f", animation->Position().x, animation->Position().y);
	
	animation->Render();
	eWAnimation->Render();
	eSAnimation->Render();
}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->Position() - focusOffset;
	//D3DXVECTOR2 textureSize = animation->TextureSize();
	//D3DXVECTOR2 scale = animation->Scale();

	//(*size).x = textureSize.x*scale.x;
	//(*size).y = textureSize.y*scale.y;
	(*size) = D3DXVECTOR2(1, 1);
}

void Player::Position(D3DXVECTOR2 vec)
{ 
	animation->Position(vec);
}

Sprite * Player::GetSprite()
{
	return animation->GetSprite();
}


