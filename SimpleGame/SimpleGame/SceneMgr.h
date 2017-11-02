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
	//int m_TotalETime{ 0};
	int m_dur{ 0 };
	Renderer *render;

public:
	CSceneMgr();
	void CreateBullet();
	void CreateBuilding();
	void CreateCharacter(float posX, float posY);
	void Update(float elapsedTime);
	void Draw(Renderer *render);
	int GetCurRectNum() const { return m_rectVec.size(); }
	~CSceneMgr();
};

