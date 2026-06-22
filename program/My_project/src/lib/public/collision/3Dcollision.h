#pragma once

#include <DxLib.h>


//3Dの衝突判定用のOBB構造体
typedef struct
{
	VECTOR pos;
	VECTOR axis[3];
	float size[3];
}T_OBB;

class C_COLLISION
{
public:

	//箱同士の当たり判定
	static bool CheckHitBoxToBox(VECTOR pos1, VECTOR size1, VECTOR pos2, VECTOR size2);
	//カプセルと箱の当たり判定
	static bool CheckHitBoxToCapsule(VECTOR _boxPos, VECTOR _boxSize, VECTOR _capPos1, VECTOR _capPos2, float _capRedius);
	//球同士の当たり判定
	static bool CheckHitSphereToSphere(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius);
	//AABBと球の当たり判定
	static bool CheckHitAABBToSphere(VECTOR _sphereCenter, float _sphereRedius, VECTOR _AABBMax, VECTOR _AABBMin);
	//AABBと球の当たり判定
	static bool CheckHitAABBToSphere(VECTOR _sphereCenter, float _sphereRedius, VECTOR _AABBPos, float _AABBSize);
	//OBBと球の当たり判定
	static bool CheckHitOBBToSphere(VECTOR _sphereCenter, float _sphereredius, T_OBB _OBB);

};

