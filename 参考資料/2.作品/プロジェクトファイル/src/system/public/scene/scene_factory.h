#pragma once

class C_SCENE_BASE;

class C_SCENE_FACTORY
{
private:

public:

	C_SCENE_FACTORY();
	~C_SCENE_FACTORY();

	static C_SCENE_BASE* Create(int sceneType);
};