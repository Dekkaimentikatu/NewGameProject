#include "scene/scene_factory.h"
#include "scene/scene.h"
#include "scene/scene_data.h"
#include "scene/scene_title.h"
#include "scene/scene_select.h"
#include "scene/scene_play.h"
#include "scene/scene_result.h"
#include "scene/scene_editer.h"

C_SCENE_FACTORY::C_SCENE_FACTORY()
{

}

C_SCENE_FACTORY::~C_SCENE_FACTORY()
{

}

C_SCENE_BASE* C_SCENE_FACTORY::Create(int sceneType)
{				
	switch (sceneType)
	{
	case C_SCENE_DATA::SCENE_TYPE::TITLE:

		return new C_SCENE_TITLE;	//次のシーンクラスインスタンスの生成

	case C_SCENE_DATA::SCENE_TYPE::SELECT:

		return new C_SCENE_SELECT;	//次のシーンクラスインスタンスの生成

	case C_SCENE_DATA::SCENE_TYPE::PLAY:

		return new C_SCENE_PLAY;	//次のシーンクラスインスタンスの生成

	case C_SCENE_DATA::SCENE_TYPE::RESULT:

		return new C_SCENE_RESULT;	//次のシーンクラスインスタンスの生成

	case C_SCENE_DATA::SCENE_TYPE::END:

		return nullptr;				//シーン終了

	case C_SCENE_DATA::SCENE_TYPE::EDITER:

		return new C_SCENE_EDITER;	//次のシーンクラスインスタンスの生成
	}

	return nullptr;
}