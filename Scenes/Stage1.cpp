#include "stdafx.h"
#include "Stage1.h"
#include "Objects/Judge.h"
#include "Objects/Player.h"
#include "Objects/Weapon.h"
#include "Objects/Warp.h"
#include "Objects/Table.h"
#include "Objects/Bullet.h"
#include "Objects/Mnormal.h"
#include "Renders/Sprite.h"
#include "Viewer/Following.h"

Stage1::Stage1(SceneValues * values)
	:Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	// room
	backGround_start = new Sprite(Textures + L"Stage/ground1.png", shaderFile, 579, 703, 899, 1023);
	backGround_start->Position(0, 0);
	backGround_start->Scale(1, 1);

	backGround_groundStart = new Sprite(Textures + L"Stage/ground1.png",shaderFile, 1, 591, 577, 1022);
	backGround_groundStart->Position(0, 0);
	backGround_groundStart->Scale(2, 2);

	WallMakerUp(backGround_groundStart, vec_upWall);
	WallMakerUpSmall(backGround_groundStart, vec_groundStart_upWallSmall1, vec_groundStart_upWallSmall2);
	EdgeMakerY(backGround_groundStart, vec_groundStart_one, vec_groundStart_two);
	EdgeMakerX(backGround_groundStart, vec_groundStart_edgeX1, vec_groundStart_edgeX2); 

	backGround_one = new Sprite(Textures + L"Stage/ground4.png", shaderFile, 1, 527, 705, 1023);
	backGround_one->Position(0, -1300);
	backGround_one->Scale(2, 2);

	WallMakerUp(backGround_one, vec_upWall);
	WallMakerUpSmall(backGround_one, vec_roomOne_upWallSmall1, vec_roomOne_upWallSmall2);
	EdgeMakerY(backGround_one, vec_roomOne_one, vec_roomOne_two);
	EdgeMakerX(backGround_one, vec_roomOne_edgeX1, vec_roomOne_edgeX2);
	AisleMaker(backGround_groundStart, backGround_one, vec_aisle_edgeY1, vec_aisle_edgeY2, 1);

	backGround_bridge = new Sprite(Textures + L"Stage/ground4.png", shaderFile, 707, 383, 899, 1023);
	backGround_bridge->RotationDegree(0.0f, 0.0f, 90.0f);
	backGround_bridge->Position(1030, -1300);
	backGround_bridge->Scale(2, 2);
	warp_one = new Warp(D3DXVECTOR2(1030,-1300), D3DXVECTOR2(0.5, 0.5));

	backGround_two = new Sprite(Textures + L"Stage/ground4.png", shaderFile, 1, 93, 611, 525);
	backGround_two->Position(2000, -1300);
	backGround_two->Scale(2, 2);

	WallMakerUp(backGround_two, vec_upWall);
	WallMakerUpSmall(backGround_two, vec_roomTwo_upWallSmall1, vec_roomTwo_upWallSmall2);
	EdgeMakerY(backGround_two, vec_roomTwo_one, vec_roomTwo_two);
	EdgeMakerX(backGround_two, vec_roomTwo_edgeX1, vec_roomTwo_edgeX2);

	backGround_three = new Sprite(Textures + L"Stage/ground2.png", shaderFile, 75, 536, 361, 902);
	backGround_three->Position(3200, -1300);
	backGround_three->Scale(2, 2);
	warp_two = new Warp(D3DXVECTOR2(backGround_three->Position().x, backGround_three->Position().y), D3DXVECTOR2(0.5, 0.5));

	WallMakerUp(backGround_three, vec_upWall);
	EdgeMakerY(backGround_three, vec_roomThree_one, vec_roomThree_two);
	EdgeMakerX(backGround_three, vec_roomThree_edgeX1, vec_roomThree_edgeX2);
	AisleMaker(backGround_two, backGround_three, vec_aisle_edgeY3, vec_aisle_edgeY4, 2);

	backGround_boss = new Sprite(Textures + L"Stage/groundboss.png", shaderFile, 1, 527, 705, 1023);
	backGround_boss->Position(3300, 0);
	backGround_boss->Scale(2, 2);

	WallMakerUp(backGround_boss, vec_upWall);
	WallMakerUpSmall(backGround_boss, vec_roomBoss_upWallSmall1, vec_roomBoss_upWallSmall2);
	EdgeMakerY(backGround_boss, vec_roomBoss_one, vec_roomBoss_two);
	EdgeMakerX(backGround_boss, vec_roomBoss_edgeX1, vec_roomBoss_edgeX2);
	AisleMaker(backGround_boss, backGround_three, vec_aisle_edgeY5, vec_aisle_edgeY6, 1);
	
	// objects
	table = new Table(D3DXVECTOR2(0, 0), D3DXVECTOR2(3, 3));
	// player 
	player = new Player(D3DXVECTOR2(0, 0), D3DXVECTOR2(3, 3));
	// weapon 
	weapon = new Weapon(D3DXVECTOR2(0, 0), 1);
	mNormalWeapon = new Weapon(D3DXVECTOR2(1000.0f, 1000.0f), 2);
	// bullet
	bullet = new Bullet(D3DXVECTOR2(1000.0f, 1000.0f), D3DXVECTOR2(2, 2), 1);
	// monster
	mMon = new Mnormal(D3DXVECTOR2(1000.0f, 1000.0f), D3DXVECTOR2(3, 3));
	// camera
	Scene::values->MainCamera = new Following(player);
}

Stage1::~Stage1()
{
	SafeDelete(backGround_groundStart);
	SafeDelete(backGround_start);
	SafeDelete(backGround_one);
	SafeDelete(backGround_bridge);
	SafeDelete(backGround_two);
	SafeDelete(backGround_three);
	SafeDelete(backGround_boss);
	SafeDelete(player);
	SafeDelete(warp_one);
	SafeDelete(warp_two);
	SafeDelete(table);
	SafeDelete(weapon);
	SafeDelete(mMon);
}

void Stage1::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	// room  
	{
		// rooms ///////////////////////////////////////////////////////////////////////////
		{
			backGround_groundStart->Update(V, P);
			backGround_start->Update(V, P);
			backGround_one->Update(V, P);
			backGround_bridge->Update(V, P);
			backGround_two->Update(V, P);
			backGround_three->Update(V, P);
			backGround_boss->Update(V, P);
		}
		// EdgeMakerX //////////////////////////////////////////////////////////////////////
		{
			for (Sprite* edges : vec_groundStart_edgeX1)
				edges->Update(V, P);
			for (Sprite* edges : vec_groundStart_edgeX2)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomOne_edgeX1)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomOne_edgeX2)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomTwo_edgeX1)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomTwo_edgeX2)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomThree_edgeX1)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomThree_edgeX2)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomBoss_edgeX1)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomBoss_edgeX2)
				edges->Update(V, P);
		}
		// EdgeMakerY //////////////////////////////////////////////////////////////////////
		{	
			for (Sprite* edges : vec_groundStart_one)
				edges->Update(V, P);
			for (Sprite* edges : vec_groundStart_two)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomOne_one)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomOne_two)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomTwo_one)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomTwo_two)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomThree_one)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomThree_two)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomBoss_one)
				edges->Update(V, P);
			for (Sprite* edges : vec_roomBoss_two)
				edges->Update(V, P);
		}
		// up walls	////////////////////////////////////////////////////////////////////////
		{
			for (Sprite* wallUps : vec_upWall)	
				wallUps->Update(V, P);
		}
		// up wall smalls
		{
			for (Sprite* UpWallSmalls : vec_groundStart_upWallSmall1)
				UpWallSmalls->Update(V, P);
			for(Sprite* UpWallSmalls : vec_groundStart_upWallSmall2)
				UpWallSmalls->Update(V, P);
			for(Sprite* UpWallSmalls : vec_roomOne_upWallSmall1)
				UpWallSmalls->Update(V, P);
			for (Sprite* UpWallSmalls : vec_roomOne_upWallSmall2)
				UpWallSmalls->Update(V, P);
			for (Sprite* UpWallSmalls : vec_roomTwo_upWallSmall1)
				UpWallSmalls->Update(V, P);
			for (Sprite* UpWallSmalls : vec_roomTwo_upWallSmall2)
				UpWallSmalls->Update(V, P);
			for (Sprite* UpWallSmalls : vec_roomThree_upWallSmall1)
				UpWallSmalls->Update(V, P);
			for (Sprite* UpWallSmalls : vec_roomThree_upWallSmall2)
				UpWallSmalls->Update(V, P);
			for (Sprite* UpWallSmalls : vec_roomBoss_upWallSmall1)
				UpWallSmalls->Update(V, P);
			for (Sprite* UpWallSmalls : vec_roomBoss_upWallSmall2)
				UpWallSmalls->Update(V, P);
		}
		// aisles //////////////////////////////////////////////////////////////////////////
		{
			for (Sprite* aisles : vec_aisle)
				aisles->Update(V, P);
			for (Sprite* aislesEdges : vec_aisle_edgeY1)
				aislesEdges->Update(V, P);
			for (Sprite* aislesEdges : vec_aisle_edgeY2)
				aislesEdges->Update(V, P);
			for (Sprite* aislesEdges : vec_aisle_edgeY3)
				aislesEdges->Update(V, P);
			for (Sprite* aislesEdges : vec_aisle_edgeY4)
				aislesEdges->Update(V, P);
			for (Sprite* aislesEdges : vec_aisle_edgeY5)
				aislesEdges->Update(V, P);
			for (Sprite* aislesEdges : vec_aisle_edgeY6)
				aislesEdges->Update(V, P);
			for (Sprite* aislesEdges : vec_aisle_upWallSmalls)
				aislesEdges->Update(V, P);
		}
		// warps ///////////////////////////////////////////////////////////////////////////
		{
			warp_one->Update(V, P);
			warp_two->Update(V, P);
		}
		// table //////////////////////////////
		{
			table->Update(V, P);
		}
		// aisle door
		{
		
		}
	}

	// actor
	player->Update(V, P);
	mMon->Update(V, P);
	weapon->Update(V, P);
	mNormalWeapon->Update(V, P);
	bullet->Update(V, P);

	// °´Ã¼ °¢Á¾ ÇÔ¼ö ¾÷µ«
	weapon->PlayerWeaponUtil(player);
	mNormalWeapon->MnormalWeaponUtil(player, mMon);
	bullet->PlayerBulletUtil(player, weapon);
	mMon->MnormalUtil(backGround_one, player);
}

void Stage1::Render()
{
	// room 
	{	
		// room edgesY //////////////////////////////////////////////////////////////////////
		{
			for (Sprite* edges : vec_groundStart_one)
				edges->Render();
			for (Sprite* edges : vec_groundStart_two)
				edges->Render();
			for (Sprite* edges : vec_roomOne_one)
				edges->Render();	
			for (Sprite* edges : vec_roomOne_two)		
				edges->Render();	
			for (Sprite* edges : vec_roomTwo_one)	
				edges->Render();	
			for (Sprite* edges : vec_roomTwo_two)	
				edges->Render();	
			for (Sprite* edges : vec_roomThree_one)
				edges->Render();
			for (Sprite* edges : vec_roomThree_two)
				edges->Render();
			for (Sprite* edges : vec_roomBoss_one)
				edges->Render();
			for (Sprite* edges : vec_roomBoss_two)
				edges->Render();
		}
		// room edgesX///////////////////////////////////////////////////////////////////////
		{
			for (Sprite* edges : vec_groundStart_edgeX1)
				edges->Render();
			for (Sprite* edges : vec_groundStart_edgeX2)
				edges->Render();
			for (Sprite* edges : vec_roomOne_edgeX1)
				edges->Render();
			for (Sprite* edges : vec_roomOne_edgeX2)
				edges->Render();
			for (Sprite* edges : vec_roomTwo_edgeX1)
				edges->Render();
			for (Sprite* edges : vec_roomTwo_edgeX2)
				edges->Render();
			for (Sprite* edges : vec_roomThree_edgeX1)
				edges->Render();
			for (Sprite* edges : vec_roomThree_edgeX2)
				edges->Render();
			for (Sprite* edges : vec_roomBoss_edgeX1)
				edges->Render();
			for (Sprite* edges : vec_roomBoss_edgeX2)
				edges->Render();
		}
		// aisle edges //////////////////////////////////////////////////////////
		{
			for (Sprite* aisles : vec_aisle_upWallSmalls)
				aisles->Render();
			for (Sprite* aislesEdges : vec_aisle_edgeY1)
				aislesEdges->Render();
			for (Sprite* aislesEdges : vec_aisle_edgeY2)
				aislesEdges->Render();
			for (Sprite* aislesEdges : vec_aisle_edgeY3)
				aislesEdges->Render();
			for (Sprite* aislesEdges : vec_aisle_edgeY4)
				aislesEdges->Render();
			for (Sprite* aislesEdges : vec_aisle_edgeY5)
				aislesEdges->Render();
			for (Sprite* aislesEdges : vec_aisle_edgeY6)
				aislesEdges->Render();
		}
		// up wall smalls //////////////////////////////////////////////////////////////////////////
		{
			for (Sprite* UpWallSmalls : vec_groundStart_upWallSmall1)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_groundStart_upWallSmall2)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomOne_upWallSmall1)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomOne_upWallSmall2)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomTwo_upWallSmall1)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomTwo_upWallSmall2)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomThree_upWallSmall1)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomThree_upWallSmall2)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomBoss_upWallSmall1)
				UpWallSmalls->Render();
			for (Sprite* UpWallSmalls : vec_roomBoss_upWallSmall2)
				UpWallSmalls->Render();
		}
		// up walls //////////////////////////////////////////////////////////////////////////
		{
			for (Sprite* wallUps : vec_upWall)
				wallUps->Render();
		}
		// aisles //////////////////////////////////////////////////////////////////////////
		{
			for (Sprite* aisles : vec_aisle)
				aisles->Render();
		}
		// aisle door
		{
		}
		// rooms ///////////////////////////////////////////////////////////////////////////
		{
			backGround_bridge->Render();
			backGround_groundStart->Render();
			backGround_start->Render();
			backGround_one->Render();
			backGround_two->Render();
			backGround_three->Render();
			backGround_boss->Render();
		}
		// warps ////////////////////////////////////////////////////////////////////////////
		{
			warp_one->Render();
			warp_two->Render();
		}
	}
	weapon->Render();
	mNormalWeapon->Render();
	player->Render();
	mMon->Render();
	table->Render();
	bullet->Render();
}

void Stage1::EdgeMakerX(Sprite * room, vector<Sprite*>& vecOne, vector<Sprite*>& vecTwo)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	class Sprite* backGround_edgeX1;
	class Sprite* backGround_edgeX2;
	class Sprite* backGround_edge_mesure = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
	backGround_edge_mesure->Scale(2, 2);

	float upWallSizeY = upWall_mesure->TextureSize().y * upWall_mesure->Scale().y;

	float edgeSizeX = backGround_edge_mesure->TextureSize().x * backGround_edge_mesure->Scale().x;
	float edgeSizeY = backGround_edge_mesure->TextureSize().y * backGround_edge_mesure->Scale().y;

	float roomSizeX = room->TextureSize().x * room->Scale().x;
	float roomSizeY = room->TextureSize().y * room->Scale().y;

	int edgeCountX = roomSizeX / edgeSizeY;
	int edgeCountY = roomSizeY / edgeSizeX;

	for (int i = 0; i < 8; i++)
	{
		backGround_edgeX1 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
		vecOne.push_back(backGround_edgeX1);
		backGround_edgeX1->Scale(2, 2);
		backGround_edgeX1->RotationDegree(0.0f, 0.0f, 90.0f);

		vecOne[i]->Position(room->Position().x - roomSizeX * 0.5f + edgeSizeY * 0.5f + (edgeSizeY * i), room->Position().y + roomSizeY * 0.5f + upWallSizeY + edgeSizeX * 0.5f);

		if (vecOne[i]->Position().x + edgeSizeY * 0.5f >= room->Position().x + roomSizeX * 0.5f)
		{
			vecOne[i]->Position(room->Position().x + roomSizeX * 0.5f - edgeSizeY * 0.5f, room->Position().y + roomSizeY * 0.5f + upWallSizeY + edgeSizeX * 0.5f);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		backGround_edgeX2 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
		vecTwo.push_back(backGround_edgeX2);
		backGround_edgeX2->Scale(2, 2);
		backGround_edgeX2->RotationDegree(0.0f, 0.0f, -90.0f);

		vecTwo[i]->Position(room->Position().x - roomSizeX * 0.5f + edgeSizeY * 0.5f + (edgeSizeY * i), room->Position().y - roomSizeY * 0.5f - edgeSizeX * 0.5f);

		if (vecTwo[i]->Position().x + edgeSizeY * 0.5f >= room->Position().x + roomSizeX * 0.5f)
		{
			vecTwo[i]->Position(room->Position().x + roomSizeX * 0.5f - edgeSizeY * 0.5f, room->Position().y - roomSizeY * 0.5f - edgeSizeX * 0.5f);
		}
	}

	for (Sprite* edges : vecOne)
		edges->DrawBound(true);
	for (Sprite* edges : vecTwo)
		edges->DrawBound(true);
}

void Stage1::EdgeMakerY(Sprite * room, vector<Sprite*>& vecOne, vector<Sprite*>& vecTwo)
{	
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	float upWallY = upWall_mesure->TextureSize().y * upWall_mesure->Scale().y;

	class Sprite* backGround_edgeY1;
	class Sprite* backGround_edgeY2;

	class Sprite* backGround_edge_mesure = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
	backGround_edge_mesure->Scale(2, 2);
	
	float edgeSizeX = backGround_edge_mesure->TextureSize().x * backGround_edge_mesure->Scale().x;
	float edgeSizeY = backGround_edge_mesure->TextureSize().y * backGround_edge_mesure->Scale().y;
	
	float roomSizeX = room->TextureSize().x * room->Scale().x;
	float roomSizeY = room->TextureSize().y * room->Scale().y;

	int edgeCountX = roomSizeX / edgeSizeY;
	int edgeCountY = roomSizeY / edgeSizeX;

	for (int i = 0; i < 8; i++)
	{
		backGround_edgeY1 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
		vecOne.push_back(backGround_edgeY1);
		backGround_edgeY1->Scale(2, 2);
		vecOne[i]->Position(room->Position().x + roomSizeX * 0.5f + edgeSizeX * 0.5f, room->Position().y - roomSizeY * 0.5f + edgeSizeY * 0.5f + (edgeSizeY * i));

		if (vecOne[i]->Position().y + edgeSizeY * 0.5f >= room->Position().y + roomSizeY * 0.5f + upWallY)
		{
			vecOne[i]->Position(room->Position().x + roomSizeX * 0.5f + edgeSizeX * 0.5f, room->Position().y + roomSizeY * 0.5f + upWallY - edgeSizeY * 0.5f);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		backGround_edgeY2 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
		vecTwo.push_back(backGround_edgeY2);
		backGround_edgeY2->Scale(2, 2);
		backGround_edgeY2->RotationDegree(0.0f, 0.0f, 180.0f);	
		vecTwo[i]->Position(room->Position().x - roomSizeX * 0.5f - edgeSizeX * 0.5f, room->Position().y - roomSizeY * 0.5f + edgeSizeY * 0.5f + (edgeSizeY * i));

		if (vecTwo[i]->Position().y + edgeSizeY * 0.5f >= room->Position().y + roomSizeY * 0.5f + upWallY)
		{
			vecTwo[i]->Position(room->Position().x - roomSizeX * 0.5f - edgeSizeX * 0.5f, room->Position().y + roomSizeY * 0.5f + upWallY - edgeSizeY * 0.5f);
		}
	}

	for (Sprite* edges : vecOne )
		edges->DrawBound(true);

	for (Sprite* edges : vecTwo)
		edges->DrawBound(true);
}

void Stage1::WallMakerUp(Sprite * room, vector<Sprite*>& vecOne) 
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	class Sprite* upWall = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 1, 427, 384, 490);
	upWall->Scale(2, 2);
	upWall_mesure = upWall;
	
	if (room->TextureSize().x * room->Scale().x > upWall->TextureSize().x * upWall->Scale().x)
	{
		float upWallPosX = room->Position().x;
		float upWallPosY = room->Position().y + room->TextureSize().y * 0.5f * room->Scale().y + upWall->TextureSize().y * 0.5f * upWall->Scale().y;

		upWall->Position(upWallPosX, upWallPosY);
		vecOne.push_back(upWall);
	}

	else if (room->TextureSize().x * room->Scale().x < upWall->TextureSize().x * upWall->Scale().x)
	{
		for (int i = 0; i < 6; i++)
		{
			class Sprite* upWallSmall;
			upWallSmall = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 65, 895, 113, 959);
			upWallSmall->Scale(2, 2);
			upWallSmall->Position(room->Position().x - room->TextureSize().x * 0.5f * room->Scale().x + upWallSmall->TextureSize().x * 0.5f * upWallSmall->Scale().x + (upWallSmall->TextureSize().x * upWallSmall->Scale().x * i),room->Position().y + room->TextureSize().y * 0.5f * room->Scale().y + upWallSmall->TextureSize().y * 0.5f * upWallSmall->Scale().y);
			vecOne.push_back(upWallSmall);
			
			if (upWallSmall->Position().x + upWallSmall->TextureSize().x * 0.5f * upWallSmall->Scale().x >= room->Position().x + room->TextureSize().x * 0.5f * room->Scale().x)
				return;
		}
	}

	for (Sprite* wallUps : vecOne)
		wallUps->DrawBound(true);
}

void Stage1::WallMakerUpSmall(Sprite * room, vector<Sprite*>& vecOne, vector<Sprite*>& vecTwo)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	
	class Sprite* upWall_mesure = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 65, 895, 113, 959);
	class Sprite* upWallSmall1;
	class Sprite* upWallSmall2;
	
	float upWallLenX = upWall_mesure->TextureSize().x * upWall_mesure -> Scale().x;
	float upWallLenY = upWall_mesure->TextureSize().y * upWall_mesure -> Scale().y;

	float upWallPosX = room->Position().x;
	float upWallPosY = room->Position().y + room->TextureSize().y * 0.5f * room->Scale().y + upWall_mesure->TextureSize().y * 0.5f * upWall_mesure->Scale().y;

	float upWallLeft = upWallPosX - upWallLenX * 0.5f;
	float upWallRight = upWallPosX + upWallLenX * 0.5f;
	
	float roomUp = room->Position().y + room->TextureSize().y * 0.5f * room->Scale().y;
	float roomLeft = room->Position().x - room->TextureSize().x * 0.5f * room->Scale().x;
	float roomRight = room->Position().x + room->TextureSize().x * 0.5f * room->Scale().x;
	
	for (int i = 0; i < 4; i++)
	{
		upWallSmall1 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 65, 895, 113, 959);
		upWallSmall1->Scale(2, 2);
		upWallSmall1->Position(roomLeft + upWallSmall1->TextureSize().x * 0.5f * upWallSmall1->Scale().x + (i * upWallSmall1 -> TextureSize().x * upWallSmall1->Scale().x), roomUp + upWallSmall1->TextureSize().y * 0.5f * upWallSmall1->Scale().y);
		vecOne.push_back(upWallSmall1);

		//if (vecOne[i]->Position().x + vecOne[i]->TextureSize().x * 0.5f * vecOne[i]->Scale().x >= upWallLeft)
		//{
		//	vecOne[i]->Position(upWallLeft - vecOne[i]->TextureSize().x * 0.5f * vecOne[i]->Scale().x, roomUp + upWallSmall1->TextureSize().y * 0.5f * upWallSmall1->Scale().y);
		//}
	}

	for (int i = 0; i < 4; i++)
	{
		upWallSmall2 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 65, 895, 113, 959);
		upWallSmall2->Scale(2, 2);
		upWallSmall2->Position(roomRight - upWallSmall2->TextureSize().x * 0.5f * upWallSmall2->Scale().x - (i * upWallSmall2->TextureSize().x * upWallSmall2->Scale().x), roomUp + upWallSmall2->TextureSize().y * 0.5f * upWallSmall2->Scale().y);
		vecTwo.push_back(upWallSmall2);

		//if (vecTwo[i]->Position().x - vecTwo[i]->TextureSize().x * 0.5f * vecTwo[i]->Scale().x <= upWallRight)
		//{
		//	vecTwo[i]->Position(upWallRight - vecTwo[i]->TextureSize().x * 0.5f * vecTwo[i]->Scale().x, roomUp + upWallSmall2->TextureSize().y * 0.5f * upWallSmall2->Scale().y);
		//}
	}

	for (Sprite* upWallSmalls : vecOne)
		upWallSmalls->DrawBound(true);
	for (Sprite* upWallSmalls : vecTwo)
		upWallSmalls->DrawBound(true);
}

void Stage1::AisleMaker(Sprite * roomOne, Sprite* roomTwo, vector<Sprite*>& edgevecOne, vector<Sprite*>& edgevecTwo, int selAislePos)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	class Sprite* aisle = new Sprite(Textures + L"Stage/ground4.png", shaderFile, 770, 575, 837, 849);
	aisle->Scale(2, 2);
	
	float roomOneUp = roomOne->Position().y + roomOne->TextureSize().y * 0.5f * roomOne->Scale().y;
	float roomOneDown = roomOne->Position().y - roomOne->TextureSize().y * 0.5f * roomOne->Scale().y;;
	float roomOneLeft = roomOne->Position().x - roomOne->TextureSize().x * 0.5f * roomOne->Scale().x;
	float roomOneRight = roomOne->Position().x + roomOne->TextureSize().x * 0.5f * roomOne->Scale().x;

	float roomTwoUp = roomTwo->Position().y + roomTwo->TextureSize().y * 0.5f * roomTwo->Scale().y;
	float roomTwoDown = roomTwo->Position().y - roomTwo->TextureSize().y * 0.5f * roomTwo->Scale().y;;
	float roomTwoLeft = roomTwo->Position().x - roomTwo->TextureSize().x * 0.5f * roomTwo->Scale().x;
	float roomTwoRight = roomTwo->Position().x + roomTwo->TextureSize().x * 0.5f * roomTwo->Scale().x;

	// roomOne, which is room Position Up
	// roomTwo, which is room Position Down
	// aislePosBottom
	float aislePosBottomX;

	if (roomOneRight > roomTwoLeft)
		aislePosBottomX = Math::Random(roomTwoLeft + aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomOneRight - aisle->TextureSize().x * 0.5f * aisle->Scale().x);
	if (roomOneLeft < roomTwoLeft)
		aislePosBottomX = Math::Random(roomOneLeft + aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomTwoRight - +aisle->TextureSize().x * 0.5f * aisle->Scale().x);
	if (roomOne->TextureSize().x * roomOne->Scale().x < roomTwo->TextureSize().x * roomTwo->Scale().x)
		aislePosBottomX = Math::Random(roomOneLeft + aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomOneRight - aisle->TextureSize().x * 0.5f * aisle->Scale().x);
	if (roomOne->TextureSize().x * roomOne->Scale().x > roomTwo->TextureSize().x * roomTwo->Scale().x)
		aislePosBottomX = Math::Random(roomTwoLeft + aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomTwoRight - aisle->TextureSize().x * 0.5f * aisle->Scale().x);

	float aislePosBottomY = roomOneDown  * 1.5f;

	// aislePosLeft
	// roomOne, which is room Position left
	// roomTwo, which is room Position right
	float aislePosLeftX = roomOneRight * 1.1f;
	
	float aislePosLeftY;
	if (roomOneUp > roomTwoDown)
		aislePosLeftY = Math::Random(roomOneUp - aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomTwoDown + aisle->TextureSize().x * 0.5f * aisle->Scale().x);
	if (roomOneDown < roomTwoUp)
		aislePosLeftY = Math::Random(roomTwoUp - aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomOneDown + aisle->TextureSize().x * 0.5f * aisle->Scale().x);
	if (roomOne->TextureSize().x * roomOne->Scale().x > roomTwo->TextureSize().x * roomTwo->Scale().x)
		aislePosLeftY = Math::Random(roomTwoUp - aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomTwoDown + aisle->TextureSize().x * 0.5f * aisle->Scale().x);
	if (roomOne->TextureSize().x * roomOne->Scale().x < roomTwo->TextureSize().x * roomTwo->Scale().x)
		aislePosLeftY = Math::Random(roomOneUp - aisle->TextureSize().x * 0.5f * aisle->Scale().x, roomOneDown + aisle->TextureSize().x * 0.5f * aisle->Scale().x);

	enum TOGGLEAISLE
	{
		BOTTOM = 1, LEFT
	};

	switch (selAislePos)
	{
		case BOTTOM:
		{
			aisle->Position(aislePosBottomX, aislePosBottomY);
			EdgeMakerY(aisle, edgevecOne, edgevecTwo);
			vec_aisle.push_back(aisle);
	
			break;
		}

		case LEFT:
		{
			aisle->RotationDegree(0.0f, 0.0f, 90.0f);
			aisle->Position(aislePosLeftX, aislePosLeftY);
			vec_aisle.push_back(aisle);

			for (int i = 0; i < 10; i++)
			{
				class Sprite* backGround_edgeY1 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
				backGround_edgeY1->Scale(2, 2);
				backGround_edgeY1->RotationDegree(0.0f, 0.0f, -90.0f);
				// È¸Àü ½Ã Ãà ¹Ù²ñ! ÁÖÀÇ
				backGround_edgeY1->Position(aisle->Position().x - aisle->TextureSize().y * 0.5f * aisle->Scale().y + backGround_edgeY1->TextureSize().y * 0.5f * backGround_edgeY1->Scale().y + (backGround_edgeY1->TextureSize().y * 0.5f * backGround_edgeY1->Scale().y * i), aisle->Position().y - aisle->TextureSize().x * 0.5f * aisle->Scale().x - backGround_edgeY1->TextureSize().x * 0.5f);
				edgevecOne.push_back(backGround_edgeY1);

				class Sprite* upWallSmall = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 65, 895, 113, 959);
				upWallSmall->Scale(2, 2);
				upWallSmall->Position(aisle->Position().x - aisle->TextureSize().y * 0.5f * aisle->Scale().y + upWallSmall->TextureSize().x * 0.5f * upWallSmall->Scale().x + (upWallSmall->TextureSize().x * upWallSmall->Scale().x * i), aisle->Position().y + aisle->TextureSize().x * 0.5f * aisle->Scale().x + upWallSmall->TextureSize().y * 0.5f * upWallSmall->Scale().y);
				vec_aisle_upWallSmalls.push_back(upWallSmall);

				class Sprite* backGround_edgeY2 = new Sprite(Textures + L"Stage/wall2.png", shaderFile, 591, 521, 604, 649);
				backGround_edgeY2->Scale(2, 2);
				backGround_edgeY2->RotationDegree(0.0f, 0.0f, 90.0f);
				backGround_edgeY2->Position(aisle->Position().x - aisle->TextureSize().y * 0.5f * aisle->Scale().y + backGround_edgeY2->TextureSize().y * 0.5f * backGround_edgeY2->Scale().y + (backGround_edgeY2->TextureSize().y * 0.5f * backGround_edgeY2->Scale().y * i), aisle->Position().y + aisle->TextureSize().x * 0.5f * aisle->Scale().x + upWallSmall->TextureSize().y * upWallSmall->Scale().y + backGround_edgeY2->TextureSize().x * 0.5f);
				
				edgevecTwo.push_back(backGround_edgeY2);
				
				if (edgevecTwo[i]->Position().x + edgevecOne[i]->TextureSize().y * 0.5f * edgevecOne[i]->Scale().y >= aisle->Position().x + aisle->TextureSize().y * 0.5f * aisle->Scale().y)
					edgevecTwo[i]->Position(aisle->Position().x + aisle->TextureSize().y * 0.5f * aisle->Scale().y - edgevecTwo[i]->TextureSize().y * 0.5f * aisle->Scale().y, aisle->Position().y + aisle->TextureSize().x * 0.5f * aisle->Scale().x + upWallSmall->TextureSize().y * upWallSmall->Scale().y + backGround_edgeY2->TextureSize().x * 0.5f);
			
				if (edgevecOne[i]->Position().x + edgevecTwo[i]->TextureSize().y * 0.5f * edgevecTwo[i]->Scale().y >= aisle->Position().x + aisle->TextureSize().y * 0.5f * aisle->Scale().y)
					edgevecOne[i]->Position(aisle->Position().x + aisle->TextureSize().y * 0.5f * aisle->Scale().y - edgevecOne[i]->TextureSize().y * 0.5f * aisle->Scale().y, aisle->Position().y - aisle->TextureSize().x * 0.5f * aisle->Scale().x - backGround_edgeY1->TextureSize().x * 0.5f);
			
				if (vec_aisle_upWallSmalls[i]->Position().x + vec_aisle_upWallSmalls[i]->TextureSize().x * 0.5f * vec_aisle_upWallSmalls[i]->Scale().x >= aisle->Position().x + aisle->TextureSize().y * 0.5f * aisle->Scale().y)
					vec_aisle_upWallSmalls[i]->Position(aisle->Position().x + aisle->TextureSize().y * 0.5f * aisle->Scale().y - vec_aisle_upWallSmalls[i]->TextureSize().x * 0.5f * vec_aisle_upWallSmalls[i]->Scale().x, aisle->Position().y + aisle->TextureSize().x * 0.5f * aisle->Scale().x + vec_aisle_upWallSmalls[i]->TextureSize().y * 0.5f * vec_aisle_upWallSmalls[i]->Scale().y);	
			}

			break;
		}

		default:
			break;
	}
	
	for (Sprite* aisles : vec_aisle)
		aisles->DrawBound(true);
	for (Sprite* aisles : edgevecOne)
		aisles->DrawBound(true);
	for (Sprite* aisles : edgevecTwo)
		aisles->DrawBound(true);
	
}

