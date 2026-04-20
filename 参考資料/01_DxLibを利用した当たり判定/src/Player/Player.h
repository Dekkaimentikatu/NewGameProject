#pragma once

#include <DxLib.h>

class Player{
private:
	VECTOR	m_camRot;
	float	m_animCnt;
	float	m_gravity;
	int		m_state;
	int		m_hndl;
	int		m_animIndex;

public:
	Player();
	~Player();

	void	LoadData();
	void	Reset();
	void	Calc();
	void	CalcCamera();
	void	Draw();

	void	ReflectCollision(VECTOR addVec);
	VECTOR	GetCenter();
	float	GetRadius();

private:
	void	RequestAnim(int animID);
	bool	CalcMove();
	bool	CalcJump();
};
