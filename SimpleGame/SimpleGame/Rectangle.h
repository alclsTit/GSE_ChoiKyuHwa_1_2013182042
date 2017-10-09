#pragma once
#include "Object.h"

class CRectangle : public Object
{
private:
	float m_width;
	float m_height;
	float m_size;

public:
	CRectangle();
	~CRectangle();

	void SetRectPosition(float x, float y, float z) { SetPosition(x, y, z); }
	void SetRectColor(float r, float g, float b, float alpha) { SetColor(r, g, b, alpha); }
	void SetRectLength(float w, float h) { m_width = w; m_height = h; }
	void SetSquareLength(float length) { m_size = length; }

	CVector3 GetRectPosition() const { return GetPosition(); }
	Color GetRectColor() const { return GetColor(); }
	float GetRectWidth() const { return m_width; }
	float GetRectHeight() const { return m_height; }
	float GetSquareLength() const { return m_size; }

};