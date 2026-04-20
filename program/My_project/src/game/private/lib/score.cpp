#include "lib/score.h"


// 定義関連=============================
#define NUMBER (10)			// 読み込む画像「0」～「9」
#define NUMBER_SIZE_X (16)	// 数字画像のサイズ　横
#define NUMBER_SIZE_Y (32)	// 数字画像のサイズ　縦
#define DIGIT_NUMBER (10)	// 表示可能な桁数(今回は99999がカンスト)
#define ADD_SCORE_SPD (10)	// 1フレームで加算されるスコア数

#define START_POS_X (315)	// スコア表示開始位置　横
#define START_POS_Y (120)	// スコア表示開始位置　縦

// 画像のパス
#define SCORE_GRAPH_PATH ("data/graphic/number/number16x32_01.png")
// 効果音
#define SCORE_SOUND_PATH ("data/sound/se2.mp3")


//======================================

int SCORE_DATA::m_hndl[10];
int SCORE_DATA::m_soundHndl;
int SCORE_DATA::m_score[10];
int SCORE_DATA::m_dispScore[10];

void SCORE_DATA::Init()
{

	memset(m_hndl, -1, sizeof(m_hndl));
	m_soundHndl = -1;
	memset(m_score, 0, sizeof(m_score));
	memset(m_dispScore, 0, sizeof(m_dispScore));
}

void SCORE_DATA::Load()
{
	int ret = LoadDivGraph(SCORE_GRAPH_PATH, NUMBER, NUMBER, 1,
		NUMBER_SIZE_X, NUMBER_SIZE_Y, m_hndl);
}

void SCORE_DATA::Update()
{
	for (int i = 0 ; i < 10; i++)
	{
		//実際のスコアと表示用スコアが一致していたら何もしない
		if (m_dispScore[i] == m_score[i])return;
		//表示用スコアを一定の値だけ加算する
		m_dispScore[i] += ADD_SCORE_SPD;

		if (m_dispScore[i] >= m_score[i])
		{
			m_dispScore[i] = m_score[i];
		}
	}
}

void SCORE_DATA::Draw(int x, int y, int _ID)
{
	int tempScore = m_dispScore[_ID];
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		//まずは下一桁を取り出す
		int num = tempScore % 10;
		//取り出した下一桁を正しい位置に表示
		DrawRotaGraph(x - NUMBER_SIZE_X * i,
			y, 1.0, 0.0, m_hndl[num], TRUE);
		//下一桁はいらないので削除する
		tempScore /= 10;
	}
}

void SCORE_DATA::Exit()
{
	for (int i = 0; i < NUMBER; i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteGraph(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
	if (m_soundHndl != -1)
	{
		DeleteSoundMem(m_soundHndl);
		m_soundHndl = -1;
	}
}

void SCORE_DATA::Add(int score, int _ID)
{
	m_score[_ID] += score;
}

void SCORE_DATA::Set(int score, int _ID)
{
	m_score[_ID] = score;
	m_dispScore[_ID] = score;
}

int SCORE_DATA::Get(int _ID)
{
	return m_score[_ID];
}