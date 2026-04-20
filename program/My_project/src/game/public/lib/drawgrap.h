#pragma once

#include <DxLib.h>
#include <vector>

using namespace std;

class C_DRAW_GRAPH
{
private:

	C_DRAW_GRAPH(int _grapAllNum = 0) : m_graphAllNum(_grapAllNum) {}

	~C_DRAW_GRAPH() = default;

	C_DRAW_GRAPH(const C_DRAW_GRAPH& other);
	C_DRAW_GRAPH& operator = (const C_DRAW_GRAPH& other);

	typedef struct
	{
		int m_ID;	//グラフィックID

		const char* m_pathString;	//ファイルパスの文字列

		int m_grapNum;	//グラフィックの枚数

		int m_GrapWidth;	//グラフィックの幅

		int m_GrapHeight;	//グラフィックの高さ

		int m_GrapXNum;	//グラフィックの枚数

		int m_GrapYNum;	//グラフィックの枚数

	}T_LAOD_FILE_BUFFER;

	typedef struct
	{
		int* m_hndl;		//画像ハンドル

		int m_graphNum;	//読み込んだ画像の枚数

	}T_GRAP_DATA;

	vector<T_GRAP_DATA*> m_graphData;

	int m_graphAllNum;

	static C_DRAW_GRAPH* m_Instance;

public:

	static C_DRAW_GRAPH* GetInstance();

	static void DeleteInstance();

	void Init();

	int LoadGraphData(const char* _pathString, int _graphNum = 1, int _graphXnum = 0, int _graphYnum = 0, int _graphWight = 0, int _graphHeight = 0);

	int DrawRota(int _graphID, int _graphNum,VECTOR _pos, float _rate = 1.0f, float _angle = 0.0f, int _revarseX = 0, int _rebarseY = 0);

	int DrawModi(int _graphID, int _graphNum, VECTOR _pos, int sizeX, int sizeY);

	int DrawRect(int _graphID, int _graphNum, VECTOR _pos, int _graphPosX, int _graphPosY , int sizeX, int sizeY);

	int DrawCircleGauge(int _graphID, int _graphNum, VECTOR _pos, double _percent);

	int DeleteGraphData(int _graphID);

	int DeleteAllGrapData();

private:
		int LoadErrFunk();

};

