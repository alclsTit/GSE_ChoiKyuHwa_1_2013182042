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
	CObjectCollision *m_objColl;
	CRectangle *m_building;
	bool m_flagOut{ false };
	int m_dur{ 0 };
	int m_hpDownTerm{ 0 };
	int m_putTag{ 0 };

	Renderer *m_render;
	GLuint m_texCharacter;

	
public:
	CSceneMgr();
	void CreateBullet();
	void CreateBuilding();
	void CreateArrow(CRectangle *rect);
	void CreateCharacter(float posX, float posY);
	void Update(float elapsedTime);
	void Draw();
	int GetCurRectNum() const { return m_rectVec.size(); }
	~CSceneMgr();
};

