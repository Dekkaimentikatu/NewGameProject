#pragma once

class C_STAGE_MANAGER
{
private:

	int m_hndl;

	char* m_string;

	char* m_string2;

public:

	void Init();	//初期化

	void LoadResource();	//リソース読込

	void Load();	//読込

	void Step();	//更新

	void Update(); //更新確定

	void Draw();	//描画

	void Exit();	//終了
};
