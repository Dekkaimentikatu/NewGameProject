#pragma once
#include "game/base/object.h"

static const char* BOARD_MODEL_PATH = "data/model/field/board.mv1";

static const char* BOARD_IMAGE_PATH[6] = { "data/graphic/tutorial_move.png",
											"data/graphic/tutorial_cam.png",
											"data/graphic/tutorial_jump.png",
											"data/graphic/tutorial_stop.png",
											"data/graphic/tutorial_attack.png",
											"data/graphic/tutorial_denger.png"};


class C_BOARD : public C_OBJECT_BASE
{
private:

	int m_imageHndl;

public:

	C_BOARD():m_imageHndl(0){}
	~C_BOARD();
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Exit();
	void Request(T_OBJECT_DATA _objectData);
	void HitCalc();
};
