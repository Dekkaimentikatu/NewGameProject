#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>

class C_RAND
{
private:

	//シード値
	static int m_seed;
	
	//乱数
	static int m_rand;	

public:

	//
	static int GetRand_I(int max, int min = 0);

};

