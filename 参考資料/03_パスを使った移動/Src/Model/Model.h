#pragma once
#include <DxLib.h>

class Model{
private:
	// アニメ関連のデータをまとめた構造体
	typedef struct{
		float	m_endFrm;		// アニメ全再生時間
		float	m_frm;			// アニメ再生時間
		float	m_spd;			// アニメ再生速度
		int		m_hndl;			// アニメハンドル
		int		m_id;			// 再生中のアニメID
		int		m_state;		// アニメの状態
	}ANIM_DATA;

	VECTOR	m_pos;				// 座標
	VECTOR	m_rot;				// 回転角度
	VECTOR	m_scale;			// 拡大縮小率
	ANIM_DATA m_animData;		// アニメ再生関連データ
	int		m_hndl;				// モデルハンドル


public:
	Model();
	virtual ~Model();

	//		初期化
	virtual void	Init();
	//		終了処理
	virtual void	Exit();
	//		更新処理
	virtual void	Update();

	//***************************************
	//		取得関数
	//***************************************
	//		モデルハンドル取得
	//	@memo	:	主にこのモデルをコピーして使いたい他のクラスに
	//			:	渡すためのものです。
	inline int		GetHandle(){ return	m_hndl; }
	//		位置取得
	//	@return	:	モデルの座標
	inline VECTOR	GetPosition(){ return m_pos; }
	//		スケール取得
	//	@return	:	モデルのスケール
	inline VECTOR	GetScale(){ return m_scale; }
	//		回転角度取得
	//	@return	:	モデルの回転角度
	inline VECTOR	GetRot(){ return m_rot; }

	//		アニメ全再生時間取得
	inline float	GetAnimEndFrm(){ return m_animData.m_endFrm; }
	//		アニメ再生時間取得
	inline float	GetAnimFrm(){ return m_animData.m_frm; }
	//		アニメ速度取得
	inline float	GetAnimSpd(){ return m_animData.m_spd; }
	//		再生中のアニメID取得
	//	@memo	:	アニメが再生されていない場合は-1が戻ってくる
	inline int		GetAnimID(){ return m_animData.m_id; }
	//		アニメが終了したか
	inline bool		IsEndAnim(){ return m_animData.m_endFrm == m_animData.m_frm || m_animData.m_endFrm == 0.f; }

	//***************************************
	//		設定関数
	//***************************************
	//		位置設定
	//	pos		:	現在の位置
	inline void	SetPosition(VECTOR pos){ m_pos = pos; }
	//		スケール設定
	//	scale	:	現在のサイズ
	inline void	SetScale(VECTOR scale){ m_scale = scale; }
	inline void	SetScale(float scale){ m_scale.x = m_scale.y = m_scale.z = scale; }
	//		回転角度設定
	//	rot		:	現在の角度
	inline void	SetRot(VECTOR rot){ m_rot = rot; }

	//		アニメ再生時間設定
	inline void	SetAnimFrm(float frm){ m_animData.m_frm = frm; }
	//		アニメ速度設定
	inline void	SetAnimSpd(float spd){ m_animData.m_spd = spd; }

	//***************************************
	//		画像読み込み関連
	//***************************************
	//		モデル通常ロード
	//	fileName	:	読み込みたいモデルデータ名
	bool	LoadModel(const char* fileName);
	//		モデルコピーロード
	//	@memo		:	すでに読み込んであるモデルを複数表示したい場合に使用します。
	//	srcHndl	:	読み込みたいモデルのハンドル
	bool	DuplicateModel(int srcHndl);
	//		モデルデータ削除
	void	DeleteModel();

	//***************************************
	//		描画関連
	//***************************************
	//		モデル描画
	virtual void	Draw();

	//***************************************
	//		アニメーション関連
	//***************************************

	//		アニメアップデート
	//	@memo	:	アニメ更新処理、毎回呼んでください
	void	UpdateAnim();

	//		アニメリクエスト
	//	animID		:	アタッチするアニメ番号
	//	animSpd	:	アニメ再生速度
	//	animSrcHndl:	アニメーションを持っているモデルのハンドル(-1ならばこのモデルのアニメ使用)
	//	isNameCheck	:	別モデルのアニメを使用する場合、モデルのフレーム名が一致していない場合
	//					アニメをアタッチするか(animSrcHndl=-1の場合は無視)
	void	Request(int animID, float animSpd, int animSrcHndl = -1, bool isNameCheck = false);
	//		ループアニメリクエスト
	//	@memo		:	アニメが最終フレームになったら最初に戻ります。
	void	RequestLoop(int animID, float animSpd, int animSrcHndl = -1, bool isNameCheck = false);
	//		エンドループアニメリクエスト
	//	@memo		:	アニメが最終フレームになったらそのままで止まります。
	void	RequestEndLoop(int animID, float animSpd, int animSrcHndl = -1, bool isNameCheck = false);

private:
	//		安全にアニメをデタッチ
	void DetachAnim();
};
