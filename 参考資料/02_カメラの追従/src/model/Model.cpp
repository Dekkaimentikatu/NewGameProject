#include "Model.h"

// 定義関連
static const VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
static const VECTOR DEFAULT_SCALE = { 1.0f, 1.0f, 1.0f };

// アニメ再生タイプ
enum {
	ANIMSTATE_NORMAL = 0,	// 終了後デタッチする(多分使わない)
	ANIMSTATE_LOOP,			// 繰返しループ
	ANIMSTATE_END,			// 最終フレームで停止

	ANIMSTATE_NUM
};

//------------------------------
//		コンストラクタ
//------------------------------
Model::Model() : m_pos(VECTOR_ZERO), m_rot(VECTOR_ZERO), m_scale(DEFAULT_SCALE)
, m_hndl(-1)
{
	ZeroMemory(&m_animData, sizeof(m_animData));
}


//------------------------------
//		デストラクタ
//------------------------------
Model::~Model()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}


//---------------------------------
//		初期化
//---------------------------------
void	Model::Init()
{
	Exit();
	m_pos = VECTOR_ZERO;
	m_rot = VECTOR_ZERO;
	m_scale = VECTOR_ZERO;
	ZeroMemory(&m_animData, sizeof(m_animData));
	m_animData.m_hndl = -1;
	m_animData.m_id = -1;
}


//---------------------------------
//		終了処理
//---------------------------------
void	Model::Exit()
{
	MV1DeleteModel(m_hndl);
}


//---------------------------------
//		更新処理
//---------------------------------
void	Model::Update()
{
	MV1SetPosition(m_hndl, m_pos);
	MV1SetRotationXYZ(m_hndl, m_rot);
	MV1SetScale(m_hndl, m_scale);
}


//------------------------------
//		データ読み込み
//------------------------------
bool	Model::LoadModel(const char* fileName)
{
	if (m_hndl != -1)
	{
		return false;		// モデル読み込み済み
	}

	m_hndl = MV1LoadModel(fileName);
	if (m_hndl == -1)
	{
		return false;		// モデルの読み込み失敗
	}
	return true;
}


//------------------------------
//		コピーデータ読み込み
//------------------------------
bool	Model::DuplicateModel(int srcHndl)
{
	if (m_hndl != -1)
	{
		return false;		// モデル読み込み済み
	}

	m_hndl = MV1DuplicateModel(srcHndl);
	if (m_hndl == -1)
	{
		return false;		// モデルの読み込み失敗
	}
	return true;
}


//---------------------------------
//		モデルデータ削除
//---------------------------------
void	Model::DeleteModel()
{
	if (m_hndl == -1) return;

	MV1DeleteModel(m_hndl);
	m_hndl = -1;
}


//---------------------------------
//		モデルデータ描画
//---------------------------------
void	Model::Draw()
{
	MV1DrawModel(m_hndl);
}


//---------------------------------
//		アニメアップデート
//---------------------------------
void	Model::UpdateAnim()
{
	if (m_animData.m_hndl != -1)
	{
		m_animData.m_frm += m_animData.m_spd;

		if (m_animData.m_frm >= m_animData.m_endFrm)
		{
			// 最終フレームまで来たら、状態に合わせて動作を変える
			switch (m_animData.m_state)
			{
				// 通常は終了させる
			case ANIMSTATE_NORMAL:
				DetachAnim();
				m_animData.m_endFrm = 0.f;
				m_animData.m_frm = 0.0f;
				m_animData.m_spd = 0.0f;
				return;
				// ループは最初に戻るだけ
			case ANIMSTATE_LOOP:
				m_animData.m_frm = 0.0f;
				break;
				// エンドループは最後で止める
			case ANIMSTATE_END:
				m_animData.m_frm = m_animData.m_endFrm;
				break;
			}
		}

		// 再生時間設定
		MV1SetAttachAnimTime(m_hndl, m_animData.m_hndl, m_animData.m_frm);

	}
}


//---------------------------------
//		アニメリクエスト
//---------------------------------
void	Model::Request(int animID, float animSpd, int animSrcHndl, bool nameCheck)
{
	DetachAnim();

	m_animData.m_hndl = MV1AttachAnim(m_hndl, animID, animSrcHndl, nameCheck);
	m_animData.m_id = animID;
	m_animData.m_endFrm = MV1GetAnimTotalTime(m_hndl, animID);
	m_animData.m_frm = 0.f;
	m_animData.m_spd = animSpd;
	m_animData.m_state = ANIMSTATE_NORMAL;
}


//---------------------------------
//		ループアニメリクエスト
//---------------------------------
void	Model::RequestLoop(int animID, float animSpd, int animSrcHndl, bool nameCheck)
{
	DetachAnim();

	m_animData.m_hndl = MV1AttachAnim(m_hndl, animID, animSrcHndl, nameCheck);
	m_animData.m_id = animID;
	m_animData.m_endFrm = MV1GetAnimTotalTime(m_hndl, animID);
	m_animData.m_frm = 0.f;
	m_animData.m_spd = animSpd;
	m_animData.m_state = ANIMSTATE_LOOP;
}


//---------------------------------
//		エンドループアニメリクエスト
//---------------------------------
void	Model::RequestEndLoop(int animID, float animSpd, int animSrcHndl, bool nameCheck)
{
	DetachAnim();

	m_animData.m_hndl = MV1AttachAnim(m_hndl, animID, animSrcHndl, nameCheck);
	m_animData.m_id = animID;
	m_animData.m_endFrm = MV1GetAnimTotalTime(m_hndl, animID);
	m_animData.m_frm = 0.f;
	m_animData.m_spd = animSpd;
	m_animData.m_state = ANIMSTATE_END;
}


//---------------------------------
//		アニメーションデタッチ
//---------------------------------
void	Model::DetachAnim()
{
	if (m_animData.m_hndl != -1)
	{
		MV1DetachAnim(m_hndl, m_animData.m_hndl);
		m_animData.m_hndl = -1;
	}
}