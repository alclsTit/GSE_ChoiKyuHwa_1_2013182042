#pragma once

//class CVector3
//{
//private:
//	float x, y, z;
//
//public:
//	CVector3() { x = y = z = 0.0; }
//	CVector3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
//	static CVector3 Add(const CVector3& v1, const CVector3& v2) { return (CVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z)); }
//	static CVector3 Subtract(const CVector3& v1, const CVector3& v2) { return (CVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z)); }
//	float GetPositionX() const { return x; }
//	float GetPositionY() const { return y; }
//	float GetPositionZ() const { return z; }
//
//	void SetPositionX(float s_x) { x = s_x; }
//	void SetPositionY(float s_y) { y = s_y; }
//	void SetPositionZ(float s_z) { z = s_z; }
//	CVector3 Normalized(const CVector3& v) const;
//};

template <typename T>
struct Vector3D
{
	T x, y, z;
	Vector3D() : x(0), y(0), z(0) {}
	template <typename T1>
	Vector3D(T1 _x, T1 _y, T1 _z) : x(static_cast<T>(_x)), y(static_cast<T>(_y)), z(static_cast<T>(_z)) {}
	template <typename T1>
	Vector3D(const Vector3D<T1>& pVec) : x(static_cast<T>(pVec.x)), y(static_cast<T>(pVec.y)), z(static_cast<T>(pVec.z)) {}
};

template <typename T>
using Vec3d = Vector3D<T>;
using Vec3f = Vector3D<float>;

template <typename T> 
inline float Length(const Vec3d<T>& pVec) { return sqrt(pVec.x * pVec.x + pVec.y * pVec.y + pVec.z * pVec.z); }

template <typename T>
inline Vec3d<T>& Normalize(Vec3d<T>& pVec) 
{
	float fLength = Length(pVec); 
	if (fLegth != 0.0f);
	return (pVec.x /= fLength; pVec.y /= fLength pVec.z /= fLength;)
}

