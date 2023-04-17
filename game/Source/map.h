namespace game_framework {

	class GameMap {  //地圖每格為60*60像素
	public:
		GameMap();
		GameMap * ReturnGameMapPointer() {
			GameMap * GameMap_ptr = this;
			return GameMap_ptr;
		}
		void LoadBitmap();
		void LoadSound();
		void Initialize(int);
		void OnMove(int, int);
		void OnShow(int);
		int ScreenX(int);
		int ScreenY(int);
		bool IsEmpty(int, int);
		bool JumpIsEmpty(int, int);
		bool IsBlock(int, int);
		bool IsFake(int, int);
		int MapLoadRange();
		bool isCheckpoint();
		void CheatCode();
		void Reset();
		~GameMap();
	private:
		int map[135][17];		//地圖大小為135*15格(第16.17格讓人物掉落使用)
		int sx = 0, sy = 0;				//(sx, sy)為"螢幕"(的左上角)在地圖上的點座標
		bool checkpoint = false;
		CMovingBitmap	block1;
		CMovingBitmap	block2;
		CMovingBitmap	block3;
		CMovingBitmap	fakeblock;
		CMovingBitmap	QuestBlock;
		CMovingBitmap   QuestBlock2;
		CMovingBitmap	AirBlock;
		CMovingBitmap   PipeLeft;
		CMovingBitmap	PipeTopLeft;
		CMovingBitmap	PipeRight;
		CMovingBitmap	PipeTopRight;
		CMovingBitmap   MidFlag;
		CMovingBitmap	Flag;
		CMovingBitmap	FlagTop;
		CMovingBitmap   Castle;
	};
}