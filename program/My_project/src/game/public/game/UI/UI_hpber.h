#pragma once

#include "game/base/UI_object.h"

constexpr int HP_GRAPH_SIZEX = 512;
constexpr int HP_GRAPH_SIZEY = 16;

class C_UI_HPBER : public C_UI_OBJECT_BASE
{
protected:

	int m_hndl1;

	int m_hndl2;

	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

public:

	//コンストラクタ
	C_UI_HPBER(int _hndl1 = 0, int _hndl2 = 0):
	m_hndl1(_hndl1),m_hndl2(_hndl2),m_playerData(nullptr){}

	//デストラクタ
	virtual ~C_UI_HPBER() {};

	//初期化
	virtual void Init(VECTOR _pos);

	//読込
	virtual void LoadAnSync();

	//更新
	virtual void Step();

	//更新確定処理
	virtual void Update();

	//描画
	virtual void Draw();

	//終了
	void Exit();

	virtual void SetSize(int _sizeX, int _sizeY);

};
