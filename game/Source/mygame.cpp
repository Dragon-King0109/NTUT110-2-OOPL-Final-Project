#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

		CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
		{
		}

		void CGameStateInit::OnInit()
		{
			//
			// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
			//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
			//
			ShowInitProgress(0);	// 一開始的loading進度為0%
			//
			// 開始載入資料
			//
			UI.LoadBitmap(IDB_UI);
			About.LoadBitmap(IDB_ABOUT);
			Instruct.LoadBitmap(IDB_INSTRUCTION);
			//Sleep(3000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
			//
			// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
			//
		}

		void CGameStateInit::OnBeginState()
		{
		}

		void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
		{
			const char KEY_ESC = 27;
			const char KEY_ENTER = 0x0d;

			const char KEY_LEFT = 0x25;
			const char KEY_RIGHT = 0x27;

			if (nChar == KEY_ENTER && counter == 2)
				GotoGameState(GAME_STATE_RUN);
			else if (nChar == KEY_ESC)
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			else if (nChar == KEY_ENTER) {
				counter++;
			}

		}

		void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
		{

			//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
		}

		void CGameStateInit::OnShow()
		{
			//
			// 貼上logo
			//
			if (counter == 0) {
				About.SetTopLeft(0, 0);
				About.ShowBitmap();
			}
			else if (counter == 1) {
				Instruct.SetTopLeft(0, 0);
				Instruct.ShowBitmap();
			}
			else {
				UI.SetTopLeft(0, 0);
				UI.ShowBitmap();
			}

		}							

		/////////////////////////////////////////////////////////////////////////////
		// 這個class為遊戲的結束狀態(Game Over)
		/////////////////////////////////////////////////////////////////////////////

		CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
		{
		}

		void CGameStateOver::OnMove()
		{
			counter--;
			if (counter < 0)

				GotoGameState(GAME_STATE_INIT);
			
		}

		void CGameStateOver::OnBeginState()
		{
			counter = 30 * 3; // 3 seconds
		}

		void CGameStateOver::OnInit()
		{
			//
			// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
			//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
			//
			ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
			//
			// 開始載入資料
			//
			//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
			//
			// 最終進度為100%
			//
			ShowInitProgress(100);
		}

		void CGameStateOver::OnShow()
		{
			CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
			CFont f,*fp;
			f.CreatePointFont(260,"Times New Roman");	// 產生 font f; 260表示26 point的字
			fp=pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(0,0,0));
			pDC->SetTextColor(RGB(255,255,0));
			char str[80];								// Demo 數字對字串的轉換
			sprintf(str, "Game Over ! (%d)", counter / 30);
			pDC->TextOut(370,425,str);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
		}


		/////////////////////////////////////////////////////////////////////////////
		// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
		/////////////////////////////////////////////////////////////////////////////

		CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
		{

		}

		CGameStateRun::~CGameStateRun()
		{

		}

		void CGameStateRun::OnBeginState()
		{
			
			if (LEVEL == 1) {
				Cat.Initialize(LEVEL);
				GameMap.Initialize(LEVEL);
				monster1.Initialize(600, 720);
				monster2.Initialize(1000, 720);
				monster3.Initialize(1400, 720);
				monster4.Initialize(2880, 480);
				monster5.Initialize(3180, 240);
				monster6.Initialize(3780, 720);
				monster7.Initialize(6000, 720);
				monster8.Initialize(6300, 720);
				monster9.Initialize(6900, 0);
				monster0.Initialize(6840, 0);
			}
			else if (LEVEL == 2) {
				Cat.Initialize(LEVEL);
				GameMap.Initialize(LEVEL);
				monster1.Initialize(660, 720);
				monster2.Initialize(2160, 720);
				monster3.Initialize(2340, 720);
				monster4.Initialize(2880, 0);
				monster5.Initialize(3000, 0);
				monster6.Initialize(3540, 720);
				monster7.Initialize(4080, 720);
				monster8.Initialize(4560, 240);
				monster9.Initialize(4860, 480);
				monster0.Initialize(5600, 720);
			}
			
			background.SetTopLeft(0,0);				// 設定背景的起始座標
			CAudio::Instance()->Play(AUDIO_LevelBGM, true);			// 撥放 WAVE
		}


		void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
		{
			//
			// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
			//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
			//
			ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
			//
			// 開始載入資料
			//
			
			monster1.LoadBitmap();
			monster2.LoadBitmap();
			monster3.LoadBitmap();
			monster4.LoadBitmap();
			monster5.LoadBitmap();
			monster6.LoadBitmap();
			monster7.LoadBitmap();
			monster8.LoadBitmap();
			monster9.LoadBitmap();
			monster0.LoadBitmap();
			GameMap.LoadBitmap();
			Cat.LoadBitmap();
			background.LoadBitmap(IDB_TEST, RGB(255, 255, 255));					// 載入背景的圖形
			//
			// 完成部分Loading動作，提高進度
			//
			ShowInitProgress(50);
			//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
			//
			// 繼續載入其他資料
			//
			GameMap.LoadSound();
			Cat.Reset(GameMap.ReturnGameMapPointer());
			black_BG.LoadBitmap(IDB_BLACK_BG);
			LifeCount.LoadBitmap(IDB_LIFE_COUNTER);
			CAudio::Instance()->Load(AUDIO_LevelBGM,  "sounds\\LevelBGM.mp3");	// 載入編號2的聲音ntut.mid
			CAudio::Instance()->Load(AUDIO_CatMarioDie, "sounds\\CatMarioDie.wav");
			//
			// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
			//
		}

		void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
		{
			const char KEY_LEFT  = 0x25; // keyboard左箭頭
			const char KEY_UP    = 0x26; // keyboard上箭頭
			const char KEY_RIGHT = 0x27; // keyboard右箭頭
			const char KEY_DOWN  = 0x28; // keyboard下箭頭
			if (nChar == KEY_LEFT)
				Cat.SetMovingLeft(true);
			if (nChar == KEY_RIGHT)
				Cat.SetMovingRight(true);
			if (nChar == KEY_UP)
				Cat.SetMovingUp(true);
		}

		void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
		{
			const char KEY_LEFT  = 0x25; // keyboard左箭頭
			const char KEY_UP    = 0x26; // keyboard上箭頭
			const char KEY_RIGHT = 0x27; // keyboard右箭頭
			const char KEY_DOWN  = 0x28; // keyboard下箭頭
			const char KEY_CHEAT = 0x43; // C
			if (nChar == KEY_LEFT)
				Cat.SetMovingLeft(false);
			if (nChar == KEY_RIGHT)
				Cat.SetMovingRight(false);
			if (nChar == KEY_UP)
				Cat.SetMovingUp(false);

			if (nChar == KEY_CHEAT)
				Cat.CheatCode(GameMap.ReturnGameMapPointer());
		}

		void CGameStateRun::OnMove()							// 移動遊戲元素
		{
			//////////////////////////////////////////
			///  Hero跟Monster的碰撞判定
			//////////////////////////////////////////
			monster0.HitHero(Cat.ReturnHeroPointer());
			monster1.HitHero(Cat.ReturnHeroPointer());
			monster2.HitHero(Cat.ReturnHeroPointer());
			monster3.HitHero(Cat.ReturnHeroPointer());
			monster4.HitHero(Cat.ReturnHeroPointer());
			monster5.HitHero(Cat.ReturnHeroPointer());
			monster6.HitHero(Cat.ReturnHeroPointer());
			monster7.HitHero(Cat.ReturnHeroPointer());
			monster8.HitHero(Cat.ReturnHeroPointer());
			monster9.HitHero(Cat.ReturnHeroPointer());

			//////////////////////////////////////////
			///  Hero跟Monster的Move
			//////////////////////////////////////////
			ShowLife = 0;
			Cat.OnMove(GameMap.ReturnGameMapPointer());
			if (LEVEL ==1) {
				monster1.OnMove(GameMap.ReturnGameMapPointer());
				monster2.OnMove(GameMap.ReturnGameMapPointer());
				monster3.OnMove(GameMap.ReturnGameMapPointer());
				if (Cat.GetX1() >= 2120) {
					monster4.OnMove(GameMap.ReturnGameMapPointer());
					monster5.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 3240) {
					monster6.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 3360) {
					monster7.OnMove(GameMap.ReturnGameMapPointer());
					monster8.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 6660) {
					monster9.OnMove(GameMap.ReturnGameMapPointer());
					monster0.OnMove(GameMap.ReturnGameMapPointer());
				}
			}
			else {
				monster1.OnMove(GameMap.ReturnGameMapPointer());
				if (Cat.GetX1() >= 1680) {
					monster2.OnMove(GameMap.ReturnGameMapPointer());
					monster3.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 2700) {
					monster4.OnMove(GameMap.ReturnGameMapPointer());
					monster5.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 3300) {
					monster6.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 3540) {
					monster7.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 4100) {
					monster8.OnMove(GameMap.ReturnGameMapPointer());
				}
				if (Cat.GetX1() >= 4220) {
					monster9.OnMove(GameMap.ReturnGameMapPointer());
				}
				monster0.OnMove(GameMap.ReturnGameMapPointer());
				
			}
			
			if (Cat.GetX1() >= 12000) {
				monster1.SetIsAlive(true);
				monster2.SetIsAlive(true);
				monster3.SetIsAlive(true);
				monster4.SetIsAlive(true);
				monster5.SetIsAlive(true);
				monster6.SetIsAlive(true);
				monster7.SetIsAlive(true);
				monster8.SetIsAlive(true);
				monster9.SetIsAlive(true);
				monster0.SetIsAlive(true);
				Cat.Clear(GameMap.ReturnGameMapPointer());
				if (LEVEL == 1) {
					LEVEL = 2;
					CAudio::Instance()->Stop(AUDIO_LevelBGM);
					GotoGameState(GAME_STATE_RUN);
				}
				else {
					LEVEL = 1;
					CAudio::Instance()->Stop(AUDIO_LevelBGM);
					GotoGameState(GAME_STATE_OVER);
				}
			}

			//////////////////////////////////////////
			///  Hero死亡判定
			//////////////////////////////////////////
			if (Cat.GetY1() >= 920 || !(Cat.GetStatus())) {
				CAudio::Instance()->Stop(AUDIO_LevelBGM);
				CAudio::Instance()->Play(AUDIO_CatMarioDie, false);
				///新增
				monster1.SetIsAlive(true);
				monster2.SetIsAlive(true);
				monster3.SetIsAlive(true);
				monster4.SetIsAlive(true);
				monster5.SetIsAlive(true);
				monster6.SetIsAlive(true);
				monster7.SetIsAlive(true);
				monster8.SetIsAlive(true);
				monster9.SetIsAlive(true);
				monster0.SetIsAlive(true);
				///
				Cat.Die();
				Cat.Reset(GameMap.ReturnGameMapPointer());
				black_BG.SetTopLeft(0, 0);
				black_BG.ShowBitmap();
				LifeCount.SetTopLeft(385, 415);
				LifeCount.ShowBitmap();
				Sleep(3000);										//延遲3秒
				ShowLife = Cat.GetLife();
				if (Cat.GetLife() <= 0) {
					LEVEL = 1;
					Cat.Clear(GameMap.ReturnGameMapPointer());
					GotoGameState(GAME_STATE_OVER);
				}
				else {
					GotoGameState(GAME_STATE_RUN);
				}
			}
		}

		void CGameStateRun::OnShow()
		{
			background.ShowBitmap();			// 貼上背景圖
			monster1.OnShow(GameMap.ReturnGameMapPointer());
			monster2.OnShow(GameMap.ReturnGameMapPointer());
			monster3.OnShow(GameMap.ReturnGameMapPointer());
			monster4.OnShow(GameMap.ReturnGameMapPointer());
			monster5.OnShow(GameMap.ReturnGameMapPointer());
			monster6.OnShow(GameMap.ReturnGameMapPointer());
			monster7.OnShow(GameMap.ReturnGameMapPointer());
			monster8.OnShow(GameMap.ReturnGameMapPointer());
			monster9.OnShow(GameMap.ReturnGameMapPointer());
			monster0.OnShow(GameMap.ReturnGameMapPointer());
			Cat.OnShow(GameMap.ReturnGameMapPointer());
			if (ShowLife !=0) {
				black_BG.SetTopLeft(0, 0);
				black_BG.ShowBitmap();
				LifeCount.SetTopLeft(385, 415);
				LifeCount.ShowBitmap();
				CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
				CFont f, *fp;
				f.CreatePointFont(640, "Times New Roman");	// 產生 font f; 260表示26 point的字
				fp = pDC->SelectObject(&f);					// 選用 font f
				pDC->SetBkColor(RGB(0, 0, 0));
				pDC->SetTextColor(RGB(255, 255, 255));
				char str[80];								// Demo 數字對字串的轉換
				sprintf(str, "%d", Cat.GetLife());
				pDC->TextOut(500, 402, str);
				pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
				CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
				Sleep(2000);
				
			}
		}
}