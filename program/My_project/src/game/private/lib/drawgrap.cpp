#include "lib/drawgrap.h"

C_DRAW_GRAPH* C_DRAW_GRAPH::m_Instance = nullptr;	//ポインタ型変数を初期化

C_DRAW_GRAPH* C_DRAW_GRAPH::GetInstance()
{
	if (m_Instance == nullptr)				//インスタンスが生成されてない場合、インスタンスを生成する
	{
		m_Instance = new C_DRAW_GRAPH();	//インスタンスの生成処理
	}

	return m_Instance;						//生成されたインスタンスを戻り値で渡す
}

void C_DRAW_GRAPH::DeleteInstance()
{
	if (m_Instance)				//すでにインスタンスが生成されている場合、インスタンスを削除する
	{
		delete m_Instance;		//インスタンスの削除処理

		m_Instance = nullptr;	//ポインタ型変数を初期化
	}
}

void C_DRAW_GRAPH::Init()
{
	m_graphAllNum = 0;

	m_graphData.clear();
}

int C_DRAW_GRAPH::LoadGraphData(const char* _pathString, int _graphNum, int _graphXnum, int _graphYnum, int _graphWight, int _graphHeight)
{
	m_graphData.push_back(new T_GRAP_DATA);		//可変長配列の末尾にインスタンスを生成

	m_graphData[m_graphAllNum]->m_hndl = nullptr;

	if (_graphNum == 1)		//画像の総枚数が1枚のときは分割読込を行わない
	{
		m_graphData[m_graphAllNum]->m_hndl = new int;			//ハンドルのメモリ領域確保
		m_graphData[m_graphAllNum]->m_graphNum = _graphNum;		//画像の分割数を保存

		m_graphData[m_graphAllNum]->m_hndl[0] = LoadGraph(_pathString);	//画像の読込

		if (-1 == m_graphData[m_graphAllNum]->m_hndl[0])		//もしエラーが発生したら、エラー処理を行う
		{
			return LoadErrFunk();			//エラー処理
		}

		m_graphAllNum++;			//読み込まれた画像の枚数を更新

		return static_cast<int>(m_graphData.size()) - 1;		//読み込まれた画像の配列での位置を返す
	}

	m_graphData[m_graphAllNum]->m_hndl = new int[_graphNum];	//画像の分割数だけ配列を確保
	m_graphData[m_graphAllNum]->m_graphNum = _graphNum;		//画像の分割数を保存

	if (-1 == LoadDivGraph(_pathString, _graphNum, _graphXnum, _graphYnum,
		_graphWight, _graphHeight, m_graphData[m_graphAllNum]->m_hndl))		//エラーが発生したら、エラー処理を行う
	{
		return LoadErrFunk();			//エラー処理
	}

	m_graphAllNum++;			//読み込まれた画像の枚数を更新

	return static_cast<int>(m_graphData.size()) - 1;		//読み込まれた画像の配列での位置を返す
}

int C_DRAW_GRAPH::LoadErrFunk()
{
	if (m_graphData[m_graphAllNum]->m_hndl != nullptr)	//メモリが確保されていれば解放処理を行う
	{
		delete m_graphData[m_graphAllNum]->m_hndl;		//確保したメモリを解放
	}

	m_graphData.pop_back();		//可変長配列の末尾の要素を削除

	return -1;			//エラーが発生したため、-1を返す
}

int C_DRAW_GRAPH::DrawRota(int _graphID, int _graphNum,VECTOR _pos, float _rate, float _angle, int _revarseX, int _rebarseY)
{
	if (_graphID < 0 || _graphID >= m_graphAllNum)return -1;	//範囲外のIDをはじく

	DrawRotaGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), static_cast<double>(_rate), static_cast<double>(_angle),
		m_graphData[_graphID]->m_hndl[_graphNum], TRUE, _revarseX , _rebarseY);	//描画処理

	return 1;
}

int C_DRAW_GRAPH::DrawModi(int _graphID, int _graphNum, VECTOR _pos, int sizeX, int sizeY)
{
	if (_graphID < 0 || _graphID >= m_graphAllNum)return -1;	//範囲外のIDをはじく

	int x1, x2;
	int y1, y2;

	x1 = static_cast<int>(_pos.x) - (sizeX / 2);
	y1 = static_cast<int>(_pos.y) - (sizeY / 2);
	x2 = static_cast<int>(_pos.x) + (sizeX / 2);
	y2 = static_cast<int>(_pos.y) + (sizeY / 2);

	DrawModiGraph(x1, y1, x2, y1, x1, y2, x2, y2, m_graphData[_graphID]->m_hndl[_graphNum], TRUE);

	return 1;
}

int C_DRAW_GRAPH::DrawRect(int _graphID, int _graphNum, VECTOR _pos, int _graphPosX, int _graphPosY, int sizeX, int sizeY)
{
	if (_graphID < 0 || _graphID >= m_graphAllNum)return -1;	//範囲外のIDをはじく

	DrawRectGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _graphPosX, _graphPosY, 
		sizeX, sizeY, m_graphData[_graphID]->m_hndl[_graphNum], TRUE);

	return 1;
}

int C_DRAW_GRAPH::DrawCircleGauge(int _graphID, int _graphNum, VECTOR _pos, double _percent)
{
	if (_graphID < 0 || _graphID >= m_graphAllNum)return -1;	//範囲外のIDをはじく
	//percentは0.0～100.0の範囲
	DrawCircleGaugeF(_pos.x, _pos.y, _percent, m_graphData[_graphID]->m_hndl[_graphNum]);

	return 1;
}

int C_DRAW_GRAPH::DeleteGraphData(int _graphID)		//たぶん使わない
{
	if (_graphID < 0 || _graphID >= m_graphAllNum)return -1;	//範囲外のIDをはじく

	if (m_graphData[_graphID]->m_hndl != nullptr)	//メモリが確保されていれば解放処理を行う
	{
		for (int i = 0; i < m_graphData[_graphID]->m_graphNum; i++)
		{
			DeleteGraph(m_graphData[_graphID]->m_hndl[i]);
		}

		delete m_graphData[_graphID]->m_hndl;		//確保したメモリを解放
	}

	m_graphAllNum--;

	m_graphData.erase(m_graphData.begin() + _graphID);

	return 1;
}

int C_DRAW_GRAPH::DeleteAllGrapData()		//こっちをメインで使う
{
	for (int i = 0; i < m_graphData.size(); i++)
	{
		if (m_graphData[i]->m_hndl != nullptr)	//メモリが確保されていれば解放処理を行う
		{
			for (int j = 0; j < m_graphData[i]->m_graphNum; j++)
			{
				DeleteGraph(m_graphData[i]->m_hndl[j]);
			}

			delete m_graphData[i]->m_hndl;		//確保したメモリを解放
		}
	}

	m_graphAllNum = 0;

	m_graphData.clear();

	return 1;
}