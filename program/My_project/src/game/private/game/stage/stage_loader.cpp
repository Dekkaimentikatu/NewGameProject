#include "game/stage/stage_loader.h"

#include "game/base/manager_base.h"

#include "game/object/static/block.h"
#include "game/object/dynamic/block_move.h"
#include "game/object/dynamic/circular_motion.h"
#include "game/object/dynamic/rot_floor.h"
#include "game/object/dynamic/damage_floor.h"
#include "game/object/dynamic/holo_block.h"
#include "game/object/static/goal.h"
#include "game/object/static/start.h"
#include "game/object/static/check_point.h"
#include "game/object/static/enemy_spawn_point.h"
#include "game/object/static/darts_emitter.h"
#include "game/object/static/board.h"

void C_STAGE_LOADER::LoadMapResource()
{
	//モデルの読み込み
	m_modelHndl.push_back(MV1LoadModel("data/model/field/Floor_1.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/Floor_2.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/DamageFloor.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/goal.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/roulette1.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/roulette2.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/holo_block.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/paper_plane.mv1"));
	m_modelHndl.push_back(MV1LoadModel("data/model/field/board.mv1"));
	//画像の読み込み
	m_graphicHndl.push_back(LoadGraph("data/graphic/texture_01_black.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/texture_01_red.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/texture_02_white.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/holo.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/tutorial_move.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/tutorial_cam.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/tutorial_jump.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/tutorial_stop.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/tutorial_attack.png"));
	m_graphicHndl.push_back(LoadGraph("data/graphic/tutorial_denger.png"));
}

void C_STAGE_LOADER::LoadMapData(list<C_OBJECT_BASE*>& _objectArray, char* _filePath)
{
	m_hndl = FileRead_open(_filePath);

	//もしファイルが読み込めなかったら終了
	if (m_hndl == 0)return;

	T_STAGE_DATA tmp = { 0 };

	m_golobalData = C_GLOBAL_DATA::GetInstace();

	//ファイルの終端まで繰り返す
	while (FileRead_eof(m_hndl) == 0)
	{
		//データの読み込み
		if (FileRead_scanf(m_hndl, "%d,", &tmp.objectID) == -1 ||
			FileRead_scanf(m_hndl, "%f,", &tmp.posX) == -1 ||
			FileRead_scanf(m_hndl, "%f,", &tmp.posY) == -1 ||
			FileRead_scanf(m_hndl, "%f,", &tmp.posZ) == -1 ||
			FileRead_scanf(m_hndl, "%f,", &tmp.scaleX) == -1 ||
			FileRead_scanf(m_hndl, "%f,", &tmp.scaleY) == -1 || 
			FileRead_scanf(m_hndl, "%f,", &tmp.scaleZ) == -1 || 
			FileRead_scanf(m_hndl, "%f,", &tmp.rotX) == -1 || 
			FileRead_scanf(m_hndl, "%f,", &tmp.rotY) == -1 ||
			FileRead_scanf(m_hndl, "%f,", &tmp.rotZ) == -1 ||
			FileRead_scanf(m_hndl, "%d,", &tmp.moveDir) == -1 ||
			FileRead_scanf(m_hndl, "%d,", &tmp.moveLen) == -1)
		{
			//読み込み失敗で終了
			break;
		}
		else
		{
			//オブジェクトの生成
			AddObject(tmp, _objectArray);
		}
	}

	//ファイルを閉じる
	FileRead_close(m_hndl);

	m_hndl = 0;
}

void C_STAGE_LOADER::AddObject(T_STAGE_DATA _stageData,list<C_OBJECT_BASE*>& _objectArray)
{
	//各オブジェクトのポインタ変数
	C_BLOCK* block = nullptr;
	C_BLOCK_MOVE* floor = nullptr;
	C_ROT_FLOOR* rotFloor = nullptr;
	C_CIRCULAR_MOTION* circular = nullptr;
	C_DAMAGE_FLOOR* damageFloor = nullptr;
	C_HOLO_BLOCK* holoBlock = nullptr;
	C_GOAL* goal = nullptr;
	C_START* start = nullptr;
	C_CHECK_POINT* checkPoint = nullptr;
	C_ENEMY_SPAWN_POINT* spawnPoint = nullptr;
	C_DARTS_EMITTER* emitter = nullptr;
	C_BOARD* board = nullptr;

	//
	C_GLOBAL_DATA::T_ENEMY_SPOWN tmpSpawnData = {0};

	//
	int objectID = _stageData.objectID;
	VECTOR pos = VGet(_stageData.posX,_stageData.posY,_stageData.posZ);
	VECTOR scale = VGet(_stageData.scaleX,_stageData.scaleY,_stageData.scaleZ);
	VECTOR rot = VGet(_stageData.rotX, _stageData.rotY, _stageData.rotZ);
	int moveDir = _stageData.moveDir;
	int moveLen = _stageData.moveLen;

	//インスタンスの生成処理
	switch (_stageData.objectID)
	{
	case OBJECT_ID_BOX:
		block = new C_BLOCK;
		block->Init();
		block->Request(pos, scale, rot, m_modelHndl[0]);
		block->Load();
		_objectArray.push_back(block);
		break;
	case OBJECT_ID_BOX_MOVE:
		floor = new C_BLOCK_MOVE;
		floor->Init();
		floor->Request(pos, scale, rot, moveLen, m_modelHndl[1]);
		floor->Load();
		_objectArray.push_back(floor);
		break;
	case OBJECT_ID_ROT_FLOOR:
		circular = new C_CIRCULAR_MOTION;
		circular->Init(); 
		circular->Request(pos, scale, rot,
			m_modelHndl[1], m_graphicHndl[0],
				moveDir, static_cast<float>(moveLen));
		circular->Load();
		_objectArray.push_back(circular);
		break;
	case OBJECT_ID_DAMAGE_FLOOR:
		damageFloor = new C_DAMAGE_FLOOR;
		damageFloor->Init();
		damageFloor->Request(pos, scale, rot, m_modelHndl[2], moveDir, m_graphicHndl[2], m_graphicHndl[1]);
		damageFloor->Load();
		_objectArray.push_back(damageFloor);
		break;
	case OBJECT_ID_ROT_DAMAGE:
		rotFloor= new C_ROT_FLOOR;
		rotFloor->Init();
		rotFloor->Request(pos, scale, rot, m_modelHndl[4],moveDir, static_cast<float>(moveLen));
		rotFloor->Load();
		_objectArray.push_back(rotFloor);
		rotFloor = new C_ROT_FLOOR;
		rotFloor->Init();
		rot.y += 3.14f/ 2.0f;
		rotFloor->Request(pos, scale, rot, m_modelHndl[5], moveDir, static_cast<float>(moveLen));
		rotFloor->SetIsAttack(true);
		rotFloor->Load();
		_objectArray.push_back(rotFloor);
		break;
	case OBJECT_ID_HOLOBLOCK:
		holoBlock = new C_HOLO_BLOCK;
		holoBlock->Init();
		holoBlock->Request(pos, scale, rot, m_modelHndl[6], m_graphicHndl[0], m_graphicHndl[3],
			moveLen);
		holoBlock->Load();
		_objectArray.push_back(holoBlock);
		break;
	case OBJECT_ID_GOAL:
		goal = new C_GOAL;
		goal->Init();
		goal->Request(pos, scale, rot, m_modelHndl[3]);
		goal->Load();
		_objectArray.push_back(goal);
		break;
	case OBJECT_ID_START:
		start = new C_START;
		start->Init();
		start->Request(pos, scale, rot, m_modelHndl[3]);
		start->Load();
		_objectArray.push_back(start);
		break;
	case OBJECT_ID_CHECKPOINT:
		checkPoint = new C_CHECK_POINT;
		checkPoint->Init();
		checkPoint->Request(pos, scale, rot, m_modelHndl[3]);
		checkPoint->Load();
		_objectArray.push_back(checkPoint);
		break;
	case OBJECT_ID_ENEMY_SPAWN:
		spawnPoint = new C_ENEMY_SPAWN_POINT;
		spawnPoint->Init();
		spawnPoint->Request(pos, scale, rot, m_modelHndl[3]);
		spawnPoint->Load();
		tmpSpawnData.pos = pos;
		tmpSpawnData.scale = scale;
		tmpSpawnData.rot = rot;
		_objectArray.push_back(spawnPoint);
		m_golobalData->GetEnemySpawnPointList()->push_back(tmpSpawnData);
		break;
	case OBJECT_ID_EMITTER:
		emitter = new C_DARTS_EMITTER;
		emitter->Init();
		emitter->Request(pos, scale, rot, m_modelHndl[7], moveLen);
		emitter->Load();
		_objectArray.push_back(emitter);
		break;
	case OBJECT_ID_BOARD:
		board = new C_BOARD;
		board->Init();
		board->Request(pos, scale, rot, m_modelHndl[8], m_graphicHndl[moveLen]);
		board->Load();
		_objectArray.push_back(board);
		break;
	}

	//ステージデータリストに情報を追加
	m_stageDataList.push_back(_stageData);
}

void C_STAGE_LOADER::AndoAddObject()
{
	auto itr = m_stageDataList.end();
	if (itr == m_stageDataList.begin())return;
	m_RedoList.push_back(*(--itr));
	m_stageDataList.erase(--itr);
}

void C_STAGE_LOADER::RedoAddObject(list<C_OBJECT_BASE*>& _objectArray)
{
	auto itr = m_RedoList.end();
	if (itr == m_RedoList.begin())return;
	AddObject(*(--itr), _objectArray);
	m_stageDataList.push_back(*(--itr));
}

void C_STAGE_LOADER::DeleteObject(VECTOR _pos)
{
	for (auto itr = m_stageDataList.begin(); itr != m_stageDataList.end(); ++itr)
	{
		if ((*itr).posX == _pos.x &&
			(*itr).posY == _pos.y &&
			(*itr).posZ == _pos.z)
		{
			//ステージデータリストから情報を削除
			m_stageDataList.erase(itr);
			return;
		}
	}
}

void C_STAGE_LOADER::DeleteObjectAll()
{
	m_stageDataList.clear();
}

void C_STAGE_LOADER::SaveMapData(char* _filePath)
{
	FILE* fp = nullptr;

	//ファイルの読込
	fopen_s(&fp, _filePath, "w");

	if (fp == nullptr)return;

	//ステージデータを保存
	for (auto itr = m_stageDataList.begin(); itr != m_stageDataList.end(); ++itr)
	{
		//ファイルに情報を保存
		fprintf_s(fp, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d\n",
			(*itr).objectID,
			(*itr).posX,
			(*itr).posY,
			(*itr).posZ,
			(*itr).scaleX,
			(*itr).scaleY,
			(*itr).scaleZ,
			(*itr).rotX,
			(*itr).rotY,
			(*itr).rotZ,
			(*itr).moveDir,
			(*itr).moveLen);
	}

	//ファイルを閉じる
	fclose(fp);
}

void C_STAGE_LOADER::Exit()
{
	//ハンドルを解放
	for (auto itr = m_modelHndl.begin(); itr != m_modelHndl.end(); ++itr)
	{
		if (MV1DeleteModel((*itr)) == 0)
		{
			(*itr) = 0;
		}
	}

	for (auto itr = m_graphicHndl.begin(); itr != m_graphicHndl.end(); ++itr)
	{
		if (DeleteGraph((*itr)) == 0)
		{
			(*itr) = 0;
		}
	}

	m_modelHndl.clear();
	m_graphicHndl.clear();
	m_golobalData->GetEnemySpawnPointList()->clear();
	DeleteObjectAll();
}