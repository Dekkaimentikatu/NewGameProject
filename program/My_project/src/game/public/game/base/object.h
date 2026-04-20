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
	}T_OBJECT_DATA;

protected:

	//グローバルデータクラスのインスタンス取得用変数
	C_GLOBAL_DATA* c_globalData;

	T_OBJECT_DATA m_objectData;

	//HP
	int m_hp;

	//HP最大値
	int m_hpMax;

	//攻撃力
	int m_att;

	//生存フラグ
	bool m_isActive;

	//ジャンプ中フラグ
	bool m_isJump;

	//当たり判定フラグ
	bool m_isHit;

	//攻撃中フラグ
	bool m_isAttack;

	//座標
	VECTOR m_pos;

	//初期座標
	VECTOR m_startPos;

	//回転
	VECTOR m_modelRota;

	//拡大率
	VECTOR m_scale;

	//各方向の大きさ
	VECTOR m_size;

	//移動ベクトル
	VECTOR m_moveVec;

	//押し戻し速度
	VECTOR m_knockBackSpeed;

	OBJECT_TYPE m_objectType;

	//当たり判定の半径
	int m_redius;

	//攻撃判定の半径
	int m_attackRedius;

	//3Dモデルのハンドル
	int m_modelHndl;

	//エフェクトのハンドル
	int m_effHndl;

	//当たり判定待機時間
	int m_hitWait;

	//攻撃待機時間
	float m_attackWait;

	//モデルの読込
	inline void LoadModel(const char* _modelPath) { m_modelHndl = (MV1LoadModel(_modelPath)); }

	//モデルの削除
	inline void DeleteModel() const { if (m_modelHndl != -1)MV1DeleteModel(m_modelHndl); }

	//モデルの描画
	inline void DrawModel() const { MV1DrawModel(m_modelHndl); }

	//モデルの更新処理
	inline void UpdateModel() const { MV1SetPosition(m_modelHndl, m_pos); MV1SetRotationXYZ(m_modelHndl, m_modelRota); MV1SetScale(m_modelHndl, m_scale); }

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
		bool _isAttack = false, VECTOR _pos = { 0 }, VECTOR _startPos = { 0 }, VECTOR _modelRota = { 0 },
		VECTOR _scale = VGet(1.0f, 1.0f, 1.0f), VECTOR _size = VGet(1.0f, 1.0f, 1.0f),
		VECTOR _moveVec = VGet(0.0f, 0.0f, 0.0f), VECTOR _knockBackSpeed = VGet(0.0f, 0.0f, 0.0f),
		OBJECT_TYPE _objectType = OBJECT_TYPE_DYNAMIC, int _redius = 0, int _attackRedius = 0,
		int _modelHndl = -1, int _effHndl = -1, int _hitWait = 0, float _attackWait = 0.0f) :
		c_globalData(_globalData), m_hp(_hp), m_hpMax(_hpMax), m_att(_att), m_isActive(_isActive),
		m_isJump(_isJump), m_isHit(_isHit), m_isAttack(_isAttack), m_pos(_pos), m_startPos(_startPos),
		m_modelRota(_modelRota), m_scale(_scale), m_size(_size), m_moveVec(_moveVec),
		m_knockBackSpeed(_knockBackSpeed), m_objectType(_objectType), m_redius(_redius),
		m_attackRedius(_attackRedius), m_modelHndl(_modelHndl), m_effHndl(_effHndl),
		m_hitWait(_hitWait), m_attackWait(_attackWait){ }

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

	//ダメージ判定処理
	virtual void DamageCalc(int att) { m_hp -= att; }

	//ATT取得
	virtual int GetAtt();

	//HP取得
	inline int GetHp() const
	{
		return m_hp;
	}

	//HP設定
	inline void SetHp(int _hp)
	{
		m_hp = _hp;
	}

	//座標加算
	virtual void AddPos(VECTOR _addPos) { m_pos = VAdd(m_pos, _addPos); }

	//リクエスト
	virtual void Request(VECTOR _pos, VECTOR _scale, VECTOR _rotation, int _modelHndl);

	//生存フラグ取得
	inline bool GetIsActive() const
	{
		return m_isActive;
	}

	//座標を取得
	inline VECTOR GetPos() const { return m_pos; }

	//初期座標を取得
	inline VECTOR GetStartPos() const { return m_startPos; }

	//回転を取得
	inline VECTOR GetRota() const { return m_modelRota; }

	//拡大率を取得
	inline VECTOR GetScale() const { return m_scale; }

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

	//攻撃中フラグ設定
	inline void SetIsAttack(const bool _isAttack)
	{
		m_isAttack = _isAttack;
	}

	//攻撃中フラグ取得
	inline bool GetIsAttack() const
	{
		return m_isAttack;
	}

	//攻撃判定の半径取得
	inline int GetAttackRedius() const
	{
		return m_attackRedius;
	}

	//攻撃判定の座標取得
	inline virtual VECTOR GetAttackPos() const
	{
		VECTOR tmp = VGet(0.0f, 0.0f, static_cast<float>(m_redius));
		MATRIX	mat1, mat2;
		mat1 = MGetTranslate(tmp);
		mat2 = MGetRotY(m_modelRota.y);
		mat1 = MMult(mat1, mat2);
		tmp = VGet(-mat1.m[3][0], mat1.m[3][1], -mat1.m[3][2]);

		return VAdd(m_pos, tmp);
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