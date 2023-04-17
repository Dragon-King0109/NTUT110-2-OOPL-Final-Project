#include "hero.h"
#include "monster.h"
#include "map.h"
#include "map2.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_LevelBGM,				// 0
		AUDIO_CatMarioDie,			// 1
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap UI;								// csie的logo
		CMovingBitmap LEVEL1;
		CMovingBitmap LEVEL2;
		CMovingBitmap LEVEL3;
		CMovingBitmap LEVEL4;
		CMovingBitmap About;
		CMovingBitmap Instruct;
		int counter = 0;
	};

	class GameMap; 
	class Hero;

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		GameMap			GameMap;
		CMovingBitmap	background;	// 背景圖
		int ShowLife = 1;
		CMovingBitmap	black_BG;	// 背景圖
		CMovingBitmap	LifeCount;	// 背景圖
		Hero			Cat;
		Monster			monster1;
		Monster			monster2;
		Monster			monster3;
		Monster			monster4; 
		Monster			monster5;
		Monster			monster6; 
		Monster			monster7;
		Monster			monster8;
		Monster			monster9;
		Monster			monster0;
		int LEVEL = 1;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}