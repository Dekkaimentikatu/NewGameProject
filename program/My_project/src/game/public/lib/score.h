#pragma once
#include <DxLib.h>

class SCORE_DATA
{
private:
	static int m_hndl[10];
	static 	int m_soundHndl;
	static 	int m_score[10];
	static 	int m_dispScore[10];
public:
	static 	void Init();

	static 	void Load();

	static 	void Update();

	static 	void Draw(int x,int y,int _ID);

	static 	void Exit();

	static 	void Add(int score, int _ID);

	static 	void Set(int score, int _ID);

	static 	int Get(int _ID);
};


