#pragma once
#include <DxLib.h>

class CField {
private:
	int	m_hndl;
	bool m_isHitFlag;

public:
	CField();
	~CField();

	void	LoadData();
	void	Set();
	VECTOR	HitCheck(VECTOR center, float radius);
	VECTOR	HitCheckCamLine(VECTOR start, VECTOR end);
	void	Draw();
};
