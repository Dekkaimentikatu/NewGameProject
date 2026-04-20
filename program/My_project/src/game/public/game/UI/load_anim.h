#pragma once

#include "game/base/UI_object.h"

class C_LOAD_ANIM : public C_UI_OBJECT_BASE
{
protected:

	int m_hndl1;

	int m_index;

public:

	//コンストラクタ
	C_LOAD_ANIM(int _hndl1 = 0, int _index = 0) : m_hndl1(_hndl1), m_index(_index){}

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