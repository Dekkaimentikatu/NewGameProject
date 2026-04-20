#include "lib/rand.h"

//typedef struct {
//	int m_rand;	// 乱数
//}RAND_DATA;
//
//RAND_DATA g_randData;	// 乱数データの構造体

int C_RAND::m_rand;

int C_RAND::GetRand_I(int max, int min)
{
    std::random_device rd;  // ハードウェア乱数生成器
    std::mt19937 mt(rd());   // メルセンヌ・ツイスタ法の生成器
    // 0から99までの一様分布の乱数を生成
    std::uniform_int_distribution<int> dist(min, max);
	return /*m_rand = */dist(mt);
}