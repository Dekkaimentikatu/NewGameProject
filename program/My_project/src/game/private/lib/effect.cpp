#include "lib/effect.h"

void Effect_Data::Init()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_hndl[i][j] = -1;
		}
	}
}

void Effect_Data::Load()
{
	if (m_hndl[0][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_2.png", 4, 4, 1, 32, 32, m_hndl[0]);
	}
	if (m_hndl[1][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_1.png", 4, 4, 1, 32, 32, m_hndl[1]);
	}
	if (m_hndl[2][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_3.png", 4, 4, 1, 32, 32, m_hndl[2]);
	}
	if (m_hndl[3][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_4.png", 4, 4, 1, 32, 32, m_hndl[3]);
	}
	if (m_hndl[4][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_4.png", 4, 4, 1, 32, 32, m_hndl[4]);
	}
	if (m_hndl[5][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_1.png", 4, 4, 1, 32, 32, m_hndl[5]);
	}
	if (m_hndl[6][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_1.png", 4, 4, 1, 32, 32, m_hndl[6]);
	}
}

void Effect_Data::Exit()
{
	for (int j = 0; j < 4; j++)
	{
		if (m_hndl[j][0] != -1)
		{
			//すべての画像を1枚ずつ破棄する
			for (int i = 0; i < 4; i++)
			{
				DeleteGraph(m_hndl[j][i]);
				m_hndl[j][i] = -1;
			}
		}
	}
}

void Block_Effect::Init()
{
	m_pos = { 0.0f, 0.0f};
	m_animCount = 0.0f;
	m_isActive = false;
}

void Block_Effect::Load()
{
	if (m_hndl[0][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_2.png", 4, 4, 1, 32, 32, m_hndl[0]);
	}
	if (m_hndl[1][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_1.png", 4, 4, 1, 32, 32, m_hndl[1]);
	}
	if (m_hndl[2][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_4.png", 4, 4, 1, 32, 32, m_hndl[2]);
	}
	if (m_hndl[3][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_3.png", 4, 4, 1, 32, 32, m_hndl[3]);
	}
	if (m_hndl[4][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_1.png", 4, 4, 1, 32, 32, m_hndl[4]);
	}
	if (m_hndl[5][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_4.png", 4, 4, 1, 32, 32, m_hndl[5]);
	}
	if (m_hndl[6][0] == -1)
	{
		//この変数successは書かなくてもOK
		//画像が表示されない場合は大体この変数の中身が「-1」になっている
		LoadDivGraph("data/graphic/scene_game/effect_5.png", 4, 4, 1, 32, 32, m_hndl[6]);
	}
}

void Block_Effect::Step()
{
	if (m_isActive == true)
	{
		//Sleep(4);
		m_animCount += 0.25;
		//想定表示枚数を超えた場合はエフェクトを消す
		if (m_animCount >= 4)
		{
			m_isActive = false;
		}
	}
}

void Block_Effect::Draw(int offset, int* hndl)
{
	if (m_isActive == true)
	{
		//現在表示すべき画像の枚数はこれで計算する
		int nowHndl = hndl[m_index * 4 + (int)m_animCount];
		DrawRotaGraph((int)m_pos.x + 16 + (int)(7.5f * 32), (int)m_pos.y + offset - 5,
			1.5, 0.0, nowHndl, TRUE);
	}
}

void Block_Effect::Exit()
{
	for (int j = 0; j < 4; j++)
	{
		if (m_hndl[j][0] != -1)
		{
			//すべての画像を1枚ずつ破棄する
			for (int i = 0; i < 4; i++)
			{
				DeleteGraph(m_hndl[j][i]);
				m_hndl[j][i] = -1;
			}
		}
	}
}

void Block_Effect::Reqest(VECTOR pos, int index)
{
	if (index == -1)return;
	//エフェクト表示に必要な情報を最初に一回セットする
	m_isActive = true;
	m_pos = pos;
	m_animCount = 0.0f;
	m_index = index;
}

bool Block_Effect::End()
{
	if (m_isActive == false)
	{
		return true;
	}
	else return false;
}

//定数関連
#define ANIM_NUM	(10)
#define ANIM_SPEED	(0.25f)
#define ANIM_MAX	(100)

//爆発エフェクト表示用構造体
typedef struct {
	VECTOR m_pos;
	float m_animCount;
	int m_hndl[ANIM_NUM];
	bool m_isActive;
}EFFECT_DATA;

//爆発エフェクト用にグローバル変数を作成
EFFECT_DATA g_effect[ANIM_MAX];

//爆発エフェクト用データの初期化
void InitEffect()
{
	for (int j = 0; j < ANIM_MAX; j++)
	{
		for (int i = 0; i < ANIM_NUM; i++)
		{
			g_effect[j].m_hndl[i] = -1;
		}
		g_effect[j].m_pos = {0.0f, 0.0f, 0.0f};
		g_effect[j].m_animCount = 0.0f;
		g_effect[j].m_isActive = false;
	}
}

//爆発エフェクトデータ読込
void LoadEffect()
{
	for (int j = 0; j < ANIM_MAX; j++)
	{
		//爆発エフェクトの画像をロード
		if (g_effect[j].m_hndl[0] == -1)
		{
			//この変数successは書かなくてもOK
			//画像が表示されない場合は大体この変数の中身が「-1」になっている
			int success = LoadDivGraph("data/graphics/game/effect_effect00.png",
				10, 10, 1, 180, 180, g_effect[j].m_hndl);
		}
	}
}

//爆発エフェクトの毎フレーム更新処理
void StepEffect()
{
	for (int j = 0; j < ANIM_MAX; j++)
	{
		if (g_effect[j].m_isActive == false)continue;
		//爆発エフェクトのアニメーション
		//表示フラグがオンの時にしかやらない
		if (g_effect[j].m_isActive == true)
		{
			Sleep(ANIM_NUM);
			g_effect[j].m_animCount += ANIM_SPEED;
			//想定表示枚数を超えた場合はエフェクトを消す
			if (g_effect[j].m_animCount >= ANIM_NUM)
			{
				g_effect[j].m_isActive = false;
			}
		}
		break;
	}
}

//爆発エフェクト表示
void DrawEffect()
{
	for (int j = 0; j < ANIM_MAX; j++)
	{
		if (g_effect[j].m_isActive == false)continue;
		if (g_effect[j].m_isActive == true)
		{
			//現在表示すべき画像の枚数はこれで計算する
			int nowHndl = g_effect[j].m_hndl[(int)g_effect[j].m_animCount];
			DrawRotaGraph((int)g_effect[j].m_pos.x, (int)g_effect[j].m_pos.y,
				1.0, 0.0, nowHndl, TRUE);
		}
		break;
	}
}

//終了前に行う必要がある処理
void ExitEffect() 
{
	for (int j = 0; j < ANIM_MAX; j++)
	{
		//爆発エフェクトの画像破棄
		//ハンドルが-1でなければ、何かしらロードされているはず
		if (g_effect[j].m_hndl[0] != -1)
		{
			//すべての画像を1枚ずつ破棄する
			for (int i = 0; i < ANIM_NUM; i++)
			{
				DeleteGraph(g_effect[j].m_hndl[i]);
				g_effect[j].m_hndl[i] = -1;
			}
		}
	}
}

//爆発エフェクト呼び出し
//@pos	:	エフェクトの表示場所
void RequestEffect(VECTOR pos) 
{
	for (int j = 0; j < ANIM_MAX; j++)
	{
		//エフェクト表示に必要な情報を最初に一回セットする
		g_effect[j].m_isActive = true;
		g_effect[j].m_pos = pos;
		g_effect[j].m_animCount = 0.0f;
		break;
	}
}

bool IsEndEffect()
{
	for (int j = 0; j < ANIM_MAX; j++)
	{
		if (g_effect[j].m_isActive == false)
		{
			return true;
		}
		else return false;
	}

	return false;
}