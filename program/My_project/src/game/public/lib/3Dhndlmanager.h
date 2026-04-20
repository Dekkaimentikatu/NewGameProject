#pragma once
#include "common.h"

class C_3D_HNDL_MANAGER
{
private:

	
	//3Dモデルハンドルの情報
	//imagePath:モデルのファイルパス	
	//hndl:読み込まれたモデルのハンドル
	typedef struct
	{
		string modelFilePath;
		int hnld;
	}T_3D_HNDL_DATA;

	list<T_3D_HNDL_DATA> m_data;

	static C_3D_HNDL_MANAGER* m_instance;

	C_3D_HNDL_MANAGER(){}

	~C_3D_HNDL_MANAGER() = default;

	C_3D_HNDL_MANAGER(const C_3D_HNDL_MANAGER& other);
	C_3D_HNDL_MANAGER& operator = (const C_3D_HNDL_MANAGER& other);

public:

	//インスタンスの取得
	static C_3D_HNDL_MANAGER* GetInstance();

	//インスタンスの削除
	static void DeleteInstance();

	//3Dモデルの読み込み
	//@param _modelFilePath:読み込むモデルのファイルパス
	void Load3DModel(const char *_modelFilePath);

	//指定した3Dモデルの削除
	//@param _modelFilePath:削除するモデルのファイルパス
	void Delete3DModel(const char* _modelFilePath);

	//全ての3Dモデルの削除
	void DeleteAll3DModel();

	//3Dモデルハンドルの取得
	//@param _modelFilePath:参照したいモデルのファイルパス
	//@returns 参照したモデルのハンドル
	int Get3DModelHndl(const char* _modelFilePath);

};
