#pragma once
#include "stdafx.h"
#include "Vector.h"

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

class Object
{
protected:
	//CVector3 m_oPosition;
	Vec3f m_vec3fPos;
	Color m_oColor;
	float m_fVelocity;
	Vec3f m_vec3fDir;
	float m_life;

public:
	Object();
	Object(const Vec3f& vec3f, const Color& color4f);
	Object(float x, float y, float z, float r, float g, float b, float alpha);

	~Object();

	void SetObjectPos(float x, float y, float z);
	void SetObjectPos(const Vec3f& pos);
	void SetObjectDirection(float x, float y, float z);
	void SetObjectDirection(const Vec3f& dir);
	void SetObjectSpeed(float speed);
	void SetObjectColor(float r, float g, float b, float alpha);
	void SetObjectColor(const Color& color4f);
	void SetObjectLife(float life);

	float GetObjectPosX() const;
	float GetObjectPosY() const;
	float GetObjectPosZ() const;
	Vec3f GetObjectPosXYZ() const;
	Color GetObjectColorRGBA() const;
	float GetObjectLife() const;
	

	virtual void Update(float elapsedTime);

	//void SetColor(float r, float g, float b, float alpha) { m_oColor.r = r; m_oColor.g = g; m_oColor.b = b; m_oColor.a = alpha; }
	//CVector3 GetPosition() const { return m_oPosition; }
	//Color GetColor() const { return m_oColor; }

	//void Update();

};
