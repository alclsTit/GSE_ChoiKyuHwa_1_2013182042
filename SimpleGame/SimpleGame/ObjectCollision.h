#pragma once
#include "Vector.h"

class CObjectCollision
{
public:
	CObjectCollision();
	//정사각형 충돌검사
	bool SquareEachCollision(const Vec3f& c_pos, const Vec3f& c_pos_other, int size); //서로간의 충돌
	~CObjectCollision();
};

