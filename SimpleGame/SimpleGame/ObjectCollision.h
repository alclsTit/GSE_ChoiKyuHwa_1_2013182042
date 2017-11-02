#pragma once
#include "Vector.h"

class CObjectCollision
{
public:
	CObjectCollision();
	//���簢�� �浹�˻�
	bool SquareEachCollision(const Vec3f& r1_cpos, const Vec3f& r2_cpos, int size); //���ΰ��� �浹
	bool SquareOtherCollision(const Vec3f& r1_cpos, const Vec3f& r2_cpos, int size, int other_size);
	~CObjectCollision();
};

