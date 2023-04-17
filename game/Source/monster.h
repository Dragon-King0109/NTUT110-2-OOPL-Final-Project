namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class GameMap;
	class Hero;
	class Monster
	{
	public:
		Monster();
		bool IsAlive();						// 是否活著
		void Initialize(int X_POS, int Y_POS);					// 設定怪物為初始值
		void LoadBitmap();					// 載入圖形
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void OnMove(GameMap *m);			// 移動
		bool HitBox(Hero *h);				//Hitbox
		void HitHero(Hero *h);				// 碰撞怪物判定
		void OnShow(GameMap *m);			// 將圖形貼到畫面
		void SetXY(int nx, int ny);			// 設定圓心的座標
		void SetIsAlive(bool alive);		// 設定是否活著
		int GetXY();
		bool GetIsAlive();
		~Monster();
	protected:
		CAnimation bmp;				// 怪物的動畫
		int x, y;					// 怪物左上角座標
		int ySpeed;
		bool is_alive;				// 是否活著
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
	};
}