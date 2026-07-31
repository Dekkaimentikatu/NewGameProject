#pragma once
#include "game/base/object.h"

static const char* SKY_MODEL_PATH = "data/model/field/sky.mv1";

class C_SKY : public C_OBJECT_BASE
{
private:

public:

	void Init() override;	//‰Šú‰»
	void Load() override;	//“Ç
	void Step() override;	//XV
	void Update() override;
	void Draw() override;	//•`‰æ
	void Exit() override;	//I—¹
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};

