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

	virtual void Update(float elapsedTime);

};


