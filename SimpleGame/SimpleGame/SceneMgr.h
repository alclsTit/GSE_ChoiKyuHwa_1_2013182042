#pragma once
#include "stdafx.h"
#include "Rectangle.h"
#include "Renderer.h"
#include <vector>
#include <random>

class CSceneMgr
{

private:
	vector<CRectangle *> m_rectVec;

public:
	CSceneMgr();
	void CreateRect();
	void Update();
	void Draw(Renderer *render);
	int GetCurRectNum() const { return m_rectVec.size(); }
	~CSceneMgr();
};

