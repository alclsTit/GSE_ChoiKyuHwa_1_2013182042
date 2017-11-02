#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
{
	m_objColl = new CObjectCollision();
	this->CreateBuilding();
}

void CSceneMgr::CreateBullet()
{
	CRectangle *bullet = nullptr;
	bullet = new CRectangle(
		0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f,
		5.0f
	);

	bullet->SetObjectDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		1.0f);
	bullet->SetObjectSpeed(300.0f);
	bullet->SetObjectLife(20);
	bullet->SetObjectType(Type::OBJECT_BULLET);

	m_rectVec.push_back(bullet);

}

void CSceneMgr::CreateBuilding()
{
	// ȭ�鿡 �ǹ� 1���� ��ġ
	m_building = new CRectangle(
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		50.0f
	);

	m_building->SetObjectDirection(0.0f, 0.0f, 1.0f);
	m_building->SetObjectSpeed(0.0f);
	m_building->SetObjectLife(500);
	m_building->SetObjectType(Type::OBJECT_BUILDING);

	m_rectVec.push_back(m_building);
}

void CSceneMgr::CreateCharacter(float posX, float posY)
{
	// ĳ���� ����
	if (m_rectVec.size() > MAX_OBJECTS_COUNT)
	{
		cout << "�� �̻� ��ü�� ������ �� �����ϴ�." << endl;
	}
	else
	{
		CRectangle * rect;
		rect = new CRectangle(
			posX - 250.0f, -posY + 500.0f - 250.0f , 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			10.0f
		);
		rect->SetObjectDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								 (1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								  1.0f);
		rect->SetObjectSpeed(300.0f);
		rect->SetObjectLife(10);
		rect->SetObjectType(Type::OBJECT_CHARACTER);

		m_rectVec.push_back(rect);
	}

}

void CSceneMgr::Update(float elapsedTime)
{
	//m_TotalETime += static_cast<int>(elapsedTime) % 1000;
	//if (static_cast<int>(m_TotalETime) % 1000 == 0)
	//{
	//	cout << "��" << endl;
	//}

	m_dur += elapsedTime * 100;

	if (m_dur >= 5000)
	{
		this->CreateBullet();
		m_dur = 0;
	}

	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		m_rectVec[i]->Update(elapsedTime);
		if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BUILDING)
			m_rectVec[i]->SetObjectColor(1.0f, 1.0f,0.0f, 1.0f);
		else if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER)
			m_rectVec[i]->SetObjectColor(1.0f, 1.0f, 1.0f, 1.0f);
		else if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BULLET)
			m_rectVec[i]->SetObjectColor(1.0f, 0.0f, 0.0f, 1.0f);
	}

	// ĳ���Ϳ� ĳ���� ���� �浹
	// 1. �浹 �� ���������� �ٲ�
	// 2. �浹 �������� ��������
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		for (int j = i + 1; j < m_rectVec.size(); ++j)
		{
			if (m_objColl->SquareOtherCollision(
				m_rectVec[i]->GetObjectPosXYZ(),
				m_rectVec[j]->GetObjectPosXYZ(),
				m_rectVec[j]->GetSquareSize(),
				m_rectVec[i]->GetSquareSize()))
			{
				//m_rectVec[i]->SetObjectColor(1.0f, 0.0f, 1.0f, 1.0f);
				//m_rectVec[j]->SetObjectColor(1.0f, 0.0f, 1.0f, 1.0f);

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BUILDING 
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_CHARACTER)
				{
					m_rectVec[i]->SetObjectLife(m_rectVec[i]->GetObjectLife() - 10);
					m_rectVec[j]->SetObjectLife(0);
					m_flagOut = true; break;
				}
				
				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_BUILDING)
				{
					m_rectVec[i]->SetObjectLife(0);
					m_rectVec[j]->SetObjectLife(m_rectVec[j]->GetObjectLife() - 10);
					m_flagOut = true; break;
				}

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BULLET
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_CHARACTER)
				{
					m_rectVec[i]->SetObjectLife(0);
					m_rectVec[j]->SetObjectLife(m_rectVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife());
					m_flagOut = true; break;
				}

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_BULLET)
				{
					m_rectVec[i]->SetObjectLife(m_rectVec[i]->GetObjectLife() - m_rectVec[j]->GetObjectLife());
					m_rectVec[j]->SetObjectLife(0);
					m_flagOut = true; break;
				}
			}
		}

		if (m_flagOut)
		{
			m_flagOut = false; break;
		}
	}


	

	// ĳ���Ϳ� �������� �浹
	// 1. ĳ���ʹ� �浹 �� �Ҹ�
	// 2. ������ �浹�� ĳ������ ��������ŭ �������� ����
	//for (int i = 0; i < m_rectVec.size(); ++i)
	//{
	//	if (m_objColl->SquareOtherCollision(m_building->GetObjectPosXYZ(),
	//		m_rectVec[i]->GetObjectPosXYZ(),
	//		m_rectVec[i]->GetSquareSize(),
	//		m_building->GetSquareSize()))
	//	{
	//		if (m_)
	//	}
	//}


	
	//vector<CRectangle*>::iterator iter = m_rectVec.begin();
	if (m_rectVec.size() >= 2)
	{
		for (auto iter = m_rectVec.begin(); iter != m_rectVec.end(); ++iter)
		{
			if ((*iter)->GetObjectLife() <= 0)
			{
				iter = m_rectVec.erase(iter);
				if (*iter == nullptr)
					break;
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
	
	//render->DrawSolidRect(
	//	m_building->GetObjectPosX(), m_building->GetObjectPosY(), m_building->GetObjectPosY(),
	//	m_building->GetSquareSize(),
	//	m_building->GetObjectColorRGBA().r, m_building->GetObjectColorRGBA().g,
	//	m_building->GetObjectColorRGBA().b, m_building->GetObjectColorRGBA().a
	//);

}

CSceneMgr::~CSceneMgr()
{
}
