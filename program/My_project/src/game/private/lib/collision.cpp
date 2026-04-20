#include "lib/collision.h"

//“_‚ÆlŠp‚Ì“–‚½‚è”»’è
bool C_COLLISION::CheckHitDotToSquare(VECTOR dotPos, VECTOR squarePos,
	int width, int height)
{
	//lŠpŒ`‚Ìã‰º¶‰E‚»‚ê‚¼‚ê‚ÌÀ•W‚ğŒvZ‚·‚é
	float up = squarePos.y - height * 0.5f;
	float down = squarePos.y + height * 0.5f;
	float left = squarePos.x - width * 0.5f;
	float right = squarePos.x + width * 0.5f;

	//4‚Â‚Ì’[‚ğ‚»‚ê‚¼‚êƒ`ƒFƒbƒN‚µ‚ÄA‚·‚×‚Ä‚ÌğŒ‚ğ–‚½‚µ‚½‚çƒqƒbƒgI
	if (dotPos.x >= left && dotPos.x <= right
		&& dotPos.y >= up && dotPos.y <= down)
	{
		return true;
	}
	else return false;
}

//‹éŒ`“¯m‚Ì“–‚½‚è”»’è
bool C_COLLISION::CheckHitSquareToSquare(VECTOR S_squarePos, VECTOR E_squarePos,
	int S_width, int S_height, int E_width, int E_height)
{
	//’e‚Ì“–‚½‚è”»’è
	float S_up = S_squarePos.y - S_height * 0.5f;
	float S_down = S_squarePos.y + S_height * 0.5f;
	float S_left = S_squarePos.x - S_width * 0.5f;
	float S_right = S_squarePos.x + S_width * 0.5f;
	//“G‚Ì“–‚½‚è”»’è
	float E_up = E_squarePos.y - E_height * 0.5f;
	float E_down = E_squarePos.y + E_height * 0.5f;
	float E_left = E_squarePos.x - E_width * 0.5f;
	float E_right = E_squarePos.x + E_width * 0.5f;
	//”»’è
	if (S_left <= E_right && S_right >= E_left 
		&& S_up <= E_down && S_down >= E_up )
	{
		return true;
	}
	else return false;
}

//‰~“¯m‚Ì“–‚½‚è”»’è
bool C_COLLISION::CheckHitCircleToCircle(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius)
{
	//”¼ŒaA‚Ì2æ+”¼ŒaB‚Ì2æ
	float addredius = static_cast<float>((S_redius * S_redius) + (E_redius * E_redius));
	//‹——£X‚Ì2æ
	float distance_X = (E_cleclePos.x - S_circlePos.x) * (E_cleclePos.x - S_circlePos.x);
	//‹——£Y‚Ì2æ
	float distance_Y = (E_cleclePos.y - S_circlePos.y) * (E_cleclePos.y - S_circlePos.y);
	//”»’è
	if ((distance_X + distance_Y) < addredius)
	{
		return true;
	}
	else return false;
}

//” “¯m‚Ì“–‚½‚è”»’è
bool C_COLLISION::CheckHitBoxToBox(VECTOR pos1, VECTOR size1, VECTOR pos2, VECTOR size2)
{
	float up1 = pos1.y - size1.y * 0.5f;
	float down1 = pos1.y + size1.y * 0.5f;
	float left1 = pos1.x - size1.x * 0.5f;
	float right1 = pos1.x + size1.x * 0.5f;
	float front1 = pos1.z - size1.z * 0.5f;
	float back1 = pos1.z + size1.z * 0.5f;

	float up2 = pos2.y - size2.y * 0.5f;
	float down2 = pos2.y + size2.y * 0.5f;
	float left2 = pos2.x - size2.x * 0.5f;
	float right2 = pos2.x + size2.x * 0.5f;
	float front2 = pos2.z - size2.z * 0.5f;
	float back2 = pos2.z + size2.z * 0.5f;

	if (left1 <= right2 && right1 >= left2
		&& up1 <= down2 && down1 >= up2
		&& front1 <= back2 && back1 >= front2)
	{
		return true;
	}
	else return false;
}

//‹…“¯m‚Ì“–‚½‚è”»’è
bool C_COLLISION::CheckHitSphereToSphere(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius)
{
	//”¼ŒaA‚Ì2æ+”¼ŒaB‚Ì2æ
	float addredius = static_cast<float>((S_redius + E_redius) * (S_redius + E_redius));
	//‹——£X‚Ì2æ
	float distance_X = (E_cleclePos.x - S_circlePos.x) * (E_cleclePos.x - S_circlePos.x);
	//‹——£Y‚Ì2æ
	float distance_Y = (E_cleclePos.y - S_circlePos.y) * (E_cleclePos.y - S_circlePos.y);
	//‹——£Z‚Ì2æ
	float distance_Z = (E_cleclePos.z - S_circlePos.z) * (E_cleclePos.z - S_circlePos.z);
	//”»’è
	if ((distance_X + distance_Y + distance_Z) < addredius)
	{
		return true;
	}
	else return false;
}