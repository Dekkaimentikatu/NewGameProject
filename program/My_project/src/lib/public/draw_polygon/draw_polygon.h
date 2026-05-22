#pragma once
#include <DxLib.h>

class C_DRAW_POLYGON
{
public:

	/*ŽOŠpŒ`‚ð•`‰æ
	* 
	* 
	*/
	static void DrawPolygonTriangle(VECTOR _center, VECTOR _vartex1, VECTOR _vartex2, VECTOR _vartex3, int _grapHndl, int _transFlag);

	/*ŽlŠpŒ`‚ð•`‰æ
	*
	*
	*/
	static void DrawPolygonSquare(VECTOR _pos, int _sizeX, int _sizeY, int _grapHndl, int _transFlag);
};
