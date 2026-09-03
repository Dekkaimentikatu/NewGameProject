#include "../public/draw_polygon/draw_polygon.h"

void C_DRAW_POLYGON::DrawLineBox(VECTOR _pos, VECTOR _size)
{
	VECTOR vartex1 = VGet(_size.x, _size.y, _size.z);
	VECTOR vartex2 = VGet(_size.x, _size.y, -_size.z);
	VECTOR vartex3 = VGet(-_size.x, _size.y, -_size.z);
	VECTOR vartex4 = VGet(-_size.x, _size.y, _size.z);
	VECTOR vartex5 = VGet(-_size.x, -_size.y, _size.z);
	VECTOR vartex6 = VGet(-_size.x, -_size.y, -_size.z);
	VECTOR vartex7 = VGet(_size.x, -_size.y,- _size.z);
	VECTOR vartex8 = VGet(_size.x, -_size.y, _size.z);

	DrawLine3D(VAdd(_pos, vartex1), VAdd(_pos, vartex2), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex2), VAdd(_pos, vartex3), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex3), VAdd(_pos, vartex4), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex4), VAdd(_pos, vartex1), GetColor(255, 255, 255));

	DrawLine3D(VAdd(_pos, vartex5), VAdd(_pos, vartex6), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex6), VAdd(_pos, vartex7), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex7), VAdd(_pos, vartex8), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex8), VAdd(_pos, vartex5), GetColor(255, 255, 255));

	DrawLine3D(VAdd(_pos, vartex1), VAdd(_pos, vartex8), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex2), VAdd(_pos, vartex7), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex3), VAdd(_pos, vartex6), GetColor(255, 255, 255));
	DrawLine3D(VAdd(_pos, vartex4), VAdd(_pos, vartex5), GetColor(255, 255, 255));
}

void C_DRAW_POLYGON::DrawPolygonTriangle(VECTOR _pos, VECTOR _vartex1, VECTOR _vartex2, VECTOR _vartex3, int _grapHndl, int _transFlag)
{
    //頂点情報の作成
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
    Vertex[1].dif = GetColorU8(255, 255, 255, 255);
    Vertex[1].spc = GetColorU8(0, 0, 0, 0);
    Vertex[1].u = 0.0f;
    Vertex[1].v = 0.0f;
    Vertex[1].su = 0.0f;
    Vertex[1].sv = 0.0f;

    Vertex[2].pos = VSub(_pos, _vartex3);
    Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[2].dif = GetColorU8(255, 255, 255, 255);
    Vertex[2].spc = GetColorU8(0, 0, 0, 0);
    Vertex[2].u = 0.0f;
    Vertex[2].v = 0.0f;
    Vertex[2].su = 0.0f;
    Vertex[2].sv = 0.0f;

	DrawPolygon3D(Vertex, 1, _grapHndl, _transFlag);
}

void C_DRAW_POLYGON::DrawPolygonSquare(VECTOR _pos, VECTOR _vartex1, VECTOR _vartex2, VECTOR _vartex3, VECTOR _vartex4, int _grapHndl, int _transFlag)
{
    VERTEX3D Vertex[4] = { 0 };
    WORD Index[6] = { 0 };

    //４頂点分のデータをセット
    Vertex[0].pos = VAdd(_pos, _vartex1);
    Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[0].dif = GetColorU8(255, 255, 255, 255);
    Vertex[0].spc = GetColorU8(255, 255, 255, 255);
    Vertex[0].u = 0.0f;
    Vertex[0].v = 0.0f;
    Vertex[0].su = 0.0f;
    Vertex[0].sv = 0.0f;

    Vertex[1].pos = VAdd(_pos, _vartex2);
    Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[1].dif = GetColorU8(255, 255, 255, 255);
    Vertex[1].spc = GetColorU8(255, 255, 255, 255);
    Vertex[1].u = 1.0f;
    Vertex[1].v = 0.0f;
    Vertex[1].su = 0.0f;
    Vertex[1].sv = 0.0f;

    Vertex[2].pos = VAdd(_pos, _vartex3);
    Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[2].dif = GetColorU8(255, 255, 255, 255);
    Vertex[2].spc = GetColorU8(255, 255, 255, 255);
    Vertex[2].u = 0.0f;
    Vertex[2].v = 1.0f;
    Vertex[2].su = 0.0f;
    Vertex[2].sv = 0.0f;

    Vertex[3].pos = VAdd(_pos, _vartex4);
    Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
    Vertex[3].dif = GetColorU8(255, 255, 255, 255);
    Vertex[3].spc = GetColorU8(255, 255, 255, 255);
    Vertex[3].u = 1.0f;
    Vertex[3].v = 1.0f;
    Vertex[3].su = 0.0f;
    Vertex[3].sv = 0.0f;

    // ２ポリゴン分のインデックスデータをセット
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 3;
    Index[4] = 2;
    Index[5] = 1;

    // ２ポリゴンの描画
    DrawPolygonIndexed3D(Vertex, 4, Index, 2, _grapHndl, _transFlag);
}