#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(D3DXVECTOR2 position, D3DXVECTOR2 scale, int selBullet) :
	velocity(D3DXVECTOR2(0.0f, 0.0f)), damage(20.0f)
{
	this->selBullet = selBullet;
	
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	
	switch (selBullet)
	{
		case Bullet::PlayerBullet:
		{
			wstring spriteFile = Textures + L"Effect/player_mnormal_bullet.png";
			
			bullet = new Sprite(spriteFile, shaderFile, 25, 373, 35, 383); // �ӽ� ��ǥ
			bullet->Position(position);
			bullet->Scale(scale);

			break;
		}

		case Bullet::GigiBullet:
		{
			wstring spriteFile = Textures + L"Effect/gigi_bullet.png";
			Clip* clip;

			// Gigi bullet
			{
				clip = new Clip(PlayMode::Loop);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 0, 14, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 14, 0, 28, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 28, 0, 42, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 42, 0, 56, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 56, 0, 70, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 70, 0, 84, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 84, 0, 98, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 0, 112, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 112, 0, 126, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 126, 0, 140, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 140, 0, 154, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 154, 0, 168, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 168, 0, 182, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 182, 0, 196, 14), 0.15f);
				clip->AddFrame(new Sprite(spriteFile, shaderFile, 196, 0, 210, 14), 0.15f);
				bulletAnim->AddClip(clip);
			}
			bulletAnim->Position(position);
			bulletAnim->Scale(scale);

			break;
		}

		case Bullet::SmileyBullet:
		{
			wstring spriteFile = Textures + L"Effect/player_mnormal_bullet.png";

			bullet = new Sprite(spriteFile, shaderFile, 25, 373, 35, 383);	
			bullet->Position(position);
			bullet->Scale(scale);

			break;
		}
		default:
			break;
	}
}

Bullet::~Bullet()
{
	SafeDelete(bulletAnim);
	SafeDelete(bullet);
}

void Bullet::PlayerBulletUtil(Player* player, Weapon * weapon)
{
	D3DXVECTOR2 mouse = Mouse->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;

	// player�� mouse ��ǥ��...
	D3DXVECTOR2 mouseScreen = Mouse->Position();
	D3DXVECTOR2 mouseWorld = mouse + weapon->PositionWeapon();
	D3DXVECTOR2	playerWorld = player->Position();
	D3DXVECTOR2 playerScreen = D3DXVECTOR2((float)Width * 0.5f, (float)Height * 0.5f);
	D3DXVECTOR2	weaponWorld = weapon->PositionWeapon();
	D3DXVECTOR2 weaponScreen = D3DXVECTOR2((float)Width * 0.5f, (float)Height * 0.5f);
	
	if (Mouse->Down(0))
	{	
		// �ƴ� �̰� �׳� ���⸸ �ϸ� �ǳ�?
		// bullet ��ġ �ʱ�ȭ 
		bullet->Position(playerWorld);
		// bullet��ġ ���濡 ���� position �ʱ�ȭ 
		position = bullet->Position();

		// mouseWorld���� playerWorld ���ָ� ������ ���� (����1 - ����2 = ����1���� ����2���� ����)
		// ����Ƽ������ �Ʒ� ����Ʈ�� ����
		// https://arainablog.tistory.com/81
		D3DXVECTOR2 bulletFirePos = mouseWorld - playerWorld;
		D3DXVec2Normalize(&bulletFirePos, &bulletFirePos);
		//D3DXVec2Length(&bulletFirePos);
		//D3DXVECTOR2 nBulletFirePos;
		//D3DXVec2Normalize(&nBulletFirePos, &bulletFirePos);

		// player���� mouse ���� ���Ⱚ�� position�� ������ velocity�� �־���
		velocity.x = bulletFirePos.x * 1100.0f;
		velocity.y = bulletFirePos.y * 1100.0f;
	}

	position += velocity * Timer->Elapsed();		
	bullet->Position(position);
}

void Bullet::MnormalBulletUtil(Sprite* room, Mnormal * monster, Player * player)
{
	D3DXVECTOR2 monsterWorld = monster->Position();
	D3DXVECTOR2 playerWorld = player->Position();

	D3DXVECTOR2 mPVec = monsterWorld - playerWorld;
	D3DXVec2Normalize(&mPVec, &mPVec);
}

void Bullet::MspecialBulletUtil(Sprite* room, Mspecial * monster, Player * player)
{
	
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (selBullet == 2)
		bulletAnim->Update(V, P);

	if (selBullet == 1)
		bullet->Update(V, P);
}

void Bullet::Render()
{
	if (selBullet == 2)
		bulletAnim->Render();

	if (selBullet == 1)
		bullet->Render();
}
