#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle() :
	Object()
{}

CRectangle::CRectangle(const Vec3f& pos, const Color& color4f, const RectLength& length) :
	Object(pos, color4f), m_RectSize(length)
{}

CRectangle::CRectangle(const Vec3f & pos, const Color & color4f, int length) :
	Object(pos, color4f), m_Length(length)
{}

CRectangle::CRectangle(float x, float y, float z, float r, float g, float b, float alpha, const RectLength & length) :
	Object(x, y, z, r, g, b, alpha), m_RectSize(length)
{}

CRectangle::CRectangle(float x, float y, float z, float r, float g, float b, float alpha, int length) :
	Object(x, y, z, r, g, b, alpha), m_Length(length)
{}

CRectangle::~CRectangle()
{
}

void CRectangle::SetRectLength(const RectLength & length)
{
	m_RectSize = length;
}

void CRectangle::SetRectLength(float w, float h)
{
	m_RectSize.width = w;
	m_RectSize.height = h;
}

void CRectangle::SetRectLength(float length)
{
	m_Length = length;
}

int CRectangle::GetSquareSize() const
{
	return static_cast<int>(m_Length);
}

RectLength CRectangle::GetRectSize() const
{
	return m_RectSize;
}

void CRectangle::Update(float fTime) 
{
	m_vec3fPos.x += m_vec3fDir.x * m_fVelocity * fTime;
	m_vec3fPos.y += m_vec3fDir.y * m_fVelocity * fTime;
	//m_vec3fPos.z += m_vec3fDir.z * m_fVelocity * fTime;

	if (m_vec3fPos.x >= WINDOW_WIDTH / 2 || m_vec3fPos.x <= -WINDOW_WIDTH / 2)
		m_vec3fDir.x = -m_vec3fDir.x;
	

	if (m_vec3fPos.y >= WINDOW_HEIGHT / 2 || m_vec3fPos.y <= -WINDOW_HEIGHT / 2)
		m_vec3fDir.y = -m_vec3fDir.y;
}

//void CRectangle::SetDirection(float x, float y, float z)
//{
//	m_vec3fdir.SetPositionX(x);
//	m_vec3fdir.SetPositionY(y);
//	m_vec3fdir.SetPositionZ(z);
//}

/*
void CRectangle::MovePosPerUpdate(CRectangle& rect, float objVel, float time = 1.0f)
{
	//CVector3 NormalVec3 = m_vector3.Normalized(vec);

	//m_preRectPos = vec;

	m_curRectPos += CVector3(rect.m_vec3fdir.GetPositionX() * objVel * time,
							rect.m_vec3fdir.GetPositionY() * objVel * time,
							rect.m_vec3fdir.GetPositionZ() * objVel * time);
	//m_curRectPos += CVector3(vec.GetPositionX() * m_dir * objVel * time,
	//	vec.GetPositionY() * m_dir * objVel * time,
	//	vec.GetPositionZ() * m_dir * objVel * time);

	//m_curRectPos = CVector3(m_preRectPos.GetPositionX() + NormalVec3.GetPositionX() * m_dir * objVel * time,
	//	m_preRectPos.GetPositionY() + NormalVec3.GetPositionY() * m_dir * objVel * time,
	//	m_preRectPos.GetPositionZ() + NormalVec3.GetPositionZ() * m_dir * objVel * time);

	if (m_curRectPos.GetPositionX() > WINDOW_WIDTH / 2 || m_curRectPos.GetPositionX() < -WINDOW_WIDTH / 2)
		rect.SetDirection = -rect.GetRectDirection;
	

	if (m_curRectPos.GetPositionY() > WINDOW_HEIGHT / 2 || m_curRectPos.GetPositionY() / 2)
		rect.SetDirection = -rect.GetRectDirection;

	//if (m_curRectPos.GetPositionX() < -250 || m_curRectPos.GetPositionX() > 250)
				//m_dir = -1;
	
	//if (m_curRectPos.GetPositionY() < -250 || m_curRectPos.GetPositionY() > 250)
				//m_dir = -1;
	// 250 -250 250 -250

	//vec.SetPositionX(m_curRectPos.GetPositionX());
	//vec.SetPositionY(m_curRectPos.GetPositionY());
	//vec.SetPositionZ(m_curRectPos.GetPositionZ());

	SetRectPosition(m_curRectPos.GetPositionX(), m_curRectPos.GetPositionY(), m_curRectPos.GetPositionZ());

	//cout << vec.GetPositionX() << "  " << vec.GetPositionY() << " " << vec.GetPositionZ() << endl;
}*/
