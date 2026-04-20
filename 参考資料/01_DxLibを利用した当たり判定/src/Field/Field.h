#pragma once
#include <DxLib.h>


class Field {
private:
	int	m_hndl;			// モデルハンドル
	bool m_isHitFlag;	// ヒットしているかどうかを判断(通常はいらない)

public:
	// コンストラクタ・デストラクタ
	Field();
	~Field();

	// データロード
	void LoadData();
	//当たり判定
	//@centor 当たり判定をする相手の座標
	//@radius 相手を球として判定するのでその半径
	//@return 押し戻す方向&距離
	VECTOR HitCheck(VECTOR center, float radius);
	// 描画
	void Draw();
};
