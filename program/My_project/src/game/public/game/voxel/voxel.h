#pragma once
#include "common.h"

class C_VOXEL
{
public:

	//ボクセルのタイプ
	enum VOXEL_TYPE
	{
		BLOCK,
		AIR,
	};

	//ポリゴン描画フラグ
	enum DRAW_POLY_FLAG
	{
		UP		=	0x0001,
		DONW	=	0x0002,
		LEFT	=	0x0004,
		RIGHT	=	0x0008,
		FRONT	=	0x0010,
		REAR	=	0x0020,
	};

	//ボクセルのデータ
	typedef struct
	{
		//座標
		VECTOR pos;
		//拡大率
		VECTOR scale;
		//一辺の長さ(単位)
		float size;
		//画像ハンドル
		int grapHndl;
		//ボクセルのタイプ
		VOXEL_TYPE voxelType;
	}T_VOXEL_DATA;

private:

	//ボクセルのデータ
	T_VOXEL_DATA m_voxelData;

	//ポリゴン描画フラグ
	int m_drawFlag;

public:

	C_VOXEL(int _drawFlag = 0) : m_voxelData(), m_drawFlag(_drawFlag){}

	~C_VOXEL(){}

	//初期化
	void Init();

	//読込
	void Load();

	//更新
	void Step();

	//更新確定
	void Update();

	//描画
	void Draw();

	//終了
	void Exit();

	//リクエスト
	void Request(T_VOXEL_DATA _voxelData) { m_voxelData = _voxelData; }

	//フラグを立てる
	void OnFlag(DRAW_POLY_FLAG _drawFlag) { m_drawFlag &= _drawFlag; }

	//フラグを折る
	void OffFlag(DRAW_POLY_FLAG _drawFlag) { m_drawFlag != _drawFlag; }

	//座標を取得
	VECTOR GetPos() const { return m_voxelData.pos; }

	//拡大率を取得
	VECTOR GetScale() const { return m_voxelData.scale; }

	//一辺の長さを取得
	int GetSize() const { return m_voxelData.size; }

	//ボクセルのタイプを取得
	VOXEL_TYPE GetVoxelType() const { return m_voxelData.voxelType; }
};

