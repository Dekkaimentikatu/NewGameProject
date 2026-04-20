#pragma once

#include <list>
#include <vector>
#include <DxLib.h>
#include "game/data/global_data.h"

using namespace std;

class C_OBJECT_BASE;

typedef struct
{
	int objectID;
	float posX;
	float posY;
	float posZ;
	float scaleX;
	float scaleY;
	float scaleZ;
	float rotX;
	float rotY;
	float rotZ;
	int moveDir;
	int moveLen;
}T_STAGE_DATA;



class C_STAGE_LOADER
{
public:

	enum OBJECT_ID
	{
		OBJECT_ID_BOX,
		OBJECT_ID_BOX_MOVE,
		OBJECT_ID_ROT_FLOOR,
		OBJECT_ID_DAMAGE_FLOOR,
		OBJECT_ID_ROT_DAMAGE,
		OBJECT_ID_HOLOBLOCK,
		OBJECT_ID_GOAL,
		OBJECT_ID_START,
		OBJECT_ID_CHECKPOINT,
		OBJECT_ID_ENEMY_SPAWN,
		OBJECT_ID_EMITTER,
		OBJECT_ID_BOARD,
		OBJECT_ID_MAX,
	};

private:

	//ファイル用ハンドル
	int m_hndl;

	//モデル用ハンドル
	vector<int> m_modelHndl;

	vector<int> m_graphicHndl;

	//情報を保存するためのリスト
	list<T_STAGE_DATA> m_stageDataList;

	list<T_STAGE_DATA> m_RedoList;

	C_GLOBAL_DATA* m_golobalData;

public:

	C_STAGE_LOADER(int _hndl = 0, C_GLOBAL_DATA* _globalData = nullptr) :
		m_hndl(_hndl), m_golobalData(_globalData){ }
	~C_STAGE_LOADER() {}

	void LoadMapResource();

	void LoadMapData(list<C_OBJECT_BASE*>& _objectArray, char* _filePath);

	void AddObject(T_STAGE_DATA _stageData, list<C_OBJECT_BASE*>& _objectArray);

	void AndoAddObject();

	void RedoAddObject(list<C_OBJECT_BASE*>& _objectArray);

	void DeleteObject(VECTOR _pos);

	void DeleteObjectAll();

	void SaveMapData(char* _filePath);

	void Exit();

	list<T_STAGE_DATA>& GetList() { return m_stageDataList; };
};