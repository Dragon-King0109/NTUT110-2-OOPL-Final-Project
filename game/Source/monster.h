namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class GameMap;
	class Hero;
	class Monster
	{
	public:
		Monster();
		bool IsAlive();						// �O�_����
		void Initialize(int X_POS, int Y_POS);					// �]�w�Ǫ�����l��
		void LoadBitmap();					// ���J�ϧ�
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void OnMove(GameMap *m);			// ����
		bool HitBox(Hero *h);				//Hitbox
		void HitHero(Hero *h);				// �I���Ǫ��P�w
		void OnShow(GameMap *m);			// �N�ϧζK��e��
		void SetXY(int nx, int ny);			// �]�w��ߪ��y��
		void SetIsAlive(bool alive);		// �]�w�O�_����
		int GetXY();
		bool GetIsAlive();
		~Monster();
	protected:
		CAnimation bmp;				// �Ǫ����ʵe
		int x, y;					// �Ǫ����W���y��
		int ySpeed;
		bool is_alive;				// �O�_����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
	};
}