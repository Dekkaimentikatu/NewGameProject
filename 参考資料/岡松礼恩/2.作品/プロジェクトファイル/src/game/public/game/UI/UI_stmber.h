#pragma once

#include "game/UI/UI_hpber.h"

constexpr float STM_GRAPH_SIZEX = 256.0f;
constexpr float STM_GRAPH_SIZEY = 16.0f;

static const char* STM_GRAPH_PATH[2] = { "data/graphic/stop_gage.png",
										"data/graphic/stop_gage_frame.png" };

class C_UI_STMBER : public C_UI_HPBER
{
public:

	double m_percent;

public:

	~C_UI_STMBER() {};

	//‰Šú‰»
	void Init(VECTOR _pos);

	void LoadAnSync();

	void Step();


	//XVŠm’èˆ—
	void Update();

	//•`‰æ
	void Draw();
};
