#pragma once
#include "Objects/Player.h"
#include "Objects/Mnormal.h"
#include "Objects/Mself.h"
#include "Objects/Mspecial.h"
#include "Objects/Bullet.h"

class Judege
{
public:
	Judege();
	~Judege();

	static void PlayerAndMnormal(Player* player, Mnormal* monster, Bullet* bulletP, Bullet* bulletM);
	static void PlayerAndMself(Player* player, Mself monster, Bullet* bulletP, Bullet* bulletM);
	static void PlayerAndMspecial(Player* player, Mspecial* monster, Bullet* bulletP, Bullet* bulletM);
};
