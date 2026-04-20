#include "lib/drawGrap2D.h"

static const char* GRAP_FILE_PATH = "data/csv/graphic.csv";

C_DRAW_GRAP2D* C_DRAW_GRAP2D::m_instance = nullptr;

C_DRAW_GRAP2D* C_DRAW_GRAP2D::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new C_DRAW_GRAP2D();
	}
	return m_instance;
}

void C_DRAW_GRAP2D::DeleteInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

void C_DRAW_GRAP2D::InitGrap2D()	//初期化
{
	int ID = 0;
	char path[256]{};
	FILE* m_fp;	//ファイルポインタ

	m_grapCount = 0;	//グラフィックの数を初期化

	if (fopen_s(&m_fp, GRAP_FILE_PATH, "r") != 0)return;//開けなかったら処理を終了する

	while (!feof(m_fp))
	{
		fscanf_s(m_fp, "%d", &ID);	//CSVのデータを写す
		fscanf_s(m_fp, "%s", &path, _countof(path));
		if (ID != -1)
		{
			m_grapCount++;
		}

	}

	fclose(m_fp);

	if (m_grapCount == 0)
	{
		return;
	}

	m_path = new grapPath[m_grapCount];
}

void C_DRAW_GRAP2D::LoadGrap2D()	//読込
{
	int ID = 0;
	char path[256]{};
	FILE* m_fp;	//ファイルポインタ

	if (fopen_s(&m_fp, GRAP_FILE_PATH, "r") != 0)return;//開けなかったら処理を終了する

	for (int i = 0; i < m_grapCount; i++)
	{
		fscanf_s(m_fp, "%d,", &ID);	//CSVのデータを写す

		if (ID == -1)
		{
			fscanf_s(m_fp, "%s", &path, _countof(path));
			i--;
		}
		else
		{
			m_path[i].m_ID = ID;	//CSVのデータを写す
			fscanf_s(m_fp, "%[^,],", &m_path[i].m_pathString, _countof(m_path[i].m_pathString));	//CSVのデータを写す
			fscanf_s(m_fp, "%d,", &m_path[i].m_GrapWidth);	//CSVのデータを写す
			fscanf_s(m_fp, "%d,", &m_path[i].m_GrapHeight);	//CSVのデータを写す
			fscanf_s(m_fp, "%d,", &m_path[i].m_GrapXNum);	//CSVのデータを写す
			fscanf_s(m_fp, "%d,", &m_path[i].m_GrapYNum);	//CSVのデータを写す
			fscanf_s(m_fp, "%d,", &m_path[i].m_GrapAllNum);	//CSVのデータを写す
			fscanf_s(m_fp, "%f,", &m_path[i].m_AnimSpeed);	//CSVのデータを写す
			fscanf_s(m_fp, "%d,", &m_path[i].m_isMove);	//CSVのデータを写す
			fscanf_s(m_fp, "%d,", &m_path[i].m_dispNum);	//CSVのデータを写す

			m_path[i].m_animCount = new float[m_path[i].m_dispNum];
			m_path[i].m_isActive = new bool[m_path[i].m_dispNum];

			m_path[i].m_hndl = new int[m_path[i].m_GrapAllNum];	//m_hndlを確保する
			for (int j = 0; j < m_path[i].m_GrapAllNum; j++)
			{
				m_path[i].m_hndl[j] = -1;
			}
			for (int j = 0; j < m_path[i].m_dispNum; j++)
			{
				m_path[i].m_animCount[j] = 0;
				m_path[i].m_isActive[j] = false;
			}
		}
	}

	fclose(m_fp);

	int tmp = 0;

	for (int i = 0; i < m_grapCount; i++)
	{

		if (m_path[i].m_GrapAllNum == 1)	//グラフィックの枚数が1枚の時はLoadGraphを使う
		{
			m_path[i].m_hndl[0] = LoadGraph(m_path[i].m_pathString);	//グラフィックを読み込む
		}
		else if (m_path[i].m_GrapAllNum > 1 && m_path[i].m_hndl[0] == -1)	//グラフィックの枚数が2枚以上の時はLoadDivGraphを使う
		{
			tmp = LoadDivGraph(m_path[i].m_pathString, m_path[i].m_GrapAllNum,
				m_path[i].m_GrapXNum, m_path[i].m_GrapYNum,
				m_path[i].m_GrapWidth, m_path[i].m_GrapHeight, &m_path[i].m_hndl[0]);	//グラフィックを読み込む
		}
	}

	if (tmp == -1)
	{
		return;	//グラフィックの読み込みに失敗したら処理を終了する
	}
}

void C_DRAW_GRAP2D::UpdataGrap2D(int ID)	//更新
{
	if (m_path != nullptr)
	{
		for (int j = 0; j < m_path[ID].m_dispNum; j++)
		{
			if (m_path[ID].m_isActive[j] && m_path[ID].m_isMove)
			{
				m_path[ID].m_animCount[j] += m_path[ID].m_AnimSpeed;	//アニメーションのカウントを進める

				if (m_path[ID].m_animCount[j] > m_path[ID].m_GrapAllNum)
				{
					m_path[ID].m_animCount[j] = 0.0f;	//アニメーションのカウントをリセットする
				}

			}
		}
	}
}

void C_DRAW_GRAP2D::RequestGrap2D(int ID, int _dispNum)
{
	if (m_path != nullptr)
	{
		if (m_path[ID].m_isActive[_dispNum] == false)
		{
			m_path[ID].m_isActive[_dispNum] = true;
		}
	}
}

void C_DRAW_GRAP2D::RequestGrap2DAuto(int ID)
{
	if (m_path != nullptr)
	{
		for (int j = 0; j < m_path[ID].m_dispNum; j++)
		{
			if (m_path[ID].m_isActive[j] == false)
			{
				m_path[ID].m_isActive[j] = true;
			}
		}
	}
}

void C_DRAW_GRAP2D::DeleteGrap2D(int ID, int _dispNum)
{
	if (m_path != nullptr)
	{
		if (m_path[ID].m_isActive[_dispNum])
		{
			m_path[ID].m_isActive[_dispNum] = false;
		}
	}
}

void C_DRAW_GRAP2D::DeleteGrap2DAuto(int ID)
{
	if (m_path != nullptr)
	{
		for (int j = 0; j < m_path[ID].m_dispNum; j++)
		{
			if (m_path[ID].m_isActive[j])
			{
				m_path[ID].m_isActive[j] = false;
			}
		}
	}
}

void C_DRAW_GRAP2D::DrawGrap2D(int _grapID, VECTOR _pos, int _dispNum, int _dispID, float _rate, bool turn)	//描画
{
	if (m_path != nullptr)
	{
		if (/*m_path[_grapID].m_isActive[_dispNum] == true && */m_path[_grapID].m_isMove == 1)
		{
			 int tmp = DrawRotaGraph((int)_pos.x, (int)_pos.y, _rate, 0.0f,
				m_path[_grapID].m_hndl[(int)m_path[_grapID].m_animCount[_dispNum]], TRUE);	//描画テスト
		}
		else/* if (m_path[_grapID].m_isActive[_dispNum] == true)*/
		{
			DrawRotaGraph((int)_pos.x, (int)_pos.y, _rate, 0.0f,
				m_path[_grapID].m_hndl[_dispID], TRUE, 0,turn);	//描画テスト
		}
	}
}

void C_DRAW_GRAP2D::ExitGrap2D()	//終了
{
	if (m_path != nullptr)
	{
		for (int i = 0; i < m_grapCount; i++)
		{
			for (int j = 0; j < m_path[i].m_GrapAllNum; j++)
			{
				if (m_path[i].m_hndl[j] != -1)
				{
					DeleteGraph(m_path[i].m_hndl[j]);	//グラフィックを削除する
				}
			}
			delete[] m_path[i].m_hndl;	//m_hndlを解放する
			delete[] m_path[i].m_animCount; //m_animCountを開放する
			delete[] m_path[i].m_isActive;	//m_isActiveを開放する
		}
		delete[] m_path;	//m_pathを解放する
	}
}

void C_DRAW_GRAP2D::ResetGrap2D()
{

}