#pragma once
#include "Vector.h"

class CObjectCollision
{
public:
	CObjectCollision();
	//���簢�� �浹�˻�
	bool SquareEachCollision(const Vec3f& c_pos, const Vec3f& c_pos_other, int size); //���ΰ��� �浹
	~CObjectCollision();
};

