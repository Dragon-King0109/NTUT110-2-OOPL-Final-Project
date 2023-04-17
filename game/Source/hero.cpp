#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "hero.h"
#include "map.h"

namespace game_framework {

	Hero::Hero()
	{	
		x = y = 0;
	}

	Hero::~Hero()
	{
	}

	int Hero::GetX1()
	{
		return x;
	}

	int Hero::GetY1()
	{
		return y;
	}

	int Hero::GetX2()
	{
		return x + animation.Width();
	}

	int Hero::GetY2()
	{
		return y + animation.Height();
	}

	int Hero::GetYSpeed() {
		return ySpeed;
	}

	void Hero::Initialize(int level)
	{	
		if (level == 2 && checkpointStatus == 1) {
			x = 3480;
			y = 600;
		}
		else if (checkpointStatus == 1) {
			x = 3960;
			y = 400;
		}
		else {
			x = 120;
			y = 120;
		}
		
		isMovingLeft = isMovingRight = isMovingUp = false;
	}

	void Hero::LoadBitmap()
	{
		animation.AddBitmap(IDB_CATMARIO_R, RGB(255, 0, 0));
		animation.AddBitmap(IDB_CATMARIO_L, RGB(255, 0, 0));
		CAudio::Instance()->Load(4, "sounds\\CatMatioJump.wav");
		CAudio::Instance()->Load(5, "sounds\\FlagPole.wav");
		CAudio::Instance()->Load(6, "sounds\\StageClear.wav");
	}

	void Hero::OnMove(GameMap *m)
	{
		StageClearCheck(m);
		if (StageClearLock == 0) {
			animation.OnMove();
			//左右
			if (isMovingLeft && !isMovingRight && xSpeed > -16)
				xSpeed -= 1;
			if (isMovingRight && xSpeed < 16)
				xSpeed += 1;

			//上下
			if (isMovingUp && jumpLock == 0) {
				if (ySpeed >= 0) {
					CAudio::Instance()->Play(4, false);
					ySpeed = -20;
				}
				else if (ySpeed > -35)
					if (m->IsEmpty(x + 10, y + 71 + ySpeed) && m->IsEmpty(x + 30, y + 71 + ySpeed) && m->IsEmpty(x + 49, y + 71 + ySpeed))
						ySpeed -= 3;
					else {
						jumpLock = 1;
						ySpeed = -ySpeed;
					}
				else
					jumpLock = 1;
			}
			else if (ySpeed < -20 && !isMovingUp && jumpLock == 0) {
				jumpLock = 1;
			}
			else if (ySpeed < 25) {
				if (ySpeed <= 15)
					ySpeed += 5;
				else
					ySpeed = 25;
			}

			//閒置時逐漸慢下來
			if (!isMovingLeft && xSpeed < 0) {
				if (xSpeed < -1)
					xSpeed += 2;
				else
					xSpeed = 0;
			}
			if (!isMovingRight && xSpeed > 0) {
				if (xSpeed > 1)
					xSpeed -= 2;
				else
					xSpeed = 0;
			}

			///////////////////////////////////////////
			/////////////////左右移動
			///////////////////////////////////////////
			if (xSpeed > 0) {  //向右
				if (m->IsEmpty(x + 51 + xSpeed, y) && m->IsEmpty(x + 51 + xSpeed, y + 35) && m->IsEmpty(x + 51 + xSpeed, y + 69) && m->ScreenX(x) <= 900) {
					x += xSpeed;
					m->OnMove(x, xSpeed);
				}
				else if (m->IsEmpty(x + 51, y) && m->IsEmpty(x + 51, y + 35) && m->IsEmpty(x + 51, y + 69) && m->ScreenX(x) <= 900) {
					for (int temp = 16; temp >= 0; temp--) {
						if (m->IsEmpty(x + 51 + temp, y) && m->IsEmpty(x + 51 + temp, y + 35) && m->IsEmpty(x + 51 + temp, y + 69)) {
							x += temp;
							break;
						}
					}
				}
			}
			if (xSpeed < 0) {
				if (m->IsEmpty(x + 9 + xSpeed, y) && m->IsEmpty(x + 9 + xSpeed, y + 35) && m->IsEmpty(x + 9 + xSpeed, y + 69) && m->ScreenX(x + xSpeed) > -10)
					x += xSpeed;
				else if (m->IsEmpty(x + 9, y) && m->IsEmpty(x + 9, y + 35) && m->IsEmpty(x + 9, y + 69) && m->ScreenX(x) >= 0) {
					for (int temp = -16; temp <= 0; temp++) {
						if (m->IsEmpty(x + 9 + temp, y) && m->IsEmpty(x + 9 + temp, y + 35) && m->IsEmpty(x + 9 + temp, y + 69) && m->ScreenX(x) > -10) {
							x += temp;
							break;
						}
					}
				}
			}

			///////////////////////////////////////////
			/////////////////上下移動
			///////////////////////////////////////////

			if (ySpeed < 0) {
				if (m->JumpIsEmpty(x + 10, y + ySpeed) && m->JumpIsEmpty(x + 30, y + ySpeed) && m->JumpIsEmpty(x + 49, y + ySpeed)) {
					y += ySpeed;
				}
				else if (m->JumpIsEmpty(x + 10, y - 1) && m->JumpIsEmpty(x + 30, y - 1) && m->JumpIsEmpty(x + 49, y - 1)) {
					y -= y - (y / 60) * 60 + 30;
					jumpLock = 1;
					if (ySpeed < -15)
						ySpeed = -ySpeed;
					else
						ySpeed = 15;

					if (m->IsBlock(x + 30, y - 1) == false)
						if (m->IsBlock(x + 49, y - 1) == false)
							m->IsBlock(x + 10, y - 1);
				}
			}

			if (ySpeed > 0) {
				if (m->IsEmpty(x + 10, y + 71 + ySpeed) && m->IsEmpty(x + 30, y + 71 + ySpeed) && m->IsEmpty(x + 49, y + 71 + ySpeed) || y > 800) {
					y += ySpeed;
				}
				else if (m->IsEmpty(x + 10, y + 71) && m->IsEmpty(x + 30, y + 71) && m->IsEmpty(x + 49, y + 71)) {
					y -= y - (y / 60 + 1) * 60 + 10;
					ySpeed = 0;
					jumpLock = 0;
				}
			}
			if (m->isCheckpoint()) {
				checkpointStatus = 1;
			}

			if (y > 820) {}
			else if (!(m->IsEmpty(x + 10, y + 71)) || !(m->IsEmpty(x + 30, y + 71)) || !(m->IsEmpty(x + 49, y + 71))) {
				ySpeed = 0;
			}
		}
		else { //通關過場
			if (StageClearTemp == 1) {
				CAudio::Instance()->Stop(0);
				CAudio::Instance()->Play(5, false);
				x = 7290;
				FlagPoleSpeed = (660 - y) / 30;
				StageClearTemp = 0;
			}
			else {
				if (FlagPoleFrameCount < 30) {
					y += FlagPoleSpeed;
				}
				else if (FlagPoleFrameCount == 40) {
					x = 7350;
					CAudio::Instance()->Play(6, false);
				}
				else if (FlagPoleFrameCount > 45 && FlagPoleFrameCount < 225) {
					y = 710;
					if (x < 7750) {
						x += 5;
					}else{
						x = 10000;
					}
				}
				else if (FlagPoleFrameCount == 225) {
					x = 13000;
				}
				FlagPoleFrameCount += 1;
			}
		}
	}

	void Hero::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Hero::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Hero::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Hero::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}


	void Hero::OnShow(GameMap *m)
	{
		m->OnShow(m->MapLoadRange());
		animation.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
		animation.OnShow();
	}

	void Hero::Die() 
	{
		Life -= 1;
	}

	int Hero::GetLife() 
	{
		return Life;
	}

	void Hero::SetStatus(bool alive) {
		Alive = alive;
	}

	bool Hero::GetStatus() {
		return Alive;
	}

	void Hero::Reset(GameMap *m)
	{
		Life = GetLife();
		xSpeed = 0;
		ySpeed = 0;
		StageClearLock = 0;
		StageClearTemp = 1;
		FlagPoleSpeed = 0;
		FlagPoleFrameCount = 0;
		Alive = true;
		jumpLock = 0;
	}

	void Hero::Clear(GameMap *m)
	{
		Life = 3;
		checkpointStatus = 0;
		xSpeed = 0;
		ySpeed = 0;
		StageClearLock = 0;
		StageClearTemp = 1;
		FlagPoleSpeed = 0;
		FlagPoleFrameCount = 0;
		Alive = true;
		jumpLock = 0;
		m->Reset();
	}

	void Hero::CheatCode(GameMap *m) {
		x = 7020;
		y = 600;
		m->CheatCode();
	}

	void Hero::StageClearCheck(GameMap *m) {
		if (x > 7290 && x < 7350 && y > 150) {
			StageClearLock = 1;
		}
	}
}