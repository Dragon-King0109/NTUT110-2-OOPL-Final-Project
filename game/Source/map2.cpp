#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "map2.h"

namespace game_framework {

	GameMap2::GameMap2() {		//載入地圖設定
	}

	GameMap2::~GameMap2() {		//載入地圖設定
	}

	void GameMap2::LoadBitmap() {
		block1.LoadBitmap(IDB_BLOCK1);
		block2.LoadBitmap(IDB_BLOCK2);
		block3.LoadBitmap(IDB_BLOCK3);
		QuestBlock.LoadBitmap(IDB_BLOCK_QUEST1);
		QuestBlock2.LoadBitmap(IDB_BLOCK_QUEST2);
		PipeLeft.LoadBitmap(IDB_PIPE_LEFT, RGB(255, 0, 0));
		PipeTopLeft.LoadBitmap(IDB_PIPE_TOPLEFT);
		PipeRight.LoadBitmap(IDB_PIPE_RIGHT, RGB(255, 0, 0));
		PipeTopRight.LoadBitmap(IDB_PIPE_TOPRIGHT);
		MidFlag.LoadBitmap(IDB_MIDFLAG, RGB(255, 0, 0));
		Flag.LoadBitmap(IDB_FLAG, RGB(255, 0, 0));
		FlagTop.LoadBitmap(IDB_FLAGTOP, RGB(255, 0, 0));
		Castle.LoadBitmap(IDB_CASTLE, RGB(0, 0, 255));
	}

	void GameMap2::LoadSound() {
		CAudio::Instance()->Load(2, "sounds\\BreakBlock2.wav");
		CAudio::Instance()->Load(3, "sounds\\GetCoin2.wav");
	}

	void GameMap2::Initialize() {
		const int X_POS = 0;				//遊戲視窗為 寬16 * 高15格 (960*900pixel)
		const int Y_POS = 0;				//貓的高度為100 pixel   一格為60*60pixel
		if (checkpoint) {
			sx = 3510;
		}
		else {
			sx = X_POS;
			sy = Y_POS;
		}
		for (int i = 0; i < 135; i++) {
			for (int j = 0; j < 15; j++) {
				if (j == 13 && i != 40 && i != 41 && i != 42 && i != 54 && i != 55 && i != 56 && i != 85 && i != 86 && i != 87 && i != 94 && i != 133 && i != 134) {
					map[i][j] = 1;
				}
				else if (j == 14 && i != 40 && i != 41 && i != 42 && i != 54 && i != 55 && i != 56 && i != 85 && i != 86 && i != 87 && i != 94 && i != 133 && i != 134) {
					map[i][j] = 2;
				}
				else
					map[i][j] = 0;
			}
		}
		//Part1 開局
		map[7][9] = 5;
		map[11][9] = 2;
		map[12][9] = 5;
		map[13][9] = 2, map[13][5] = 5;
		map[14][9] = 5;
		map[15][9] = 2;
		
		//Part2 水管設置
		map[20][12] = 11, map[20][11] = 11, map[20][10] = 12;
		map[21][12] = 13, map[21][11] = 13, map[21][10] = 14;
		map[29][12] = 11, map[29][11] = 11, map[29][10] = 11, map[29][9] = 12;
		map[30][12] = 13, map[30][11] = 13, map[30][10] = 13, map[30][9] = 14;

		//Part3 孔明磚
		map[40][9] = 30;
		map[46][9] = 2;
		map[47][9] = 5;
		map[48][9] = 2;
		map[49][5] = 2;
		map[50][5] = 2;
		map[51][5] = 2;
		map[52][5] = 2;
		map[53][5] = 2;
		map[57][5] = 2;
		map[58][5] = 2;
		map[59][5] = 2, map[59][9] = 2;

		//Part4 中繼點
		map[66][9] = 2, map[66][8] = 15;
		map[67][9] = 2;
		map[71][9] = 5;
		map[74][5] = 5;
		map[74][9] = 5;
		map[77][9] = 5;
		map[82][12] = 3;
		map[83][12] = 3, map[83][11] = 3;
		map[84][12] = 3, map[84][11] = 3, map[84][10] = 3;
		map[88][12] = 3, map[88][11] = 3, map[88][10] = 3;
		map[89][12] = 3, map[89][11] = 3, map[89][6] = 30;
		map[90][10] = 30, map[91][10] = 30, map[92][10] = 30, map[93][10] = 30, map[94][10] = 30;
		map[95][12] = 11, map[95][11] = 11, map[95][10] = 12;
		map[96][12] = 13, map[96][11] = 13, map[96][10] = 14;
		map[99][9] = 2, map[100][9] = 2, map[101][9] = 5, map[102][9] = 2;
		map[106][12] = 11, map[106][11] = 12;
		map[107][12] = 13, map[107][11] = 14;

		//Part5 最後的階梯
		map[108][12] = 3;
		map[109][12] = 3; map[109][11] = 3;
		map[110][12] = 3; map[110][11] = 3; map[110][10] = 3;
		map[111][12] = 3; map[111][11] = 3; map[111][10] = 3; map[111][9] = 3;
		map[112][12] = 3; map[112][11] = 3; map[112][10] = 3; map[112][9] = 3; map[112][8] = 3;
		map[113][12] = 3; map[113][11] = 3; map[113][10] = 3; map[113][9] = 3; map[113][8] = 3; map[113][7] = 3;
		map[114][12] = 3; map[114][11] = 3; map[114][10] = 3; map[114][9] = 3; map[114][8] = 3; map[114][7] = 3; map[114][6] = 3;
		map[115][12] = 3; map[115][11] = 3; map[115][10] = 3; map[115][9] = 3; map[115][8] = 3; map[115][7] = 3; map[115][6] = 3; map[115][5] = 3;
		map[116][12] = 3; map[116][11] = 3; map[116][10] = 3; map[116][9] = 3; map[116][8] = 3; map[116][7] = 3; map[116][6] = 3; map[116][5] = 3;

		//Part6 旗子
		map[122][12] = 3; map[122][11] = 40; map[122][10] = 40; map[122][9] = 40; map[122][8] = 40; map[122][7] = 40; map[122][6] = 40; map[122][5] = 40; map[122][4] = 41;
		//Part7 城堡
		map[127][6] = 50;
	}

	void GameMap2::OnMove(int x, int NowSpeed) {
		if(x - sx > 450 && sx < 7140)
			sx += NowSpeed;
	}

	void GameMap2::OnShow(int NowX) {
		for (int i = NowX; i < NowX+17; i++) {
			for (int j = 0; j < 15; j++) {
				int x = i * 60 - sx;
				int y = j * 60 - sy;
				switch (map[i][j]) {
				case 1:		//磚塊1
					block1.SetTopLeft(x, y);
					block1.ShowBitmap();
					break;
				case 2:		//磚塊2
					block2.SetTopLeft(x, y);
					block2.ShowBitmap();
					break;
				case 3:
					block3.SetTopLeft(x, y);
					block3.ShowBitmap();
					break;
				case 5:		//問號磚塊
					QuestBlock.SetTopLeft(x, y);
					QuestBlock.ShowBitmap();
					break;
				case 6:     //問號磚塊觸發完的
					QuestBlock2.SetTopLeft(x, y);
					QuestBlock2.ShowBitmap();
					break;
				case 11:     //左水管
					PipeLeft.SetTopLeft(x, y);
					PipeLeft.ShowBitmap();
					break;
				case 12:     //左水管頂部
					PipeTopLeft.SetTopLeft(x, y);
					PipeTopLeft.ShowBitmap();
					break;
				case 13:     //右水管
					PipeRight.SetTopLeft(x, y);
					PipeRight.ShowBitmap();
					break;
				case 14:     //右水管頂部
					PipeTopRight.SetTopLeft(x, y);
					PipeTopRight.ShowBitmap();
					break;
				case 15:	//中間點旗子
					MidFlag.SetTopLeft(x, y);
					MidFlag.ShowBitmap();
					break;
				case 40:     //旗子
					Flag.SetTopLeft(x, y);
					Flag.ShowBitmap();
					break;
				case 41:     //旗子
					FlagTop.SetTopLeft(x, y);
					FlagTop.ShowBitmap();
					break;
				case 50:
					Castle.SetTopLeft(x, y+50);
					Castle.ShowBitmap();
				}
			}
		}
	}

	int GameMap2::ScreenX(int x) {
		return x - sx;
	}

	int GameMap2::ScreenY(int y) {
		return y - sy;
	}

	bool GameMap2::IsEmpty(int x, int y) {
		int gx = x / 60;
		int gy = y / 60;
		if (map[gx][gy] == 15) {
			map[gx][gy] = 0;   //中繼點
			checkpoint = true;
			return true;
		}
		return map[gx][gy] == 0 || map[gx][gy] == 30 || map[gx][gy] == 40 || map[gx][gy] == 41 || y < 0;
	}

	bool GameMap2::JumpIsEmpty(int x, int y) {
		int gx = x / 60;
		int gy = y / 60;
		return map[gx][gy] == 0 || map[gx][gy] == 15 || map[gx][gy] == 40 || map[gx][gy] == 41 || y < 0;
	}

	bool GameMap2::IsBlock(int x, int y) {
		int gx = x / 60;
		int gy = y / 60;
		if (map[gx][gy] == 2) {
			map[gx][gy] = 0;   //撞到普通磚塊後設為空氣
			CAudio::Instance()->Play(2, false);
			return true;
		}
		if (map[gx][gy] == 5) {   
			map[gx][gy] = 6;   //撞到問號方塊後
			CAudio::Instance()->Play(3, false);
			return true;
		}
		if (map[gx][gy] == 30) {
			map[gx][gy] = 6;   //撞到孔明磚
			return true;
		}
		return false;
	}

	int GameMap2::MapLoadRange() {
		return sx / 60;
	}

	bool GameMap2::isCheckpoint() {
		return checkpoint;
	}

	void GameMap2::CheatCode() {
		sx = 7020;
	}

	void GameMap2::Reset() {
		checkpoint = false;
	}
}