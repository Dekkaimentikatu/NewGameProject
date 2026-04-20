#pragma once
#include "game/base/UI_object.h"

class C_BUTTON_TRG : public C_UI_OBJECT_BASE
{
private:

public:

	//初期化
	void Init(VECTOR _pos);

	//読込
	virtual void LoadAnSync();

	//更新
	virtual void Step();

	//更新確定処理
	void Update();

	//描画
	void Draw();

	//終了
	void Exit();

	virtual void SetSize(float _sizeX, float _sizeY);
};