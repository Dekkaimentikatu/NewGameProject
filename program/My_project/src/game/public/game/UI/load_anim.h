#pragma once

#include "game/base/UI_object.h"

constexpr int LOAD_GRAPH_MAX = 8;

static const char* LOAD_GRAPH_PATH = "data/graphic/load_anim.png";

constexpr int LOAD_GRAPH_X_NUM = 4;

constexpr int LOAD_GRAPH_Y_NUM = 2;

constexpr int LOAD_GRAPH_SIZE = 32;

class C_LOAD_ANIM : public C_UI_OBJECT_BASE
{
protected:

	int m_hndl[LOAD_GRAPH_MAX];

	int m_index;

public:

	//コンストラクタ
	C_LOAD_ANIM(int _index = 0) : m_hndl(), m_index(_index){}

	//デストラクタ
	~C_LOAD_ANIM() {};

	//初期化
	void Init(VECTOR _pos);

	//
	void LoadSync();

	//読込
	void LoadAnSync();

	void StepLoading();

	//更新
	void Step();

	//更新確定処理
	void Update();

	void DrawLoading();

	//描画
	void Draw();

	//終了
	void Exit();

	virtual void SetSize(int _sizeX, int _sizeY);

};