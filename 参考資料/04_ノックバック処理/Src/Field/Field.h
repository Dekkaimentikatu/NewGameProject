#pragma once
#include <DxLib.h>


class CField{
private:
	int	m_hndl;
	bool m_hitFlag;

public:
	CField();
	~CField();

	void	LoadData();
	void	Set();
	VECTOR	HitCheck(VECTOR center, float radius);
	VECTOR	HitCheck(VECTOR start, VECTOR end);
	void	Draw();
};
