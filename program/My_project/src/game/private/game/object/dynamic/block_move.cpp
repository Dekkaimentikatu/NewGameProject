#include "game/object/dynamic/block_move.h"
#include "lib/2Ddirection/easing/easing.h"
#include "block_common.h"

C_BLOCK_MOVE::~C_BLOCK_MOVE()
{

}

void C_BLOCK_MOVE::Init()
{
	m_objectData = { 0 };
	m_moveVec = VGet(0.0f, 0.0f, 0.0f);
	m_modelHndl = -1;	//ハンドル
	m_speedUp = MAX_TIME;
}

void C_BLOCK_MOVE::Request(T_OBJECT_DATA _objectData)
{
	m_pos = m_objectData.initPos = _objectData.initPos;
	m_objectData.modelScale = _objectData.modelScale;
	m_objectData.modelRot.y = _objectData.modelRot.y;
	m_moveRot = _objectData.modelRot;
	m_objectType = OBJECT_TYPE_BLCOK;
	m_isActive = true;
	m_moveLen = _objectData.moveLen;
	m_moveDir = true;	//移動方向（true:正、false:負）
}

void C_BLOCK_MOVE::Load()
{
	c_globalData = C_GLOBAL_DATA::GetInstace();
	m_playerData = c_globalData->GetPlayerData();
	DuplicateModel(m_modelHndl);
	UpdateModel();
	SetUpCollInfo();
}

void C_BLOCK_MOVE::Step()
{
	//イージングの加減速
	if (!m_playerData->isStop)
	{
		m_speedUp += PLAYBACK_SPEED;
		if (m_speedUp >= MAX_TIME)m_speedUp = MAX_TIME;
	}
	else
	{
		m_speedUp -= PLAYBACK_SPEED;
		if (m_speedUp <= MIN_TIME)m_speedUp = MIN_TIME;
	}

	//移動ベクトル計算
	if (m_moveDir)
	{
		m_moveVec = VScale(MoveCalc(), BOSS_MOVE_SPEED);
	}
	else
	{
		m_moveVec = VScale(MoveCalc(), -BOSS_MOVE_SPEED);
	}

	//移動ベクトルにイージング処理
	m_moveVec = VScale(m_moveVec, C_EASING::InQuad<float>(m_speedUp, MAX_TIME));
	//位置更新
	m_pos = VAdd(m_pos, m_moveVec);

	//移動限界到達判定
	VECTOR tmp = VSub(m_pos, m_objectData.initPos);
	float len = VSize(tmp);
	if (len >= MOVE_LIMIT)
	{
		if (m_moveDir)m_moveDir = false;
		else m_moveDir = true;
	}

	if (m_playerData->isRespawn)
	{
		m_pos = m_objectData.initPos;
		m_moveDir = true;
	}
}

VECTOR C_BLOCK_MOVE::Circular()
{
	//ベクトルの外積で方向ベクトルを算出
	VECTOR vResult = VGet(m_moveLen * cosf(m_moveRot.y) + m_objectData.initPos.x, 0.0f,
		m_moveLen * sinf(m_moveRot.y) + m_objectData.initPos.z);

	return vResult;
}

VECTOR C_BLOCK_MOVE::Translation()
{
	//移動方向
	VECTOR moveDir = { 0.0f, 0.0f, -1.0f };
	//平行移動行列
	MATRIX dir = MGetTranslate(moveDir);
	//ヨー回転行列
	MATRIX mRotY = MGetRotY(m_moveRot.y);
	//ピッチ回転行列
	MATRIX mRotX = MGetRotX(m_moveRot.x);
	//計算
	MATRIX mResult = MMult(dir, mRotY);
	mResult = MMult(mResult, mRotX);

	//行列からベクトルを取得
	VECTOR vResult = { 0 };

	vResult.x = mResult.m[3][0];
	vResult.y = mResult.m[3][1];
	vResult.z = mResult.m[3][2];

	//正規化
	vResult = VNorm(vResult);

	return vResult;
}

VECTOR C_BLOCK_MOVE::MoveCalc()
{
	//移動方向
	VECTOR moveDir = { 0.0f, 0.0f, -1.0f };
	//平行移動行列
	MATRIX dir = MGetTranslate(moveDir);
	//ヨー回転行列
	MATRIX mRotY = MGetRotY(m_moveRot.y);
	//ピッチ回転行列
	MATRIX mRotX = MGetRotX(m_moveRot.x);
	//計算
	MATRIX mResult = MMult(dir, mRotY);
 	mResult = MMult(mResult, mRotX);

	//行列からベクトルを取得
	VECTOR vResult = {0};

	vResult.x = mResult.m[3][0];
	vResult.y = mResult.m[3][1];
	vResult.z = mResult.m[3][2];

	//正規化
	vResult = VNorm(vResult);

	return vResult;
}

void C_BLOCK_MOVE::Update()
{
	UpdateModel();
	UpdataCollInfo();
}

void C_BLOCK_MOVE::Draw()
{
	DrawModel();

#ifdef DEBUG_MODE

	//移動範囲表示
	auto LineLen = [](VECTOR _pos1, VECTOR _pos2, float _scale)
	{
		VECTOR tmp = VScale(_pos2, _scale);
		tmp = VAdd(_pos1, tmp);
		return tmp;
	};

	VECTOR tmp1 = LineLen(m_objectData.initPos, MoveCalc(), MOVE_LIMIT);
	VECTOR tmp2 = LineLen(m_objectData.initPos, MoveCalc(), -MOVE_LIMIT);

	DrawLine3D(tmp1, m_objectData.initPos, GetColor(255, 0, 0));
	DrawLine3D(tmp2, m_objectData.initPos, GetColor(0, 0, 255));

#endif

}

void C_BLOCK_MOVE::Exit()
{
	DeleteModel();
	DeleteCollInfo();
}

void C_BLOCK_MOVE::HitCalc()
{

}