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
public:
	CSceneMgr();
	void CreateRect(float posX, float posY);
	void Update(float elapsedTime);
	void Draw(Renderer *render);
	int GetCurRectNum() const { return m_rectVec.size(); }
	~CSceneMgr();
};

