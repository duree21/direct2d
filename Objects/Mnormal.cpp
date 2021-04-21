#include "stdafx.h"
#include "Mnormal.h"
#define _USE_MATH_DEFINES
#include <math.h>

Mnormal::Mnormal(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	: hp(100.0f), velocity(D3DXVECTOR2(0.0f, 0.0f))
{
	animation = new Animation();
	Clip* clip;

	wstring spriteFile = Textures + L"monster/mnormal/kin.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	// idle_w 0
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 42, 16, 54, 45), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 57, 17, 69, 45), 0.2f);

		animation->AddClip(clip);
	}
	
	// idle_s 1
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 5, 16, 17, 45), 0.2f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 20, 16, 32, 45), 0.2f);

		animation->AddClip(clip);
	}

	// walk_w 2
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 5, 92, 17, 121), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 20, 93, 37, 121), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 40, 93, 58, 121), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 61, 92, 73, 121), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 76, 91, 94, 121), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 97, 92, 114, 121), 0.1f);
 
		animation->AddClip(clip);
	}
	
	// walk_s 3
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 5, 60, 18, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 21, 59, 38, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 41, 60, 57, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 61, 60, 73, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 76, 59, 93, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 96, 61, 114, 89), 0.1f);

		animation->AddClip(clip);
	}

	// walk_a or walk_sa && walk_d or walk_sd 4 (��������Ʈ �� a�� �ȴ� ���ϸ��̼�) ��, ����, ��, �Ͽ�
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 60, 144, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 147, 59, 164, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 167, 60, 184, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 167, 60, 184, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 187, 60, 199, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 202, 59, 219, 89), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 222, 61, 240, 89), 0.1f);

		animation->AddClip(clip);
	}

	// walk_wa && walk_wd 5(��������Ʈ�� wa�� �ȴ� ���ϸ��̼�) ����, ���
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 93, 149, 121), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 152, 91, 170, 121), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 173, 92, 190, 121), 0.1f);

		animation->AddClip(clip);
	}

	// hit 6
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 5, 135, 17, 164), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 20, 146, 32, 164), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 136, 52, 164), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 56, 135, 73, 164), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 76, 135, 93, 164), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 96, 135, 114, 164), 0.1f);

		animation->AddClip(clip);
	}

	// dead normal 7
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 358, 22, 409), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 26, 391, 47, 409), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 50, 393, 71, 409), 0.1f);

		animation->AddClip(clip);
	}

	// dead explode 8
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 22, 190, 34, 218), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 5, 190, 19, 218), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 37, 189, 62, 218), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 70, 194, 93, 218), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 96, 186, 128, 218), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 131, 181, 168, 218), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 171, 180, 213, 218), 0.1f);

		animation->AddClip(clip);
	}

	// dead normal end 9 (��������Ʈ �� �Ӹ��� a�� ���� ����)
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 24, 472, 40, 490), 0.1f);

		animation->AddClip(clip);
	}

	// dead explpode end 10
	{
	}
	
	animation->Play(1);
	Position(position);
	Scale(scale);
	animation->DrawBound(true);
}

Mnormal::~Mnormal()
{
	SafeDelete(animation);
}

void Mnormal::MnormalUtil(Sprite* room, Player * player)
{	
	// Mnormal animation Ƣ�� ����
	// Player�� �����϶��� Mnormal animation�� Ʀ 

	// Mnormal�� �̵��� bPlayerEnterRoom�� true�� ���� �۵��� 
	// false �� ���� room �� ��ġ���� Math::Random �Լ��� �̿� �������� �������� ������
	// �� ��Ȳ�� �ƴ� ���� ������ Ƣ�� �� �˾Ҵµ� �� �߾����� �ص� �Ȱ��� 

	// �� �Լ��� Stage1.cpp�� Update() �Լ����� �� ������ ���ŵ�
	// �� Ŭ������ Animation.cpp > Clip.cpp > Sprite.cpp �� ������Ʈ �� 
	// Clip.cpp�� Update()�� Render()������ �ݵ�� ����� 

	bool bPlayerEnterRoom = false;
	bPlayerEnterRoom = Sprite::Aabb(room, player->GetSprite());

	D3DXVECTOR2	playerWorld = player->GetPlayer()->Position();
	D3DXVECTOR2 monsterWorld = Position();

	D3DXVECTOR2 monMovePos = monsterWorld - playerWorld;
	D3DXVec2Normalize(&monMovePos, &monMovePos);

	velocity.x = monMovePos.x * 90.0f;
	velocity.y = monMovePos.y * 90.0f;

	if (bPlayerEnterRoom)
	{
		bool bAttack = true;

		bool bStopS = false;
		bool bStopW = false;

		bool bMoveW = false;
		bool bMoveS = false;
		bool bMoveA = false;
		bool bMoveD = false;

		bool bMoveWA = false;
		bool bMoveWD = false;
		bool bMoveSA = false;
		bool bMoveSD = false;
		
		// Mnormal move
		if (monMovePos.y > 0.0f)	// s
		{
			bMoveS = true; 

			bMoveW = false;
			bMoveA = false;
			bMoveD = false;
			bMoveWA = false;
			bMoveWD = false;
			bMoveSA = false;
			bMoveSD = false;
			
			if (monMovePos.x > 0.0f)	//sa
			{
				bMoveSA = true;

				bMoveW = false;
				bMoveS = false;
				bMoveA = false;
				bMoveD = false;
				bMoveWA = false;
				bMoveWD = false;
				bMoveSD = false;
			}
			if (monMovePos.x < 0.0f)	//sd
			{
				bMoveSD = true;

				bMoveW = false;
				bMoveS = false;
				bMoveA = false;
				bMoveD = false;
				bMoveWA = false;
				bMoveWD = false;
				bMoveSA = false;
			}
		}
		
		else if (monMovePos.y < 0.0f)	// w
		{
			bMoveW = true; 

			bMoveS = false;
			bMoveA = false;
			bMoveD = false;
			bMoveWA = false;
			bMoveWD = false;
			bMoveSA = false;
			bMoveSD = false;
			
			if (monMovePos.x > 0.0f)	// wa
			{
				bMoveWA = true;

				bMoveW = false;
				bMoveS = false;
				bMoveA = false;
				bMoveD = false;
				bMoveWD = false;
				bMoveSA = false;
				bMoveSD = false;
			}
			if (monMovePos.x > 0.0f)	// wd
			{
				bMoveWD = true;

				bMoveW = false;
				bMoveS = false;
				bMoveA = false;
				bMoveD = false;
				bMoveWA = false;
				bMoveSA = false;
				bMoveSD = false;
			}
		}

		D3DXVECTOR2 mPVec = playerWorld - monsterWorld;
		D3DXVec2Length(&mPVec);

		// Mnormal stop for attack 
		if (abs(mPVec.x) < 100.0f || abs(mPVec.y) < 100.0f)
		{
			velocity.x = 0.0f;
			velocity.y = 0.0f;

			if (monMovePos.y > 0.0f)
				bStopS = true;
			else if (monMovePos.y < 0.0f)	// else if�� �̹Ƿ�, �� if�� ������ �����̸� bStopS�� �������� false �̹Ƿ�
				bStopW = true;	// bStopS�� ���԰� ��ø�� ���� �ʾƼ� ������ �ʴ´�

			bMoveW = false;
			bMoveS = false;
			bMoveA = false;
			bMoveD = false;

			bMoveWA = false;
			bMoveWD = false;
			bMoveSA = false;
			bMoveSD = false;
		}

		// Mnormal anim
		if (bStopW)
			animation->Play(0);
		if (bStopS)
			animation->Play(1);
		if (bMoveW)
			animation->Play(2);
		if (bMoveS)
			animation->Play(3);
		if (bMoveA)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(4);
		}
		if(bMoveD)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(4);
		}
		if (bMoveWA)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(5);
		}
		if(bMoveWD)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(5);
		}
		if(bMoveSA)
		{
			animation->RotationDegree(0.0f, 0.0f, 0.0f);
			animation->Play(4);
		}
		if(bMoveSD)
		{
			animation->RotationDegree(0.0f, 180.0f, 0.0f);
			animation->Play(4);
		}

		// update Mnormal position
		position -= velocity * Timer->Elapsed();
		Position(position);
	}

	else if (!bPlayerEnterRoom)
	{
		D3DXVECTOR2 spawnPos = D3DXVECTOR2(Math::Random(room->Position().x - room->TextureSize().x * 0.5f * room->Scale().x + animation->TextureSize().x * 0.5f * animation->Scale().x, room->Position().x + room->TextureSize().x * 0.5f * room->Scale().x - animation->TextureSize().x * 0.5f * animation->Scale().x), Math::Random(room->Position().y - room->TextureSize().y * 0.5f * room->Scale().y + animation->TextureSize().y * 0.5f * animation->Scale().y, room->Position().y + room->TextureSize().y * 0.5f * room->Scale().y - animation->TextureSize().y * 0.5f * animation->Scale().y));
		position = spawnPos;
	}
}

void Mnormal::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	animation->Update(V, P);
}

void Mnormal::Render()
{
	animation->Render();
}
