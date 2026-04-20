#pragma once
#include <DxLib.h>

class Field {
private:
	int	m_hndl;
	bool m_isHitFlag;

public:
	Field();
	~Field();

	void	LoadData();
	void	Set();
	VECTOR	HitCheck(VECTOR center, float radius);
	VECTOR	HitCheckCamLine(VECTOR start, VECTOR end);
	void	Draw();
};
