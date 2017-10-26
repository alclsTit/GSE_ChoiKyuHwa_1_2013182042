#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
{
	m_objColl = new CObjectCollision();
}

void CSceneMgr::CreateRect(float posX, float posY)
{
	if (m_rectVec.size() > MAX_OBJECTS_COUNT)
	{
		cout << "더 이상 객체를 생성할 수 없습니다." << endl;
	}
	else
	{
		CRectangle * rect;
		rect = new CRectangle(
			posX - 250.0f, -posY + 500.0f - 250.0f , 1.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
			40.0f
		);
		rect->SetObjectDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								 (1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								  1.0f);
		rect->SetObjectSpeed(500.0f);
		rect->SetObjectLife(1000.0f);
	
		m_rectVec.push_back(rect);
	}

}

void CSceneMgr::Update(float elapsedTime)
{
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		m_rectVec[i]->Update(elapsedTime);
		m_rectVec[i]->SetObjectColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		for (int j = 0; j < m_rectVec.size(); ++j)
		{
			if (i != j && m_rectVec.size() >= 2)
			{
				if (m_objColl->SquareEachCollision(m_rectVec[i]->GetObjectPosXYZ(),
					m_rectVec[j]->GetObjectPosXYZ(),
					m_rectVec[i]->GetSquareSize()))
				{
					m_rectVec[i]->SetObjectColor(1.0f, 0.0f, 0.0f, 1.0f);
					m_rectVec[i]->SetObjectLife(m_rectVec[i]->GetObjectLife() - 1);
					//m_rectVec[j]->SetObjectColor(1.0f, 0.0f, 0.0f, 1.0f);			
				}	
			}
		}
	}

	
	//vector<CRectangle*>::iterator iter = m_rectVec.begin();
	if (m_rectVec.size() >= 1)
	{
		for (auto iter = m_rectVec.begin(); iter != m_rectVec.end(); ++iter)
		{
			if ((*iter)->GetObjectLife() <= 0)
			{
				iter = m_rectVec.erase(iter);
			}
		}
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
	}
}

CSceneMgr::~CSceneMgr()
{
}
