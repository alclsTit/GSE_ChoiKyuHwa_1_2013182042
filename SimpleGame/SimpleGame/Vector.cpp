#include "stdafx.h"
#include "Vector.h"

CVector3 CVector3::Normalized(const CVector3 & v) const
{
	float denomi;
	denomi = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		//sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));

	return (CVector3(v.x / denomi, v.y / denomi, v.z / denomi));
}
