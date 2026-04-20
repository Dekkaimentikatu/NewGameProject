#include "lib/3Dhndlmanager.h"

C_3D_HNDL_MANAGER* C_3D_HNDL_MANAGER::m_instance = nullptr;

C_3D_HNDL_MANAGER* C_3D_HNDL_MANAGER::GetInstance()
{
	//nullチェック
	if (m_instance == nullptr)
	{
		//インスタンスを生成
		m_instance = new C_3D_HNDL_MANAGER;
	}

	//インスタンスを返す
	return m_instance;
}

void C_3D_HNDL_MANAGER::DeleteInstance()
{
	//nullチェック
	if (m_instance)
	{
		//インスタンスの削除と初期化
		delete m_instance;
		m_instance = nullptr;
	}
}

void C_3D_HNDL_MANAGER::Load3DModel(const char *_modelFilePath)
{
	//一時保存用のローカル変数
	T_3D_HNDL_DATA tmp;
	//モデルのファイルパスをコピー
	tmp.modelFilePath = _modelFilePath;
	//モデルの読込開始
	tmp.hnld = MV1LoadModel(tmp.modelFilePath.c_str());
	//情報の保存
	m_data.push_back(tmp);
}

void C_3D_HNDL_MANAGER::Delete3DModel(const char* _modelFilePath)
{
	//保存されている情報からファイルパスが一致するモデルハンドルを探索
	for (auto itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		//ファイルパスが一致しない場合、次の要素を探索する
		if (strcmp((*itr).modelFilePath.c_str(), _modelFilePath) != 0)continue;

		MV1DeleteModel((*itr).hnld);
		/*delete (*itr).modelFilePath;*/
		m_data.erase(itr);
		return;
	}
}

void C_3D_HNDL_MANAGER::DeleteAll3DModel()
{
	//保存されている情報からファイルパスが一致するモデルハンドルを探索
	for (auto itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		MV1DeleteModel((*itr).hnld);
		/*delete (*itr).modelFilePath;*/
	}

	m_data.clear();
}

int C_3D_HNDL_MANAGER::Get3DModelHndl(const char* _modelFilePath)
{
	//保存されている情報からファイルパスが一致するモデルハンドルを探索
	for (auto itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		//ファイルパスが一致した場合、モデルハンドルを返す
		if (strcmp((*itr).modelFilePath.c_str(), _modelFilePath) != 0)continue;
		else return (*itr).hnld;
	}

	return -1;
}