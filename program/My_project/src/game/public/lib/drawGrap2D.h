#pragma once

#include <DxLib.h>
#include <vector>

class grapPath
{
public:
	int m_ID;	//グラフィックID

	char m_pathString[128];	//ファイルパスの文字列

	int m_GrapWidth;	//グラフィックの幅

	int m_GrapHeight;	//グラフィックの高さ

	int m_GrapXNum;	//グラフィックの枚数

	int m_GrapYNum;	//グラフィックの枚数

	int m_GrapAllNum;	//グラフィックの枚数

	float m_AnimSpeed;	//グラフィックのスピード

	int* m_hndl;	//グラフィックハンドル

	float* m_animCount;	//グラフィックのアニメーションカウント

	int m_isMove;	//アニメーションフラグ

	int m_dispNum;	//最大表示枚数

	bool* m_isActive;	//生存フラグ
};

class C_DRAW_GRAP2D
{
private:
	C_DRAW_GRAP2D() = default;

	~C_DRAW_GRAP2D() = default;

	grapPath* m_path;	//グラフィックパス構造体のポインタ

	int m_grapCount;	//グラフィックの数

	static C_DRAW_GRAP2D* m_instance;

public:
	void InitGrap2D();	//初期化

	void LoadGrap2D();	//読込

	void UpdataGrap2D(int ID);		//更新

	void RequestGrap2D(int ID, int _dispNum);

	void RequestGrap2DAuto(int ID);

	void DeleteGrap2D(int ID, int _dispNum);

	void DeleteGrap2DAuto(int ID);

	void DrawGrap2D(int _grapID, VECTOR _pos, int _dispNum, int _dispID = 0, float _rate = 1.0f, bool turn = 0);	//描画

	void ExitGrap2D();	//終了

	void ResetGrap2D();	//m_endCheckをリセットする

	static C_DRAW_GRAP2D* GetInstance();

	static void DeleteInstance();
};