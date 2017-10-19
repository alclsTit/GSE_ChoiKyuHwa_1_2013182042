#pragma once
#include "stdafx.h"
#include "Rectangle.h"
#include "Renderer.h"
#include <vector>
#include <random>

class CSceneMgr
{
private:
	CRectangle m_Rect;
	vector<CRectangle> m_rectVec;
	Renderer *m_Render = nullptr;
public:
	CSceneMgr();
	void CreateRect();
	void Update();
	void Draw();
	int GetCurRectNum() const { return m_rectVec.size(); }
	~CSceneMgr();
};

