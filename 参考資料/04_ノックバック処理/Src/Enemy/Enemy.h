#pragma once

#include <DxLib.h>
#include "../Player/Player.h"

class Enemy : public Player {
private:
	VECTOR m_speed;		// ノックバック用
	int m_rootHndl;		// ルート用のモデルハンドル
	int m_rootID;		// 今の自分の目的地
	int m_state;		// 敵の行動パターン

public:
	Enemy();
	virtual ~Enemy();

	virtual void	LoadData();
	virtual void	Reset();
	virtual void	Step(VECTOR playerPos);

	// ヒットした後の処理
	void HitCalc(VECTOR speed);

private:
	//	ルートを歩く
	void MoveRoot(VECTOR playerPos);
	//	ターゲットを追いかける
	void ChaceTarget(VECTOR playerPos);
	//	ノックバック
	void MoveBack();
	//	ターゲットが近くにいるか判定
	//	@radius	:	ここで設定した範囲内にいればtrueを返す
	bool IsNearTarget(VECTOR playerPos, float radius);

};
