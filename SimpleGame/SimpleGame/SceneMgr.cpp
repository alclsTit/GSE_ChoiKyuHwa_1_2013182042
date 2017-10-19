#include "stdafx.h"
#include "SceneMgr.h"

#define MIN_RAND_POS -200
#define MAX_RAND_POS 200

CSceneMgr::CSceneMgr()
{
	// Initialize Renderer
	//m_Render = new Renderer(500, 500);
	//if (!m_Render->IsInitialized())
	//{
	//	std::cout << "Renderer could not be initialized.. \n";
	//}

}

void CSceneMgr::CreateRect()
{
	if (m_rectVec.size() > MAX_OBJECTS_COUNT)
		cout << "더 이상 객체를 생성할 수 없습니다." << endl;
	else
	{
		default_random_engine dre;
		dre.seed(time(nullptr));

		uniform_real_distribution<float> rn_pos_x(-MIN_RAND_POS, MAX_RAND_POS);
		uniform_real_distribution<float> rn_pos_y(-MIN_RAND_POS, MAX_RAND_POS);

		m_Rect.SetRectColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Rect.SetRectPosition(rn_pos_x(dre), rn_pos_y(dre), 0.0f);
		m_Rect.SetSquareLength(40);

		m_rectVec.push_back(m_Rect);
	}

}

void CSceneMgr::Update()
{
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		CVector3 tempVec = m_rectVec[i].GetPosition();
		m_rectVec[i].MovePosPerUpdate(tempVec,0.5f, 1.0f);
	}
}

void CSceneMgr::Draw(Renderer *render)
{
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		render->DrawSolidRect(
			m_rectVec[i].GetRectPosition().GetPositionX(), m_rectVec[i].GetPosition().GetPositionY(),
			m_rectVec[i].GetPosition().GetPositionZ(), m_rectVec[i].GetSquareLength(),
			m_rectVec[i].GetRectColor().r, m_rectVec[i].GetRectColor().g,
			m_rectVec[i].GetRectColor().b, m_rectVec[i].GetRectColor().a);
	}
}

CSceneMgr::~CSceneMgr()
{
}
