#pragma once

#include <DxLib.h>

#include "game/data/global_data.h"

class C_UI_OBJECT_BASE
{
protected:

	//座標
	VECTOR m_pos;

	//UIの立幅
	int m_sizeX;

	//UIの横幅
	int m_sizeY;

	//データ管理クラス
	C_GLOBAL_DATA* c_golobalData;

public:

	//コンストラクタ
	C_UI_OBJECT_BASE(VECTOR _pos = { 0 }, int _sizeX = 0, int _sizeY = 0, C_GLOBAL_DATA* _golobalData = nullptr) :
		m_pos(_pos), m_sizeX(_sizeX), m_sizeY(_sizeY),c_golobalData(_golobalData){}

	//デストラクタ
	virtual ~C_UI_OBJECT_BASE() = default;

	//初期化
	virtual void Init(VECTOR _pos) = 0;

	//同期読込
	virtual void LoadSync() {}

	//非同期読込
	virtual void LoadAnSync() = 0;

	//読込中更新
	virtual void StepLoading(){}

	//更新
	virtual void Step() = 0;

	//更新確定処理
	virtual void Update() = 0;

	//読込中描画
	virtual void DrawLoading() {};

	//描画
	virtual void Draw() = 0;

	//終了
	virtual void Exit() = 0;

	//UIの大きさを設定
	virtual void SetSize(int _sizeX, int _sizeY) { m_sizeX = _sizeX; m_sizeY = _sizeY; }

	//座標の設定
	inline void SetPos(VECTOR _pos) { m_pos = _pos; }

};