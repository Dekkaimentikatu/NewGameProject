#include "lib/2Dhndlmanager.h"

C_2D_HNDL_MANAGER* C_2D_HNDL_MANAGER::m_instance;

//インスタンスの取得
C_2D_HNDL_MANAGER* C_2D_HNDL_MANAGER::GetInstance()
{
	//nullチェック
	if (m_instance == nullptr)
	{
		//インスタンスを生成
		m_instance = new C_2D_HNDL_MANAGER;
	}

	//インスタンスを返す
	return m_instance;
}

//インスタンスの削除
void C_2D_HNDL_MANAGER::DeleteInstance()
{
	//nullチェック
	if (m_instance)
	{
		//インスタンスの削除と初期化
		delete m_instance;
		m_instance = nullptr;
	}
}

//画像の読み込み
void C_2D_HNDL_MANAGER::Load2DImage(char* _imgaeFilePath, int _allNum, int _XNum, int _YNum, int _XSize, int _YSize)
{
	//一時保存用のローカル変数
	T_2D_HNDL_DATA tmp;
	//画像のファイルパスをコピー
	tmp.imageFilePath = _imgaeFilePath;

	//画像を分割せずに読み込み
	if (_allNum <= 1)
	{
		//画像の総枚数を保存
		tmp.grapAllNum = 1;
		tmp.hndl = new int;
		tmp.hndl[0] = LoadGraph(tmp.imageFilePath.c_str());
	}
	//画像を分割して読み込み
	else
	{
		//画像の総枚数を保存
		tmp.grapAllNum = _allNum;
		tmp.hndl = new int[_allNum];
		LoadDivGraph(tmp.imageFilePath.c_str(), _allNum, _XNum, _YNum, _XSize, _YSize, tmp.hndl);
	}

	//情報の保存
	m_data.push_back(tmp);
}

//画像の取得
int C_2D_HNDL_MANAGER::Get2DImageHndl(char* _imgaeFilePath, int _graphNum)
{
	//保存されている情報からファイルパスが一致するモデルハンドルを探索
	for (auto itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		//ファイルパスが一致しない場合、次の要素を探索する
		if (strcmp((*itr).imageFilePath.c_str(), _imgaeFilePath) != 0)continue;
		//画像の総枚数を超えていなければ対応するハンドルを返す
		if ((*itr).grapAllNum > _graphNum)return(*itr).hndl[_graphNum];
	}

	//対応するハンドルがなければエラー処理
	return -1;
}

//画像情報の削除
void C_2D_HNDL_MANAGER::Delete2DData(char* _imgaeFilePath)
{
	//保存されている情報からファイルパスが一致するモデルハンドルを探索
	for (auto itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		//ファイルパスが一致しない場合、次の要素を探索する
		if (strcmp((*itr).imageFilePath.c_str(), _imgaeFilePath) != 0)continue;

		//画像ハンドルの開放
		for (int i = 0; i < (*itr).grapAllNum; i++)
		{
			DeleteGraph((*itr).hndl[i]);
		}
		//ハンドル配列の解放
		delete[] (*itr).hndl;
		//要素を削除
		m_data.erase(itr);
		return;
	}
}

//すべての画像情報の削除
void C_2D_HNDL_MANAGER::DeleteAll2DData()
{
	//保存されている情報からファイルパスが一致するモデルハンドルを探索
	for (auto itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		//画像ハンドルの開放
		for (int i = 0; i < (*itr).grapAllNum; i++)
		{
			DeleteGraph((*itr).hndl[i]);
		}
		//ハンドル配列の解放
		delete[] (*itr).hndl;
	}
	//listを初期化
	m_data.clear();
}