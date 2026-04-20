#pragma once

#include <DxLib.h>
#include <vector>

#include "common.h"

#include "game/data/global_data.h"

using namespace std;



class C_OBJECT_BASE
{
public:

	//オブジェクトのタイプ
	enum OBJECT_TYPE
	{
		OBJECT_TYPE_PLAYER,
		OBJECT_TYPE_ENEMY,
		OBJECT_TYPE_BLCOK,
		OBJECT_TYPE_FLAG,
		OBJECT_TYPE_STATIC,
		OBJECT_TYPE_DYNAMIC,
	};

	typedef struct
	{
		VECTOR initPos;
		VECTOR modelRot;
		VECTOR modelScale;
		float moveLen;
	}T_OBJECT_DATA;

protected:

	//グローバルデータクラスのインスタンス取得用変数
	C_GLOBAL_DATA* c_globalData;

	//オブジェクト情報
	T_OBJECT_DATA m_objectData;

	//座標
	VECTOR m_pos;

	//移動ベクトル
	VECTOR m_moveVec;

	//押し戻し速度
	VECTOR m_knockBackSpeed;

	//オブジェクトの分類
	OBJECT_TYPE m_objectType;

	//当たり判定の半径
	int m_redius;

	//3Dモデルのハンドル
	int m_modelHndl;

	//エフェクトのハンドル
	int m_effHndl;

	//生存フラグ
	bool m_isActive;

	//モデルの読込
	inline void LoadModel(const char* _modelPath) { m_modelHndl = (MV1LoadModel(_modelPath)); }

	//モデルの削除
	inline void DeleteModel() const { if (m_modelHndl != -1)MV1DeleteModel(m_modelHndl); }

	//モデルの描画
	inline void DrawModel() const { MV1DrawModel(m_modelHndl); }

	//モデルの更新処理
	inline void UpdateModel() const {
		MV1SetPosition(m_modelHndl, m_pos);
		MV1SetRotationXYZ(m_modelHndl, m_objectData.modelRot);
		MV1SetScale(m_modelHndl, m_objectData.modelScale);
	}

	//モデルのコリジョン情報の構築
	inline void SetUpCollInfo() const { MV1SetupCollInfo(m_modelHndl); }

	//モデルのコリジョン情報の更新
	inline void UpdataCollInfo() const { MV1RefreshCollInfo(m_modelHndl); }

	//モデルのコリジョン情報の破棄
	inline void DeleteCollInfo() const { MV1TerminateCollInfo(m_modelHndl); }

public:

	//コンストラクタ
	C_OBJECT_BASE(C_GLOBAL_DATA* _globalData = nullptr, int _hp = 0, int _hpMax = 0,
		int _att = 0, bool _isActive = false, bool _isJump = false, bool _isHit = false,
		bool _isAttack = false, VECTOR _pos = { 0 }, VECTOR _moveVec = VGet(0.0f, 0.0f, 0.0f), 
		VECTOR _knockBackSpeed = VGet(0.0f, 0.0f, 0.0f), OBJECT_TYPE _objectType = OBJECT_TYPE_DYNAMIC, 
		int _redius = 0, int _attackRedius = 0, int _modelHndl = -1, int _effHndl = -1, 
		int _hitWait = 0, float _attackWait = 0.0f) :
		c_globalData(_globalData), m_isActive(_isActive), m_pos(_pos), m_moveVec(_moveVec),
		m_knockBackSpeed(_knockBackSpeed), m_objectType(_objectType), m_redius(_redius), m_modelHndl(_modelHndl), 
		m_effHndl(_effHndl){ }

	//デストラクタ
	virtual ~C_OBJECT_BASE() {}

	//初期化
	virtual void Init();

	//読込
	virtual void Load() = 0;

	//更新
	virtual void Step() = 0;

	//更新確定
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;	

	//終了
	virtual void Exit() = 0;

	//座標加算
	virtual void AddPos(VECTOR _addPos) { m_pos = VAdd(m_pos, _addPos); }

	//リクエスト
	virtual void Request(T_OBJECT_DATA _objectData);

	//生存フラグ取得
	inline bool GetIsActive() const
	{
		return m_isActive;
	}

	//座標を取得
	inline VECTOR GetPos() const { return m_pos; }

	//初期座標を取得
	inline VECTOR GetInitPos() const { return m_objectData.initPos; }

	//回転を取得
	inline VECTOR GetRot() const { return m_objectData.modelRot; }

	//拡大率を取得
	inline VECTOR GetScale() const { return m_objectData.modelScale; }

	inline VECTOR GetMoveVec() const { return m_moveVec; }

	//当たり判定の半径を取得
	inline int GetRedius() const { return m_redius; }

	//アクターの中心座標を取得
	inline VECTOR GetCenter() const
	{
		VECTOR center = m_pos;

		center.y += m_redius;	//中心を少し上にずらす

		return center;
	}

	//当たり判定処理
	virtual void HitCalc() = 0;

	//壁との当たり判定
	virtual void HitCalcWall(){}

	//天井との当たり判定
	virtual void HitCalcCeiling(){}

	//モデルの複製
	inline void DuplicateModel(const int _modelHndl) { m_modelHndl = MV1DuplicateModel(_modelHndl); }

	//モデルのハンドルを取得
	inline int GetModelHndle() const { return m_modelHndl; };

	//オブジェクトのタイプを取得
	inline OBJECT_TYPE GetObjectType() const { return m_objectType; }

	//ノックバック速度を設定
	virtual void SetKonckBackSpeed(VECTOR _knockBackSpeed)
	{
		m_knockBackSpeed = _knockBackSpeed;
	}
};