#pragma once
#include "Vector.h"

class CObjectCollision
{
public:
	CObjectCollision();
	//정사각형 충돌검사
	bool SquareEachCollision(const Vec3f& r1_cpos, const Vec3f& r2_cpos, int size); //서로간의 충돌
	bool SquareOtherCollision(const Vec3f& r1_cpos, const Vec3f& r2_cpos, int size, int other_size);
	~CObjectCollision();
};

