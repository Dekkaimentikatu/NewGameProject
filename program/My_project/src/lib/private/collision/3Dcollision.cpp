#include "../public/collision/3Dcollision.h"

//î†ìØémÇÃìñÇΩÇËîªíË
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

bool C_COLLISION::CheckHitBoxToCapsule(VECTOR _boxPos, VECTOR _boxSize, VECTOR _capPos1, VECTOR _capPos2, float _capRedius)
{
	return true;
}

//ãÖìØémÇÃìñÇΩÇËîªíË
bool C_COLLISION::CheckHitSphereToSphere(VECTOR S_circlePos, VECTOR E_cleclePos, int S_redius, int E_redius)
{
	//îºåaAÇÃ2èÊ+îºåaBÇÃ2èÊ
	float addredius = static_cast<float>((S_redius + E_redius) * (S_redius + E_redius));
	//ãóó£XÇÃ2èÊ
	float distance_X = (E_cleclePos.x - S_circlePos.x) * (E_cleclePos.x - S_circlePos.x);
	//ãóó£YÇÃ2èÊ
	float distance_Y = (E_cleclePos.y - S_circlePos.y) * (E_cleclePos.y - S_circlePos.y);
	//ãóó£ZÇÃ2èÊ
	float distance_Z = (E_cleclePos.z - S_circlePos.z) * (E_cleclePos.z - S_circlePos.z);
	//îªíË
	if ((distance_X + distance_Y + distance_Z) < addredius)
	{
		return true;
	}
	else return false;
}