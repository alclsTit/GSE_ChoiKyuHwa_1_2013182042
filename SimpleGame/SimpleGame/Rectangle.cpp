#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::MovePosPerUpdate(CVector3& vec, float objVel, float time = 1)
{
	CVector3 NormalVec3 = m_vector3.Normalized(vec);

	m_preRectPos = vec;

	m_curRectPos = CVector3(m_preRectPos.GetPositionX() + NormalVec3.GetPositionX() * m_dir * objVel * time,
		m_preRectPos.GetPositionY() + NormalVec3.GetPositionY() * m_dir * objVel * time,
		m_preRectPos.GetPositionZ() + NormalVec3.GetPositionZ() * m_dir * objVel * time);

	if (m_curRectPos.GetPositionX() < -250 || m_curRectPos.GetPositionX() > 250)
				m_dir = -1;
	
	//if (m_curRectPos.GetPositionY() < -250 || m_curRectPos.GetPositionY() > 250)
				//m_dir = -1;
	// 250 -250 250 -250

	vec.SetPositionX(m_curRectPos.GetPositionX());
	vec.SetPositionY(m_curRectPos.GetPositionY());
	vec.SetPositionZ(m_curRectPos.GetPositionZ());
	//SetRectPosition(m_curRectPos.GetPositionX(), m_curRectPos.GetPositionY(), m_curRectPos.GetPositionZ());

	cout << vec.GetPositionX() << "  " << vec.GetPositionY() << " " << vec.GetPositionZ() << endl;
}
