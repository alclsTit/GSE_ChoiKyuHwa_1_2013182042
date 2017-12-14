#pragma once
#include "stdafx.h"
#include "Vector.h"

struct AniMove
{
	int w_move;
	int h_move;
};

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

	int m_life;
	float m_lifeTime{ 1000 };

	Type m_objectType;

	float m_arrowTime{ 0.0f };
	bool  m_createArrow{ false };

	float m_characterTime{ 0.0f };
	bool m_createMyChar{ true };

	int   m_tag{ 0 };

	float m_objectLevel;
	int m_oriLife{ 0 };

	AniMove aniMove{ 0, 0 };
	float m_aniTime{ 0.0f };
	int m_aniTimeCnt{ 0 };

	//불렛 파티클이 시간주기마다 생성되도록(인자로 넘겨준 값)
	float m_bulletTime{ 0.0f };
	//float m_oriParticleAlpha{ 1.0f };
	//float m_particleAlpha{ 1.0f };
	//float m_decAlphaVal{ 0.0f };

	//불렛의 생성주기를 위해 빌딩에 설정
	float m_createBulletTime{ 0.0f };
	
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
	void SetObjectLife(int life);
	void SetObjectLifeTime(float lfTime);
	void SetObjectType(Type objtype);
	void SetObjectLevel(float level);

	bool SetObjectArrowCoolTime(float time);
	bool SetObjectCharacterCoolTime(float time);

	void SetCreateArrowFlag(bool flag);
	void SetCharacterTag(int tag);
	void SetCanCreateMyCharacter(bool flag);
	void SetObjectOriginalLife(int life);
	void SetBulletObjectTime(float time);
	bool IsCanCharAniToNext();
	void SetCharAniMove(Type type);
	bool IsCanCreateBulletTime(float time);

	float GetObjectPosX() const;
	float GetObjectPosY() const;
	float GetObjectPosZ() const;
	Vec3f GetObjectPosXYZ() const;
	Color GetObjectColorRGBA() const;
	int GetObjectLife() const;
	Type GetObjectType() const;
	float GetObjectLifeTime() const;
	float GetArrowCoolTime() const;
	bool GetCreateArrowFlag() const;
	int GetCharacterTag() const;
	bool GetCanCreateMyCharacter() const;
	float GetObjectLevel() const;
	int GetObjectOriginalLife() const;
	Vec3f GetObjectDirection() const;
	float GetBulletObjectTime() const;
	AniMove GetCharacterAniMove() const;
	
	virtual void Update(float elapsedTime);

	//void SetColor(float r, float g, float b, float alpha) { m_oColor.r = r; m_oColor.g = g; m_oColor.b = b; m_oColor.a = alpha; }
	//CVector3 GetPosition() const { return m_oPosition; }
	//Color GetColor() const { return m_oColor; }

	//void Update();

};
