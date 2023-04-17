namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class GameMap;
	class Monster;
	class Hero
	{
	public:
		Hero();
		Hero* ReturnHeroPointer() {
			Hero * Hero_ptr = this;
			return Hero_ptr;
		}
		int  GetX1();						// 左上角 x 座標
		int  GetY1();						// 左上角 y 座標
		int  GetX2();						// 右下角 x 座標
		int  GetY2();						// 右下角 y 座標
		int  GetYSpeed();					// Y速度
		void Initialize(int);				// 設定Hero為初始值
		void LoadBitmap();					// 載入圖形
		void OnMove(GameMap *m);			// 移動Hero
		void OnShow(GameMap *m);			// 將Hero圖形貼到畫面
		void SetMovingLeft(bool flag);		// 設定是否正在往左移動
		void SetMovingRight(bool flag);		// 設定是否正在往右移動
		void SetMovingUp(bool flag);		// 設定是否正在往上移動
		void SetXY(int nx, int ny);			// 設定Hero左上角座標
		void Die();							// 死亡後扣除生命
		int  GetLife();						// 獲取當前生命數
		void SetStatus(bool alive);			// 設定貓的狀態
		bool GetStatus();					// 檢查貓的狀態
		void Reset(GameMap *m);				// 貓的狀態重設
		void Clear(GameMap *m);				// 貓的資料全部清除重設
		void CheatCode(GameMap *m);			// 密技
		void StageClearCheck(GameMap *m);	// 通關系統控制
		~Hero();
	protected:
		CAnimation animation;		// Hero的動畫
		bool Alive = true;
		int Life = 3;
		int xSpeed = 0, ySpeed = 0;
		int x, y;					// Hero左上角座標
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool jumpLock = 0;			// 跳躍鎖定
		int checkpointStatus = 0;	// 中繼點狀態紀錄
		int StageClearLock = 0;		// 通關點狀態紀錄
		int StageClearTemp = 1;		// 通關播放BGM紀錄
		int FlagPoleSpeed = 0;		// 拉旗速度
		int FlagPoleFrameCount = 0;	// 拉旗使用，紀錄幀數用
	};
}