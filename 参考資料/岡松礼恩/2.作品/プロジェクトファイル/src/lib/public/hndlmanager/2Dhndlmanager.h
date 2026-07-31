#pragma once

#include "common.h"

class C_2D_HNDL_MANAGER
{
private:

	//3Dモデルハンドルの情報
	//imagePath:モデルのファイルパス	
	//hndl:読み込まれたモデルのハンドル
	typedef struct
	{
		//画像のファイルパス
		string imageFilePath;
		//画像の総枚数
		int grapAllNum;
		//グラフィックハンドル
		int* hndl;
	}T_2D_HNDL_DATA;

	list<T_2D_HNDL_DATA> m_data;

	static C_2D_HNDL_MANAGER* m_instance;

	C_2D_HNDL_MANAGER() {}

	~C_2D_HNDL_MANAGER() = default;

	C_2D_HNDL_MANAGER(const C_2D_HNDL_MANAGER& other);
	C_2D_HNDL_MANAGER& operator = (const C_2D_HNDL_MANAGER& other);

public:

	//インスタンスの取得
	static C_2D_HNDL_MANAGER* GetInstance();

	//インスタンスの削除
	static void DeleteInstance();

	//画像の読み込み
	//@param char* _imgaeFilePath:読み込むモデルのファイルパス
	//@param int _AllNum:画像の分割総数
	//@param int _XNum:画像の縦の分割数
	//@param int _YNum:画像の横の分割数
	//@param int _XSize:画像の縦の分割サイズ(px)
	//@param int _YSize:画像の横の分割サイズ(px)
	void Load2DImage(const char* _imgaeFilePath, int _allNum = 1, int _XNum = 0, int _YNum = 0, int _XSize = 0, int _YSize = 0);

	//画像の取得
	//@param _modelFilePath:参照したいモデルのファイルパス
	//@returns 参照したモデルのハンドル
	int Get2DImageHndl(const char* _imgaeFilePath, int _graphNum = 0);

	//描画機能群
	int DrawRota(int* _graphID, VECTOR _pos, int _graphNum = 0, float _rate = 1.0f, float _angle = 0.0f, 
				int _traceFlag = TRUE, int _revarseX = 0, int _rebarseY = 0);

	int DrawModi(int* _graphID, VECTOR _pos, int sizeX, int sizeY,
				int _graphNum = 0, int _traceFlag = TRUE);

	int DrawRect(int* _graphID, VECTOR _pos, int _graphPosX, int _graphPosY,
				int sizeX, int sizeY, int _graphNum = 0, int _traceFlag = TRUE,
				int _revarseX = 0, int _rebarseY = 0);

	int DrawCircleGauge(int* _graphID, VECTOR _pos, double _percent, int _graphNum = 0,
						double _startPercent = 0.0, double _scale = 1.0f,int _revarseX = 0, int _rebarseY = 0);

	//画像情報の削除
	void Delete2DData(const char* _imgaeFilePath);

	//すべての画像情報の削除
	void DeleteAll2DData();
};
