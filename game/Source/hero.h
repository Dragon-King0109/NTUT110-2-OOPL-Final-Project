namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
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
		int  GetX1();						// ���W�� x �y��
		int  GetY1();						// ���W�� y �y��
		int  GetX2();						// �k�U�� x �y��
		int  GetY2();						// �k�U�� y �y��
		int  GetYSpeed();					// Y�t��
		void Initialize(int);				// �]�wHero����l��
		void LoadBitmap();					// ���J�ϧ�
		void OnMove(GameMap *m);			// ����Hero
		void OnShow(GameMap *m);			// �NHero�ϧζK��e��
		void SetMovingLeft(bool flag);		// �]�w�O�_���b��������
		void SetMovingRight(bool flag);		// �]�w�O�_���b���k����
		void SetMovingUp(bool flag);		// �]�w�O�_���b���W����
		void SetXY(int nx, int ny);			// �]�wHero���W���y��
		void Die();							// ���`�ᦩ���ͩR
		int  GetLife();						// �����e�ͩR��
		void SetStatus(bool alive);			// �]�w�ߪ����A
		bool GetStatus();					// �ˬd�ߪ����A
		void Reset(GameMap *m);				// �ߪ����A���]
		void Clear(GameMap *m);				// �ߪ���ƥ����M�����]
		void CheatCode(GameMap *m);			// �K��
		void StageClearCheck(GameMap *m);	// �q���t�α���
		~Hero();
	protected:
		CAnimation animation;		// Hero���ʵe
		bool Alive = true;
		int Life = 3;
		int xSpeed = 0, ySpeed = 0;
		int x, y;					// Hero���W���y��
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool jumpLock = 0;			// ���D��w
		int checkpointStatus = 0;	// ���~�I���A����
		int StageClearLock = 0;		// �q���I���A����
		int StageClearTemp = 1;		// �q������BGM����
		int FlagPoleSpeed = 0;		// �ԺX�t��
		int FlagPoleFrameCount = 0;	// �ԺX�ϥΡA�����V�ƥ�
	};
}