#pragma once
#include <DxLib.h>

class C_DRAW_POLYGON
{
public:

	//
	static void DrawLineBox(VECTOR _pos, VECTOR _size);

	/*ŽOŠpŒ`‚ð•`‰æ
	* 
	* 
	*/
	static void DrawPolygonTriangle(VECTOR _center, VECTOR _vartex1, VECTOR _vartex2, VECTOR _vartex3, int _grapHndl, int _transFlag);

	/*ŽlŠpŒ`‚ð•`‰æ
	*
	*
	*/
	static void DrawPolygonSquare(VECTOR _pos, VECTOR _vartex1, VECTOR _vartex2, VECTOR _vartex3, VECTOR _vartex4, int _grapHndl, int _transFlag);
};
