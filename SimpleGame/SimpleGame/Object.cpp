#include "stdafx.h"
#include "Object.h"


Object::Object() :
	m_vec3fPos({ 0.0f,0.0f,0.0f }),
	m_oColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
	m_fVelocity(0.0f),
	m_vec3fDir({ 0.0f,0.0f,0.0f })
{}

Object::Object(const Vec3f & vec3f, const Color & color4f) :
	m_vec3fPos(vec3f),
	m_oColor(color4f),
	m_vec3fDir({ 0.0f,0.0f,0.0f })
{}

Object::Object(float x, float y, float z, float r, float g, float b, float alpha) :
	m_vec3fPos({ x,y,z }),
	m_oColor({ r,g,b,alpha })
{
}

//void Object::Update()
//{
//
//}


Object::~Object()
{
}

void Object::SetObjectPos(float x, float y, float z)
{
	m_vec3fPos = { x, y ,z };
}

void Object::SetObjectPos(const Vec3f & pos)
{
	m_vec3fPos = pos;
}

void Object::SetObjectDirection(float x, float y, float z)
{
	m_vec3fDir = { x, y ,z };
}

void Object::SetObjectDirection(const Vec3f & dir)
{
	m_vec3fDir = dir;
}

void Object::SetObjectSpeed(float speed)
{
	m_fVelocity = speed;
}

void Object::SetObjectColor(float r, float g, float b, float alpha)
{
	m_oColor = { r, g, b, alpha };
}

void Object::SetObjectColor(const Color & color4f)
{
	m_oColor = color4f;
}

void Object::SetObjectLife(float life)
{
	m_life = life;
}

void Object::SetObjectType(Type objtype)
{
	m_objectType = objtype;
}

float Object::GetObjectPosX() const
{
	return m_vec3fPos.x;
}

float Object::GetObjectPosY() const
{
	return m_vec3fPos.y;
}

float Object::GetObjectPosZ() const
{
	return m_vec3fPos.z;
}

Vec3f Object::GetObjectPosXYZ() const
{
	return m_vec3fPos;
}

Color Object::GetObjectColorRGBA() const
{
	return m_oColor;
}

float Object::GetObjectLife() const
{
	return m_life;
}

Type Object::GetObjectType() const
{
	return m_objectType;
}

void Object::Update(float elapsedTime)
{
}
