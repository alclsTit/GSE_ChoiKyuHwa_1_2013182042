#pragma once
#include "Object.h"
#include <vector>

struct RectLength
{
	int width;
	int height;
};

class CRectangle : public Object
{
private:
	RectLength m_RectSize{ 10,5 };
	int m_Length{ 10 };

	//float m_velocity;
	//CVector3 m_vec3fdir{ 0.0f,0.0f,0.0f };

	//CVector3 m_vector3;
	//CVector3 m_curRectPos;
	//CVector3 m_preRectPos;

public:
	CRectangle();
	CRectangle(const Vec3f& pos, const Color& color4f, const RectLength& length);
	CRectangle(const Vec3f& pos, const Color& color4f, int length);

	CRectangle(float x, float y, float z, float r, float g, float b, float alpha, const RectLength& length);
	CRectangle(float x, float y, float z, float r, float g, float b, float alpha, int length);
	~CRectangle();

	void SetRectLength(const RectLength& length);
	void SetRectLength(float w, float h);
	void SetRectLength(float length);

	int GetSquareSize() const;
	RectLength GetRectSize() const;

	virtual void Update(float fTime = 1.0);

};



//void SetRectPosition(float x, float y, float z) { SetPosition(x, y, z); }
//void SetRectColor(float r, float g, float b, float alpha) { SetColor(r, g, b, alpha); }

//void SetDirection(float x, float y, float z);

//CVector3 GetRectPosition() const { return GetPosition(); }
//Color GetRectColor() const { return GetColor(); }
//float GetRectWidth() const { return m_width; }
//float GetRectHeight() const { return m_height; }
//float SetRectLength() const { return m_size; }
//CVector3 GetRectDirection() const { return m_vec3fdir; }

//void MovePosPerUpdate(CRectangle& rect, float objVel, float time);