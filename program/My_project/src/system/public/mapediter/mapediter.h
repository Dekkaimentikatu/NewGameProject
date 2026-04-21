#pragma once

#include <list>
#include <DxLib.h>
#include "game/base/object.h"
#include "game/stage/stage_loader.h"

static const char* FILE_PATH = "data/csv/stage/stage1.csv";

class C_MAP_EDITER
{
private:

	enum EDITER_MODE
	{
		EDITER_MODE_LOADSTAGE,
		EDITER_MODE_SELECT,
		EDITER_MODE_POSITION,
		EDITER_MODE_SCALE,
		EDITER_MODE_ROTATION,
		EDITER_MODE_MOVE_LEN,
		EDITER_MODE_NUM,
	};

	enum INPUT_MODE
	{
		INPUT_MODE_X,
		INPUT_MODE_Y,
		INPUT_MODE_Z,
		INPUT_MODE_NUM,
	};

private:

	int m_hndl;

	int m_moveDir;

	int m_moveLen;

	int m_editerMode;

	list<C_OBJECT_BASE*> c_objectArray;

	VECTOR m_pos;

	VECTOR m_scl;

	VECTOR m_rot;

	int m_index;

	int m_inputHndl;

	int m_inputState;

	char m_filePath[256];

	char m_prevfilePath[256];

	C_STAGE_LOADER m_stageLoader;

	void AddObject();

	void DeleteObject();

	void DeleteObjectAll();

public:

	//コンストラクタ
	C_MAP_EDITER(int _hndl = 0, int _moveDir = 0, int _moveLen = 0,
		int _editerMode = 0,VECTOR _pos = { 0 }, VECTOR _scl = { 0 }, 
		VECTOR _rot = { 0 }, int _index = 0, int _inputHndl = -1, int _inputState = 0):
	m_hndl(_hndl), m_moveDir(0), m_moveLen(_moveLen), m_editerMode(_editerMode),
	m_pos(_pos), m_scl(_scl), m_rot(_rot), m_index(_index), m_inputHndl(_inputHndl),
		m_inputState(_inputState), m_filePath(), m_prevfilePath(){}

	//デストラクタ
	~C_MAP_EDITER(){}

	void Init();

	void LoadAnSync();

	void LoadSync();

	void Step();

	void Update();

	void Draw();

	void Exit();

};