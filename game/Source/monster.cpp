#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "monster.h"
#include "hero.h"
#include "map.h"
#include "map2.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Monster: Monster class
	/////////////////////////////////////////////////////////////////////////////

	Monster::Monster()
	{
		is_alive = true;
		x = y = 0;
	}
	Monster::~Monster()
	{
	}

	void Monster::Initialize(int X_POS, int Y_POS)
	{
		x = X_POS;
		y = Y_POS;
		isMovingLeft = true;
		isMovingRight = false;
	}

	bool Monster::IsAlive()
	{
		return is_alive;
	}

	void Monster::LoadBitmap()
	{
		bmp.AddBitmap(IDB_MOB1_LEFT, RGB(255, 0, 0));			// 載入怪物的圖形
	}
	
	void Monster::OnMove(GameMap *m)
	{
		const int STEP_SIZE = 4;
		bmp.OnMove();
		if (!is_alive)
			return;
		if (isMovingLeft) {
			if (m->IsEmpty(x- STEP_SIZE, y))
				x -= STEP_SIZE;
			else {
				isMovingLeft = false;
				isMovingRight = true;
			}
		}
		if (isMovingRight) {
			if (m->IsEmpty(x + 60 + STEP_SIZE, y))
				x += STEP_SIZE;
			else {
				isMovingLeft = true;
				isMovingRight = false;
				x -= STEP_SIZE;
			}
		}
		if (isMovingRight) {
			if (m->IsEmpty(x + 60 + STEP_SIZE, y))
				x += STEP_SIZE;
			else {
				isMovingLeft = true;
				isMovingRight = false;
				x -= STEP_SIZE;
			}
		}

		
		if (m->IsEmpty(x + 10, y + 71) && m->IsEmpty(x + 30, y + 71) && m->IsEmpty(x + 49, y + 71)&& y >= 0) {
			y += 15;
			if (y >= 800) {
				y = -60;
			}
			isMovingLeft = false;
			isMovingRight = false;
			if (!(m->IsEmpty(x + 10, y + 71) && m->IsEmpty(x + 30, y + 71) && m->IsEmpty(x + 49, y + 71))) {
				isMovingLeft = true;
				isMovingRight = false;
			}
		}
	}

	bool Monster::HitBox(Hero *h) {
		if (h->GetX1() + 10 > x + 9 && h->GetX1() + 10 < x + 51 && h->GetY1() > y + 9 && h->GetY1() < y + 51) {	//貓左上
			return true;
		}
		else if (h->GetX1() + 49 > x + 9 && h->GetX1() + 49 < x + 51 && h->GetY1() > y + 9 && h->GetY1() < y + 51) {		//貓右上
			return true;
		}
		else if (h->GetX1() + 10 > x + 9 && h->GetX1() + 10 < x + 51 && h->GetY1() + 35 > y + 9 && h->GetY1() < y + 51) {		//貓左中
			return true;
		}
		else if (h->GetX1() + 49 > x + 9 && h->GetX1() + 49 < x + 51 && h->GetY1() + 35 > y + 9 && h->GetY1() < y + 51) {		//貓右中
			return true;
		}
		else if (h->GetX1() + 10 > x + 9 && h->GetX1() + 10 < x + 51 && h->GetY1() + 69 > y + 9 && h->GetY1() + 69 < y + 51) {	//貓左下
			return true;
		}
		else if (h->GetX1() + 49 > x + 9 && h->GetX1() + 49 < x + 51 && h->GetY1() + 69 > y + 9 && h->GetY1() + 69 < y + 51) {	//貓右下
			return true;
		}
		return false;
	}

	void Monster::HitHero(Hero *h) {
		if (HitBox(h) && h->GetStatus() && is_alive) {
			if (h->GetYSpeed() > 0) {
				is_alive = false;
			}
			else {
				h->SetStatus(false);
			}
		}
	}

	void Monster::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Monster::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Monster::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Monster::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Monster::OnShow(GameMap *m)
	{
		if (is_alive) {
			bmp.SetTopLeft(m->ScreenX(x), m->ScreenY(y));
			bmp.OnShow();
			m->OnShow(m->MapLoadRange());
		}
	}

	int Monster::GetXY() {
		return x;
	}

	bool Monster::GetIsAlive() {
		return is_alive;
	}
}