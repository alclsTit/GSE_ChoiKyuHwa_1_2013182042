#include "stdafx.h"
#include "ObjectCollision.h"


CObjectCollision::CObjectCollision()
{
}

bool CObjectCollision::SquareEachCollision(const Vec3f& r1_cpos, const Vec3f& r2_cpos, int size)
{
	int halfSize = size / 2;

	if (r1_cpos.x + halfSize >= r2_cpos.x - halfSize && r1_cpos.x - halfSize <= r2_cpos.x + halfSize
		&& r1_cpos.y + halfSize >= r2_cpos.y - halfSize && r1_cpos.y - halfSize <= r2_cpos.y + halfSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CObjectCollision::SquareOtherCollision(const Vec3f & r1_cpos, const Vec3f & r2_cpos, int size, int other_size)
{
	int halfSize = size / 2;
	int halfOSize = other_size / 2;

	if (r1_cpos.x + halfOSize >= r2_cpos.x - halfSize && r1_cpos.x - halfOSize <= r2_cpos.x + halfSize
		&& r1_cpos.y + halfOSize >= r2_cpos.y - halfSize && r1_cpos.y - halfOSize <= r2_cpos.y + halfSize)
	{
		return true;
	}
	else
	{
		return false;
	}
}


CObjectCollision::~CObjectCollision()
{
}
