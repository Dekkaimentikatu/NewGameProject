#pragma once

#include <DxLib.h>
#include "../Model/Model.h"

class Player : public Model{
private:
	VECTOR	m_camRot;
	float	m_gravity;

public:
	Player();
	virtual ~Player();

	virtual void	LoadData();
	virtual void	Reset();
	virtual void	Step();
	void	Update();
	void	Draw();

	void	ReflectCollision(VECTOR addVec);
	VECTOR	GetCenter();
	float	GetRadius();
	void	SetCameraRot(VECTOR camRot){ m_camRot = camRot; }

	// 攻撃の当たり判定用
	bool IsAttack();
	VECTOR GetAttackPos();

private:
	//		歩き処理
	void	ExecWalk();
	//		走り処理
	void	ExecRun();
	//		待機処理
	void	ExecWait();
	//		しゃがみ処理
	void	ExecDown();
	//		しゃがみ攻撃処理
	void	ExecDownAttack();
	//		立ち攻撃1処理
	void	ExecAttack1();
	//		立ち攻撃2処理
	void	ExecAttack2();

	//		十字キーによる移動方向取得
	VECTOR	GetSpeed();
	//		速度をプレイヤーに反映させる
	void	CalcSpeed(VECTOR speed);

protected:
	//		重力更新
	void	UpdateGravity();
};
