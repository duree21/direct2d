#include "stdafx.h"
#include "Judge.h"

Judege::Judege()
{
}

Judege::~Judege()
{
}

void Judege::PlayerAndMnormal(Player * player, Mnormal * monster, Bullet * bulletP, Bullet * bulletM)
{
	bool bBulletPAtk = false;
	bBulletPAtk = Sprite::Aabb(bulletP->GetBulletSprite(), monster->GetMnormal());

	bool bBulletMAtk = false;
	bBulletMAtk = Sprite::Aabb(bulletM->GetBulletAnim()->GetSprite(), player->GetSprite());

	if (bBulletPAtk)
	{
		float result = monster->GetHp() - bulletP->GetBulletDamage();
		monster->SetHp(result);
	}

	if (bBulletMAtk)
	{
		float result = player->GetHp() - bulletM->GetBulletDamage();
		player->SetHp(result);
	}
}

void Judege::PlayerAndMself(Player * player, Mself monster, Bullet * bulletP, Bullet * bulletM)
{
}

void Judege::PlayerAndMspecial(Player * player, Mspecial * monster, Bullet * bulletP, Bullet * bulletM)
{
}
