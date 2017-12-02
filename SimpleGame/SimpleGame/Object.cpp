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

void Object::SetObjectPos(const Vec3f& pos)
{
	m_vec3fPos = pos;
}

void Object::SetObjectDirection(float x, float y, float z)
{
	m_vec3fDir = { x, y ,z };
}

void Object::SetObjectDirection(const Vec3f& dir)
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

void Object::SetObjectColor(const Color& color4f)
{
	m_oColor = color4f;
}

void Object::SetObjectLife(int life)
{
	m_life = life;
}

void Object::SetObjectLifeTime(float lfTime)
{
	m_lifeTime = lfTime;
}

void Object::SetObjectType(Type objtype)
{
	m_objectType = objtype;
}

void Object::SetObjectLevel(float level)
{
	m_objectLevel = level;
}

bool Object::SetObjectArrowCoolTime(float time)
{
	m_arrowTime += (time / 1000.0f);

	if (m_arrowTime >= ArrowCoolTime)
	{
		m_arrowTime = 0.0f;
		return true;
	}

	return false;
}

bool Object::SetObjectCharacterCoolTime(float time)
{
	m_characterTime += (time / 1000.0f);

	if (m_characterTime >= MyCharacterCoolTime)
	{
		m_characterTime = 0.0f;
		return true;
	}

	return false;
}

void Object::SetBulletObjectTime(float time)
{
	m_bulletTime += (time / 1000.0f);
}

bool Object::IsCanCharAniToNext()
{
	++m_aniTimeCnt;

	if (m_aniTimeCnt >= CHAR_MOVE_PER_FRAME)
	{
		m_aniTimeCnt = 0;
		return true;
	}

	return false;
}

void Object::SetCharAniMove(Type type)
{
	AniType anitype;

	aniMove.w_move += 1;

	if (type == Type::My_OBJECT_CHARACTER)
	{
		if (aniMove.w_move >= anitype.MyChar.Max_Width &&  aniMove.h_move < anitype.MyChar.Max_Height)
		{
			aniMove.w_move = 0; 
			aniMove.h_move += 1;
		}
			
		if (aniMove.h_move >= anitype.MyChar.Max_Height && aniMove.w_move >= anitype.MyChar.Max_Width)
		{
			aniMove.w_move = 0;
			aniMove.h_move = 0;
		}
					
	}

	if (type == Type::Enemy_OBJECT_CHARACTER)
	{
		if (aniMove.w_move >= anitype.MyChar.Max_Width &&  aniMove.h_move < anitype.MyChar.Max_Height)
		{
			aniMove.w_move = 0;
			aniMove.h_move += 1;
		}

		if (aniMove.h_move >= anitype.MyChar.Max_Height && aniMove.w_move >= anitype.MyChar.Max_Width)
		{
			aniMove.w_move = 0;
			aniMove.h_move = 0;
		}
			
	}
}

bool Object::IsCanCreateBulletTime(float time)
{
	m_createBulletTime += (time / 1000.0f);

	if (m_createBulletTime >= BuildingCreateBulletCoolTime)
	{
		m_createBulletTime = 0.0f;
		return true;
	}
	return false;
}

void Object::SetCreateArrowFlag(bool flag)
{
	m_createArrow = flag;
}

void Object::SetCharacterTag(int tag)
{
	m_tag = tag;
}

void Object::SetCanCreateMyCharacter(bool flag)
{
	m_createMyChar = flag;
}

void Object::SetObjectOriginalLife(int life)
{
	m_oriLife = life;
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

int Object::GetObjectLife() const
{
	return m_life;
}

Type Object::GetObjectType() const
{
	return m_objectType;
}

float Object::GetObjectLifeTime() const
{
	return m_lifeTime;
}

float Object::GetArrowCoolTime() const
{
	return m_arrowTime;
}

bool Object::GetCreateArrowFlag() const
{
	return m_createArrow;
}

int Object::GetCharacterTag() const
{
	return m_tag;
}

bool Object::GetCanCreateMyCharacter() const
{
	return m_createMyChar;
}

float Object::GetObjectLevel() const
{
	return m_objectLevel;
}

int Object::GetObjectOriginalLife() const
{
	return m_oriLife;
}

Vec3f Object::GetObjectDirection() const
{
	return m_vec3fDir;
}

float Object::GetBulletObjectTime() const
{
	return m_bulletTime;
}

AniMove Object::GetCharacterAniMove() const
{
	return aniMove;
}

void Object::Update(float elapsedTime)
{
}
