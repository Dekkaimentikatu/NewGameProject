#pragma once
#include "game/base/UI_object.h"
#include "game/manager/map_manager.h"

constexpr int DISP_MOVE_LIMIT = 600;

constexpr float DISP_MOVE_SPEED = 20.0f;

class C_SELECT_DISP : public C_UI_OBJECT_BASE
{
protected:

	int m_hndl[C_MAP_MANAGER::SELECT_STAGE_MAX];

	VECTOR m_dispPos[C_MAP_MANAGER::SELECT_STAGE_MAX];

	VECTOR m_dispMove;

	float m_dispScale[C_MAP_MANAGER::SELECT_STAGE_MAX];

	int m_index;

	bool m_moveFlag;

	C_GLOBAL_DATA::T_PLAYER_DATA* m_playerData;

public:

	//コンストラクタ
	C_SELECT_DISP() : m_hndl(), m_index(0), m_dispPos(), m_dispMove(), m_dispScale(), m_playerData(nullptr), m_moveFlag(false) {}

	//デストラクタ
	virtual ~C_SELECT_DISP() {};

	//初期化
	void Init(VECTOR _pos);

	//読込
	virtual void LoadAnSync();

	//更新
	virtual void Step();

	//更新確定処理
	void Update();

	//描画
	void Draw();

	//終了
	void Exit();

	virtual void SetSize(int _sizeX, int _sizeY);

};

