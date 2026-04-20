#pragma once

#include <DxLib.h>
#include <vector>

using namespace std;

enum Effect_ID
{
	Rock,
	Iron,
	LowIron,
	Treasure,
	Enemy,

	E_ID,

};

class Effect_Data
{
protected:
	VECTOR m_pos;
	float m_animCount;
	int m_hndl[7][4];
	int m_index;
	bool m_isActive;
public:

	Effect_Data()
	{
		m_pos.x = 0;
		m_pos.y = 0;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_hndl[i][j] = -1;
			}
		}
		m_animCount = 0.0f;
		m_index = 0;
		m_isActive = false;
	}

	virtual void Init();

	virtual void Load();

	virtual void Step() {}

	virtual void Draw() {}

	virtual void Exit();

	virtual void Reqest() {}

	virtual bool End() { return true; }

	~Effect_Data()
	{

	}

	int* GetHndl()
	{
		return &m_hndl[0][0];
	}

};

class Block_Effect : public Effect_Data
{
public:
	Block_Effect()
	{
		m_pos.x = 0;
		m_pos.y = 0;
		m_animCount = 0.0f;
		m_index = 0;
		m_isActive = false;
	}

	~Block_Effect()
	{

	}

	void Init();

	void Load();

	void Step();

	void Draw(int offset, int* hndl);

	void Exit();

	void Reqest(VECTOR pos, int index);

	bool End();
};

//背景用データの初期化
void InitExplosion();
//背景データ読込
void LoadExplosion();
//背景データの毎フレーム更新処理
void StepExplosion();
//背景表示
void DrawExplosion();
//終了前に行う必要がある処理
void ExitExplosion();

//爆発エフェクト呼び出し
//@pos	:	エフェクトの表示場所
void RequestExplosion(VECTOR pos);

bool IsEndExplosion();

