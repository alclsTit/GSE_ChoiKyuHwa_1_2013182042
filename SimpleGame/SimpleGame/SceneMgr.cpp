#include "stdafx.h"
#include "SceneMgr.h"

#define MIN_RAND_POS -200
#define MAX_RAND_POS 200

CSceneMgr::CSceneMgr()
{

}

void CSceneMgr::CreateRect()
{
	//int r_x, r_y = 0;
	if (m_rectVec.size() > MAX_OBJECTS_COUNT)
	{
		cout << "더 이상 객체를 생성할 수 없습니다." << endl;
	}
	else
	{
		CRectangle * rect;
		rect = new CRectangle(
			200 - rand() % 400, 200 - rand() % 400, 1.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
			40.0f
		);

		//rect->SetObjectColor(0.0f, 0.0f, 0.0f, 1.0f);
		rect->SetObjectDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								 (1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								  1.0f);

		//rect->SetObjectPos(200 - rand() % 400, 200 - rand() % 400, 1.0f);
		rect->SetObjectSpeed(0.01f);
		//rect->SetRectLength(40.0f);
		
		m_rectVec.push_back(rect);
		//default_random_engine dre;
		//dre.seed(time(nullptr));

		//uniform_int_distribution<int> rn_x(MIN_RAND_POS, MAX_RAND_POS);
		//uniform_int_distribution<int> rn_y(MIN_RAND_POS, MAX_RAND_POS);

		//r_x = rn_x(dre);
		//r_y = rn_y(dre);

		//m_Rect.SetRectColor(1.0f, 1.0f, 1.0f, 1.0f);
		//m_Rect.SetRectPosition(r_x, r_y, 0.0f);
		//m_Rect.SetSquareLength(40);
		//m_Rect.SetDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		//					(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		//					1.0f);
		//
		//m_rectVec.push_back(m_Rect);
	}

}

void CSceneMgr::Update()
{
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		//CVector3 tempVec = m_rectVec[i].GetRectPosition();
		//m_rectVec[i].MovePosPerUpdate(m_rectVec[i],0.01f, 1.0f);
		m_rectVec[i]->Update();
	}
}

void CSceneMgr::Draw(Renderer *render)
{
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		render->DrawSolidRect(
			m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
			m_rectVec[i]->GetSquareSize(),
			m_rectVec[i]->GetObjectColorRGBA().r, m_rectVec[i]->GetObjectColorRGBA().g,
			m_rectVec[i]->GetObjectColorRGBA().b, m_rectVec[i]->GetObjectColorRGBA().a
		);
		//render->DrawSolidRect(
		//	m_rectVec[i].GetRectPosition().GetPositionX(), m_rectVec[i].GetPosition().GetPositionY(),
		//	m_rectVec[i].GetPosition().GetPositionZ(), m_rectVec[i].GetSquareLength(),
		//	m_rectVec[i].GetRectColor().r, m_rectVec[i].GetRectColor().g,
		//	m_rectVec[i].GetRectColor().b, m_rectVec[i].GetRectColor().a);
	}
}

CSceneMgr::~CSceneMgr()
{
}
