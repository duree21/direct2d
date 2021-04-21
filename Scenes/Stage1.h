#pragma once
#include "Scene.h"

class Stage1 : public Scene
{
public:
	Stage1(SceneValues* values);
	~Stage1();

	void Update() override;
	void Render() override;

	void EdgeMakerX(Sprite * room, vector<Sprite*>& vecOne, vector<Sprite*>& vecTwo);
	void EdgeMakerY(Sprite * room, vector<Sprite*>& vecOne, vector<Sprite*>& vecTwo);
	void WallMakerUp(Sprite* room, vector<Sprite*>& vecOne); 
	void WallMakerUpSmall(Sprite* room, vector<Sprite*>& vecOne, vector<Sprite*>& vecTwo);
	void AisleMaker(Sprite* roomOne, Sprite* roomTwo, vector<Sprite*>& edgevecOne, vector<Sprite*>& edgevecTwo, int selAislePos);

	// vector ////////////////////////////////////////
	// rooms ////////////////////////////////////////
private:
	class Sprite* backGround_groundStart;
	class Sprite* backGround_start; 
	class Sprite* backGround_one;
	class Sprite* backGround_bridge;
	class Sprite* backGround_two;
	class Sprite* backGround_three;
	class Sprite* backGround_boss;
	class Sprite* backGround_edge;
	class Sprite* upWall_mesure;

	// roomEdgesX ////////////////////////////////////////
private:
	vector<Sprite*> vec_groundStart_one;
	vector<Sprite*> vec_groundStart_two;	
	vector<Sprite*> vec_roomOne_one;
	vector<Sprite*> vec_roomOne_two;
	vector<Sprite*> vec_roomTwo_one;
	vector<Sprite*> vec_roomTwo_two;
	vector<Sprite*> vec_roomThree_one;
	vector<Sprite*> vec_roomThree_two;
	vector<Sprite*> vec_roomBoss_one;
	vector<Sprite*> vec_roomBoss_two;

	// roomEdgesY ////////////////////////////////////////
private:
	vector<Sprite*> vec_groundStart_edgeX1;
	vector<Sprite*> vec_groundStart_edgeX2;
	vector<Sprite*> vec_roomOne_edgeX1;
	vector<Sprite*> vec_roomOne_edgeX2;
	vector<Sprite*> vec_roomTwo_edgeX1;
	vector<Sprite*> vec_roomTwo_edgeX2;
	vector<Sprite*> vec_roomThree_edgeX1;
	vector<Sprite*> vec_roomThree_edgeX2;
	vector<Sprite*> vec_roomBoss_edgeX1;
	vector<Sprite*> vec_roomBoss_edgeX2;

	// upWalls, upWallSmalls ////////////////////////////////////////
private:
	vector<Sprite*> vec_upWall;

	vector<Sprite*> vec_groundStart_upWallSmall1; 
	vector<Sprite*> vec_groundStart_upWallSmall2;
	vector<Sprite*> vec_roomOne_upWallSmall1;
	vector<Sprite*> vec_roomOne_upWallSmall2;
	vector<Sprite*> vec_roomTwo_upWallSmall1;
	vector<Sprite*> vec_roomTwo_upWallSmall2;
	vector<Sprite*> vec_roomThree_upWallSmall1;
	vector<Sprite*> vec_roomThree_upWallSmall2;
	vector<Sprite*> vec_roomBoss_upWallSmall1;
	vector<Sprite*> vec_roomBoss_upWallSmall2;

	// aisles, aisleEdgesY ////////////////////////////////////////
private:
	vector<Sprite*> vec_aisle;

	vector<Sprite*> vec_aisle_edgeY1;
	vector<Sprite*> vec_aisle_edgeY2;
	vector<Sprite*> vec_aisle_edgeY3;
	vector<Sprite*> vec_aisle_edgeY4;
	vector<Sprite*> vec_aisle_edgeY5;
	vector<Sprite*> vec_aisle_edgeY6;

	vector<Sprite*> vec_aisle_upWallSmalls;

private:
	class Player* player;
	//class Bullet* bullet;
	class Fire* fire;
	class Weapon* weapon;
	class Weapon* mNormalWeapon;
	class Warp* warp_one;
	class Warp* warp_two;
	class Table* table;
	class Bullet* bullet;

	class Mnormal* mMon;

};