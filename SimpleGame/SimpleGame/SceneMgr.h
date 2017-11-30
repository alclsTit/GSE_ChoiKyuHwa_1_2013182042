#pragma once
#include "stdafx.h"
#include "Rectangle.h"
#include "ObjectCollision.h"
#include "Renderer.h"
#include <vector>
#include <random>


class CSceneMgr
{
private:
	vector<CRectangle*> m_rectVec;
	vector<CRectangle*> m_topVec;

	CObjectCollision *m_objColl{ nullptr };
	CRectangle *m_building{ nullptr };

	CRectangle *m_obj{ nullptr };

	bool m_flagOut{ false };

	float m_buildingTime{ 0.0f };
	float m_enyCharTime{ 0.0f };
	float m_myCharTime{ 0.0f };

	bool m_createMyChar{ false };
	bool m_cancCreChar{ true };

	int m_hpDownTerm{ 0 };
	int m_myCharTag{ 0 };
	int m_enyCharTag{ 0 };

	Renderer *m_render{ nullptr };

	GLuint m_texEnemyBuilding;
	GLuint m_texMyBuilding;
	GLuint m_texBackground;

	GLuint m_texAnimationSp;
	GLuint m_texEnyAnimationSp;

	GLuint m_texParticle;
	GLuint m_texEnyParticle;

	Level m_objLevel;
	
public:
	CSceneMgr();
	void CreateBuilding(vector<CRectangle*>& vec, Vec3f pos, Color color, 
		int size, int life, float lifeTime, Type type, char* imagePath);
	void CreateBullet(Vec3f createPos, Color color, Type type);
	void CreateArrow(CRectangle *rect);
	void CreateMyCharacter(float posX, float posY);
	void CreateEnemyCharacter();
	void Update(float elapsedTime);
	void Draw();
	int GetCurRectNum() const { return m_rectVec.size(); }
	~CSceneMgr();
};

