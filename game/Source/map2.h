namespace game_framework {

	class GameMap2 {  //�a�ϨC�欰60*60����
	public:
		GameMap2();
		GameMap2 * ReturnGameMapPointer() {
			GameMap2 * GameMap_ptr = this;
			return GameMap_ptr;
		}
		void LoadBitmap();
		void LoadSound();
		void Initialize();
		void OnMove(int, int);
		void OnShow(int);
		int ScreenX(int);
		int ScreenY(int);
		bool IsEmpty(int, int);
		bool JumpIsEmpty(int, int);
		bool IsBlock(int, int);
		int MapLoadRange();
		bool isCheckpoint();
		void CheatCode();
		void Reset();
		~GameMap2();
	private:
		int map[135][17];		//�a�Ϥj�p��135*15��(��16.17�����H�������ϥ�)
		int sx = 0, sy = 0;				//(sx, sy)��"�ù�"(�����W��)�b�a�ϤW���I�y��
		bool checkpoint = false;
		CMovingBitmap	block1;
		CMovingBitmap	block2;
		CMovingBitmap	block3;
		CMovingBitmap	QuestBlock;
		CMovingBitmap   QuestBlock2;
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