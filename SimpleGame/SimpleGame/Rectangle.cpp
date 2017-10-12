#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::MovePosPerUpdate(float objVel, float time = 1)
{
	CVector3 tempVec3 = GetRectPosition();
	CVector3 NormalVec3 = m_vector3.Normalized(tempVec3);

	m_preRectPos = tempVec3;

	m_curRectPos = CVector3(m_preRectPos.GetPositionX() + NormalVec3.GetPositionX() * objVel * time,
		m_preRectPos.GetPositionY() + NormalVec3.GetPositionY() * objVel * time,
		m_preRectPos.GetPositionZ() + NormalVec3.GetPositionZ() * objVel * time);

	SetRectPosition(m_curRectPos.GetPositionX(), m_curRectPos.GetPositionY(), m_curRectPos.GetPositionZ());

	cout << GetRectPosition().GetPositionX() << "  " << GetRectPosition().GetPositionY() << " " << GetRectPosition().GetPositionZ() << endl;
}
