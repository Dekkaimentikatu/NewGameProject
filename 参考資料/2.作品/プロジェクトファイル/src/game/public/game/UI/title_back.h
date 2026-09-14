#pragma once
#include "game/base/UI_object.h"

static const char* TITLE_BACK_GRAPH_PATH = "data/graphic/Title.png";

class C_TITLE_BACK : public C_UI_OBJECT_BASE
{
protected:

	int m_hndl1;

public:

	//コンストラクタ
	C_TITLE_BACK(int _hndl1 = 0) :m_hndl1(_hndl1){}

	//デストラクタ
	virtual ~C_TITLE_BACK() {};

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