#include "../public/draw_polygon/draw_polygon.h"

void C_DRAW_POLYGON::DrawPolygonTriangle(VECTOR _pos, VECTOR _vartex1, VECTOR _vartex2, VECTOR _vartex3, int _grapHndl, int _transFlag)
{
    //í∏ì_èÓïÒÇÃçÏê¨
    VERTEX3D Vertex[3] = { 0 };
	
    Vertex[0].pos = VSub(_pos, _vartex1);
    Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[0].dif = GetColorU8(255, 255, 255, 255);
    Vertex[0].spc = GetColorU8(0, 0, 0, 0);
    Vertex[0].u = 0.0f;
    Vertex[0].v = 0.0f;
    Vertex[0].su = 0.0f;
    Vertex[0].sv = 0.0f;

    Vertex[1].pos = VSub(_pos, _vartex2);
    Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[1].dif = GetColorU8(255, 0, 255, 255);
    Vertex[1].spc = GetColorU8(0, 0, 0, 0);
    Vertex[1].u = 0.0f;
    Vertex[1].v = 0.0f;
    Vertex[1].su = 0.0f;
    Vertex[1].sv = 0.0f;

    Vertex[2].pos = VSub(_pos, _vartex3);
    Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[2].dif = GetColorU8(0, 255, 255, 255);
    Vertex[2].spc = GetColorU8(0, 0, 0, 0);
    Vertex[2].u = 0.0f;
    Vertex[2].v = 0.0f;
    Vertex[2].su = 0.0f;
    Vertex[2].sv = 0.0f;

	DrawPolygon3D(Vertex, 1, _grapHndl, _transFlag);
}

void C_DRAW_POLYGON::DrawPolygonSquare(VECTOR _pos, int _sizeX, int _sizeY, int _grapHndl, int _transFlag)
{
    VERTEX3D Vertex[4] = { 0 };

	//DrawPolygonIndexed3D();
}