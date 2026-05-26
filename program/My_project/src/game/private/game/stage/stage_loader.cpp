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
#include "hndlmanager/3Dhndlmanager.h"
#include "hndlmanager/2Dhndlmanager.h"

void C_STAGE_LOADER::LoadMapResource()
{
	C_3D_HNDL_MANAGER* hndlManager3D = C_3D_HNDL_MANAGER::GetInstance();
	//モデルの読み込み
	hndlManager3D->Load3DModel(BLOCK_MODEL_PATH);
	hndlManager3D->Load3DModel(BLOCK_MOVE_MODEL_PATH);
	hndlManager3D->Load3DModel(HOLO_BLOCK_MODEL_PATH);
	hndlManager3D->Load3DModel(GOAL_MODEL_PATH);
	hndlManager3D->Load3DModel(START_MODEL_PATH);
	hndlManager3D->Load3DModel(CHECK_POINT_MODEL_PATH);
	hndlManager3D->Load3DModel(ROT_FLOOR_MODEL_PATH);
	hndlManager3D->Load3DModel(DAMAGE_FLOOR_MODEL_PATH);
	hndlManager3D->Load3DModel(DARTS_MODEL_PATH);
	hndlManager3D->Load3DModel(BOARD_MODEL_PATH);

	C_2D_HNDL_MANAGER* hndlManager2D = C_2D_HNDL_MANAGER::GetInstance();
	//画像の読み込み
	hndlManager2D->Load2DImage(BOARD_IMAGE_PATH[0]);
	hndlManager2D->Load2DImage(BOARD_IMAGE_PATH[1]);
	hndlManager2D->Load2DImage(BOARD_IMAGE_PATH[2]);
	hndlManager2D->Load2DImage(BOARD_IMAGE_PATH[3]);
	hndlManager2D->Load2DImage(BOARD_IMAGE_PATH[4]);
	hndlManager2D->Load2DImage(BOARD_IMAGE_PATH[5]);
}

void C_STAGE_LOADER::LoadMapData(char* _filePath)
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
			FileRead_scanf(m_hndl, "%d,", &tmp.moveLen) == -1)
		{
			//読み込み失敗で終了
			break;
		}

		//ステージデータリストに情報を追加
		m_stageDataList.push_back(tmp);
	}

	//ファイルを閉じる
	FileRead_close(m_hndl);

	m_hndl = 0;
}

void C_STAGE_LOADER::LoadObject(list<shared_ptr<C_OBJECT_BASE>>& _objectList)
{
	for (auto itr = m_stageDataList.begin(); itr != m_stageDataList.end(); ++itr)
	{
		//オブジェクトの追加
		_objectList.push_back(AddObject((*itr)));
	}
}

shared_ptr<C_OBJECT_BASE> C_STAGE_LOADER::AddObject(T_STAGE_DATA _stageData)
{
	//ベースクラスのポインタ変数
	shared_ptr<C_OBJECT_BASE> tmp = nullptr;

	//オブジェクトに与えるデータ
	C_OBJECT_BASE::T_OBJECT_DATA data = { 0 };
	data.initPos = VGet(_stageData.posX, _stageData.posY, _stageData.posZ);
	data.modelScale = VGet(_stageData.scaleX, _stageData.scaleY, _stageData.scaleZ);
	data.modelRot = VGet(_stageData.rotX, _stageData.rotY, _stageData.rotZ);
	data.moveLen = _stageData.moveLen;

	//インスタンスの生成処理
	switch (_stageData.objectID)
	{
	case OBJECT_ID_BOX:
		tmp = make_shared<C_BLOCK>();
		break;
	case OBJECT_ID_BOX_MOVE:
		tmp = make_shared <C_BLOCK_MOVE>();
		break;
	case OBJECT_ID_ROT_FLOOR:
		tmp = make_shared <C_CIRCULAR_MOTION>();
		break;
	case OBJECT_ID_DAMAGE_FLOOR:
		tmp = make_shared <C_DAMAGE_FLOOR>();
		break;
	case OBJECT_ID_ROT_DAMAGE:
		tmp = make_shared <C_ROT_FLOOR>();
		break;
	case OBJECT_ID_HOLOBLOCK:
		tmp = make_shared <C_HOLO_BLOCK>();
		break;
	case OBJECT_ID_GOAL:
		tmp = make_shared <C_GOAL>();
		break;
	case OBJECT_ID_START:
		tmp = make_shared <C_START>();
		break;
	case OBJECT_ID_CHECKPOINT:
		tmp = make_shared <C_CHECK_POINT>();
		break;
	case OBJECT_ID_ENEMY_SPAWN:
		tmp = make_shared <C_ENEMY_SPAWN_POINT>();
		break;
	case OBJECT_ID_EMITTER:
		tmp = make_shared <C_DARTS_EMITTER>();
		break;
	case OBJECT_ID_BOARD:
		tmp = make_shared <C_BOARD>();
		break;
	}

	tmp->Init();
	tmp->Request(data);
	tmp->Load();

	return tmp;
}

void C_STAGE_LOADER::AndoAddObject(list<shared_ptr<C_OBJECT_BASE>>& _objectList)
{
	if (_objectList.size() == 0)return;
	if (m_stageDataList.size() == 0)return;
	auto itr1 = --m_stageDataList.end();
	auto itr2 = --_objectList.end();
	(*itr2)->Exit();
	itr2 = _objectList.erase(itr2);
	m_RedoList.push_back(*itr1);
	itr1 = m_stageDataList.erase(itr1);
}

void C_STAGE_LOADER::RedoAddObject(list<shared_ptr<C_OBJECT_BASE>>& _objectList)
{
	if (m_RedoList.size() == 0)return;
	auto itr = m_RedoList.begin();
	_objectList.push_back(AddObject((*itr)));
	m_RedoList.erase(itr);
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
		fprintf_s(fp, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d\n",
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
			(*itr).moveLen);
	}

	//ファイルを閉じる
	fclose(fp);
}

void C_STAGE_LOADER::Exit()
{

	for (auto itr = m_graphicHndl.begin(); itr != m_graphicHndl.end(); ++itr)
	{
		if (DeleteGraph((*itr)) == 0)
		{
			(*itr) = 0;
		}
	}

	C_3D_HNDL_MANAGER* hndlManager3D = C_3D_HNDL_MANAGER::GetInstance();
	//モデルの読み込み
	hndlManager3D->Delete3DModel(BLOCK_MODEL_PATH);
	hndlManager3D->Delete3DModel(BLOCK_MOVE_MODEL_PATH);
	hndlManager3D->Delete3DModel(HOLO_BLOCK_MODEL_PATH);
	hndlManager3D->Delete3DModel(GOAL_MODEL_PATH);
	hndlManager3D->Delete3DModel(START_MODEL_PATH);
	hndlManager3D->Delete3DModel(CHECK_POINT_MODEL_PATH);
	hndlManager3D->Delete3DModel(ROT_FLOOR_MODEL_PATH);
	hndlManager3D->Delete3DModel(DAMAGE_FLOOR_MODEL_PATH);
	hndlManager3D->Delete3DModel(DARTS_MODEL_PATH);
	hndlManager3D->Delete3DModel(BOARD_MODEL_PATH);

	C_2D_HNDL_MANAGER* hndlManager2D = C_2D_HNDL_MANAGER::GetInstance();
	//画像の読み込み
	hndlManager2D->Delete2DData(BOARD_IMAGE_PATH[0]);
	hndlManager2D->Delete2DData(BOARD_IMAGE_PATH[1]);
	hndlManager2D->Delete2DData(BOARD_IMAGE_PATH[2]);
	hndlManager2D->Delete2DData(BOARD_IMAGE_PATH[3]);
	hndlManager2D->Delete2DData(BOARD_IMAGE_PATH[4]);
	hndlManager2D->Delete2DData(BOARD_IMAGE_PATH[5]);

	m_modelHndl.clear();
	m_graphicHndl.clear();
	m_golobalData->GetEnemySpawnPointList()->clear();
	DeleteObjectAll();
}