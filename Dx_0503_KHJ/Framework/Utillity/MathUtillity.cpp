#include "framework.h"
#include "MathUtillity.h"

int MathUtillity::RandomInt(int min, int max)
{
	int range = rand() % (max - min);

	return min + range;
}

float MathUtillity::RandomFloat(float min, float max)
{
	float normal = (float)rand() / (float)RAND_MAX; // 0 ~ 1������ ������ �Ǽ�

	return min + (max - min) * normal;
}