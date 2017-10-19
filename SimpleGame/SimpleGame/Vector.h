#pragma once

class CVector3
{
private:
	float x, y, z;

public:
	CVector3() { x = y = z = 0.0; }
	CVector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	static CVector3 Add(const CVector3& v1, const CVector3& v2) { return (CVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z)); }
	static CVector3 Subtract(const CVector3& v1, const CVector3& v2) { return (CVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z)); }
	float GetPositionX() const { return x; }
	float GetPositionY() const { return y; }
	float GetPositionZ() const { return z; }

	void SetPositionX(float s_x) { x = s_x; }
	void SetPositionY(float s_y) { y = s_y; }
	void SetPositionZ(float s_z) { z = s_z; }
	CVector3 Normalized(const CVector3& v) const;
};