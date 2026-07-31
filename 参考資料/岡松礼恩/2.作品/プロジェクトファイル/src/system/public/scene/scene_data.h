#pragma once

class C_SCENE_DATA
{
public:

	enum SCENE_TYPE
	{
		TITLE,
		SELECT,
		PLAY,
		RESULT,
		END,
		EDITER,

		SCENE_TYPE_NUM,
	};

private:

	C_SCENE_DATA() = default;

	~C_SCENE_DATA() = default;

	C_SCENE_DATA(const C_SCENE_DATA& other);
	C_SCENE_DATA& operator = (const C_SCENE_DATA& other);

	static C_SCENE_DATA* m_classInstance;

	SCENE_TYPE m_sceneType;

	bool m_isEnd;

	bool m_isWait;

public:

	static C_SCENE_DATA* GetInstance();

	static void DeleteInstance();

	void Init();

	void SetSceneType(SCENE_TYPE _sceneType)
	{
		m_sceneType = _sceneType;
	}

	SCENE_TYPE GetSceneType() const
	{
		return m_sceneType;
	}

	void SetIsEnd(bool _isEnd)
	{
		m_isEnd = _isEnd;
	}

	bool GetIsEnd() const
	{
		return m_isEnd;
	}

	void SetIsWait(bool _isWait)
	{
		m_isWait = _isWait;
	}

	bool GetIsWait() const
	{
		return m_isWait;
	}

};

