#pragma once

#include <DxLib.h>
#include "../Player/Player.h"

// プレイヤーを継承するこの作りは危険すぎる！
class Enemy : public Player {
private:
	int m_rootHndl;		// ルート用のモデルハンドル
	int m_rootID;		// 今の自分の目的地
	int m_state;		// 敵の行動パターン

public:
	Enemy();
	virtual ~Enemy();

	virtual void	LoadData();
	virtual void	Reset();
	virtual void	Calc(VECTOR playerPos);
private:
	// ルートを歩く
	void MoveRoot();
	// ターゲットを追いかける
	void ChaceTarget(VECTOR targetPos);
	// ターゲットが近くにいるかを判定
	bool IsNearTarget(VECTOR targetPos, float radius);
};
