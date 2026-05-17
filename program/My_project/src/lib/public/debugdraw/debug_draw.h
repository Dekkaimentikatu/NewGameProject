#pragma once
#include <DxLib.h>

class C_DEBUG_DRAW
{
public:

	// ワイヤーフレームボックス描画
	static void DrawBox3DWire(
		VECTOR minPos,
		VECTOR maxPos,
		unsigned int color)
	{
		VECTOR v[8];

		// 頂点作成
		v[0] = VGet(minPos.x, minPos.y, minPos.z);
		v[1] = VGet(maxPos.x, minPos.y, minPos.z);
		v[2] = VGet(maxPos.x, maxPos.y, minPos.z);
		v[3] = VGet(minPos.x, maxPos.y, minPos.z);

		v[4] = VGet(minPos.x, minPos.y, maxPos.z);
		v[5] = VGet(maxPos.x, minPos.y, maxPos.z);
		v[6] = VGet(maxPos.x, maxPos.y, maxPos.z);
		v[7] = VGet(minPos.x, maxPos.y, maxPos.z);

		// 手前面
		DrawLine3D(v[0], v[1], color);
		DrawLine3D(v[1], v[2], color);
		DrawLine3D(v[2], v[3], color);
		DrawLine3D(v[3], v[0], color);

		// 奥面
		DrawLine3D(v[4], v[5], color);
		DrawLine3D(v[5], v[6], color);
		DrawLine3D(v[6], v[7], color);
		DrawLine3D(v[7], v[4], color);

		// 接続線
		DrawLine3D(v[0], v[4], color);
		DrawLine3D(v[1], v[5], color);
		DrawLine3D(v[2], v[6], color);
		DrawLine3D(v[3], v[7], color);
	}
};
