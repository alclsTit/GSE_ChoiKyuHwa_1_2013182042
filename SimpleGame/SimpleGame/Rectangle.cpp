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

void CRectangle::Update(float elapsedTime)
{
	auto newElapsedTime = elapsedTime / 1500.0f;

	//m_vec3fPos.z += m_vec3fDir.z * m_fVelocity * fTime;

	if (m_vec3fPos.x >= WINDOW_WIDTH / 2 || m_vec3fPos.x <= -WINDOW_WIDTH / 2 )
		m_vec3fDir.x = -m_vec3fDir.x;

	if (m_vec3fPos.y >= WINDOW_HEIGHT / 2  || m_vec3fPos.y <= -WINDOW_HEIGHT / 2)
		m_vec3fDir.y = -m_vec3fDir.y;

	if (m_vec3fPos.x >= WINDOW_WIDTH / 2 - GetSquareSize() / 2 || m_vec3fPos.x <= -WINDOW_WIDTH / 2 + GetSquareSize() / 2)
		m_vec3fDir.x = -m_vec3fDir.x;
	
	if (m_vec3fPos.y >= WINDOW_HEIGHT / 2 - GetSquareSize() / 2 || m_vec3fPos.y <= -WINDOW_HEIGHT / 2 + GetSquareSize() / 2)
		m_vec3fDir.y = -m_vec3fDir.y;

	m_vec3fPos.x += m_vec3fDir.x * m_fVelocity * newElapsedTime;
	m_vec3fPos.y += m_vec3fDir.y * m_fVelocity * newElapsedTime;


}

