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
private:
	CVector3 m_oPosition;
	Color m_oColor;
public:
	Object();
	~Object();

	void SetPosition(float x, float y, float z) { m_oPosition = CVector3(x, y, z);}
	void SetColor(float r, float g, float b, float alpha) { m_oColor.r = r; m_oColor.g = g; m_oColor.b = b; m_oColor.a = alpha; }
	CVector3 GetPosition() const { return m_oPosition; }
	Color GetColor() const { return m_oColor; }

};
