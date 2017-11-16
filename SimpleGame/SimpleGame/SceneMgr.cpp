#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
{
	m_render = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);


	m_objColl = new CObjectCollision();
	this->CreateBuilding();
}



void CSceneMgr::CreateBullet()
{
	CRectangle *bullet = nullptr;
	bullet = new CRectangle(
		0.0f, 0.0f, 1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f,
		2
	);

	bullet->SetObjectDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		1.0f);
	bullet->SetObjectSpeed(300.0f);
	bullet->SetObjectLife(20);
	bullet->SetObjectLifeTime(500);
	bullet->SetObjectType(Type::OBJECT_BULLET);

	m_rectVec.push_back(bullet);

}

void CSceneMgr::CreateBuilding()
{
	// 화면에 건물 1개를 배치
	m_building = new CRectangle(
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		50
	);

	m_building->SetObjectDirection(0.0f, 0.0f, 1.0f);
	m_building->SetObjectSpeed(0.0f);
	m_building->SetObjectLife(500);
	m_building->SetObjectLifeTime(5000);
	m_building->SetObjectType(Type::OBJECT_BUILDING);

	m_rectVec.push_back(m_building);

	m_texCharacter = m_render->CreatePngTexture("./Resources/minion.png");
}

void CSceneMgr::CreateArrow(CRectangle *rect)
{
	CRectangle *arrow = new CRectangle(
		rect->GetObjectPosXYZ(), Color{ 1.0f,1.0f,0.0f,1.0f }, 2
	);

	arrow->SetObjectDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		1.0f);

	arrow->SetObjectSpeed(100.0f);
	arrow->SetObjectLife(10);
	arrow->SetObjectType(Type::OBJECT_ARROW);
	arrow->SetCharacterTag(rect->GetCharacterTag());

	m_rectVec.push_back(arrow);
}

void CSceneMgr::CreateCharacter(float posX, float posY)
{
	// 캐릭터 생성
	if (m_rectVec.size() > MAX_OBJECTS_COUNT)
	{
		cout << "더 이상 객체를 생성할 수 없습니다." << endl;
	}
	else
	{
		m_putTag += 1;
		CRectangle * rect;
		rect = new CRectangle(
			posX - 250.0f, -posY + 500.0f - 250.0f , 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			10
		);
		rect->SetObjectDirection((1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								 (1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
								  1.0f);
		rect->SetObjectSpeed(300.0f);
		rect->SetObjectLife(10);
		rect->SetObjectType(Type::OBJECT_CHARACTER);
		rect->SetObjectLifeTime(1000);
		rect->SetObjectArrowCoolTime(0);
		rect->SetCharacterTag(m_putTag);

		m_rectVec.push_back(rect);
	}

}

void CSceneMgr::Update(float elapsedTime)
{
	/*
	// 주기적으로 모든 오브젝트들의 hp가 1씩 감소한다.
	m_hpDownTerm += elapsedTime * 100;
	if (m_hpDownTerm >= 60000)
	{
		for (int i = 0; i < m_rectVec.size(); ++i)
		{
			if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BULLET ||
				m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER)
			{
				//m_rectVec[i]->SetObjectLife(m_rectVec[i]->GetObjectLife() - 1);
				m_rectVec[i]->SetObjectLifeTime(m_rectVec[i]->GetObjectLifeTime() - 100);

				if (m_rectVec[i]->GetObjectLifeTime() < 0)
				{
					m_rectVec[i]->SetObjectLife(0);
				}
			}
		}

		//for (int i = 0; i < m_rectVec.size(); ++i)
		//{
		//	if (m_rectVec[i]->GetObjectLifeTime() < 0)
		//	{
		//		m_rectVec[i]->SetObjectLife(0);
		//	}
		//	else
		//	{
		//		if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BULLET ||
		//			m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER)
		//		{
		//			m_rectVec[i]->SetObjectLifeTime(
		//				m_rectVec[i]->GetObjectLifeTime() - 100);
		//		}
		//	}
		//}

		m_hpDownTerm = 0;
	}
	*/

	// 0.5초마다 붉은색상의 총알을 랜덤방향으로 생성한다.
	m_dur += elapsedTime * 100;
	if (m_dur >= 55000)
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
		{
			m_rectVec[i]->SetObjectColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_rectVec[i]->SetObjectArrowCoolTime(elapsedTime);
		}
		else if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BULLET)
			m_rectVec[i]->SetObjectColor(1.0f, 0.0f, 0.0f, 1.0f);

		if (m_rectVec[i]->GetCreateArrowFlag())
		{
			this->CreateArrow(m_rectVec[i]);
			m_rectVec[i]->SetCreateArrowFlag(false);
		}
		
	}

	 int temp, other_temp;
	// 캐릭터와 캐릭터 간의 충돌
	// 1. 충돌 시 빨간색으로 바뀜
	// 2. 충돌 데미지는 입지않음
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
					temp = m_rectVec[i]->GetObjectLife() - m_rectVec[j]->GetObjectLife();

					m_rectVec[i]->SetObjectLife(temp);
					m_rectVec[j]->SetObjectLife(0);
					m_flagOut = true; break;
				}
				
				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_BUILDING)
				{
					temp = m_rectVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife();

					m_rectVec[j]->SetObjectLife(temp);
					m_rectVec[i]->SetObjectLife(0);
					m_flagOut = true; break;
				}

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BULLET
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_CHARACTER)
				{
					temp = m_rectVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife();

					m_rectVec[j]->SetObjectLife(temp);
					m_rectVec[i]->SetObjectLife(0);
					m_flagOut = true; break;
				}

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_BULLET)
				{
					temp = m_rectVec[i]->GetObjectLife() - m_rectVec[j]->GetObjectLife();

					m_rectVec[i]->SetObjectLife(temp);
					m_rectVec[j]->SetObjectLife(0);
					m_flagOut = true; break;
				}

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_ARROW
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_CHARACTER)
				{
					if (m_rectVec[i]->GetCharacterTag() != m_rectVec[j]->GetCharacterTag()) 
					{
						temp = m_rectVec[i]->GetObjectLife() - m_rectVec[j]->GetObjectLife();
						other_temp = m_rectVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife();

						m_rectVec[i]->SetObjectLife(temp);
						m_rectVec[j]->SetObjectLife(other_temp);
						m_flagOut = true; break;
					}
				}

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_ARROW)
				{
					if (m_rectVec[i]->GetCharacterTag() != m_rectVec[j]->GetCharacterTag())
					{
						temp = m_rectVec[i]->GetObjectLife() - m_rectVec[j]->GetObjectLife();
						other_temp = m_rectVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife();

						m_rectVec[i]->SetObjectLife(temp);
						m_rectVec[j]->SetObjectLife(other_temp);
						m_flagOut = true; break;
					}
				}


				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_ARROW
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_BUILDING)
				{
					temp = m_rectVec[i]->GetObjectLife() - m_rectVec[j]->GetObjectLife();
					other_temp = m_rectVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife();

					m_rectVec[i]->SetObjectLife(temp);
					m_rectVec[j]->SetObjectLife(other_temp);
					m_flagOut = true; break;
				}

				if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BUILDING
					&& m_rectVec[j]->GetObjectType() == Type::OBJECT_ARROW)
				{
					temp = m_rectVec[i]->GetObjectLife() - m_rectVec[j]->GetObjectLife();
					other_temp = m_rectVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife();

					m_rectVec[i]->SetObjectLife(temp);
					m_rectVec[j]->SetObjectLife(other_temp);
					m_flagOut = true; break;
				}
			}
		}

		if (m_flagOut)
		{
			m_flagOut = false; break;
		}
	}

	//vector<CRectangle*>::iterator iter = m_rectVec.begin();
	if (m_rectVec.size() >= 1)
	{
		for (auto iter = m_rectVec.begin(); iter != m_rectVec.end();)
		{
			if ((*iter)->GetObjectLife() <= 0)
			{
				iter = m_rectVec.erase(iter);
			}
			else
				++iter;

		}
	}
}

void CSceneMgr::Draw()
{
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BUILDING)
		{
			m_render->DrawTexturedRect(
				m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
				m_rectVec[i]->GetSquareSize(), 0.0f, 0.0f, 0.0f, 0.5f, m_texCharacter);

		}
		else
		{
			m_render->DrawSolidRect(
				m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
				m_rectVec[i]->GetSquareSize(),
				m_rectVec[i]->GetObjectColorRGBA().r, m_rectVec[i]->GetObjectColorRGBA().g,
				m_rectVec[i]->GetObjectColorRGBA().b, m_rectVec[i]->GetObjectColorRGBA().a
			);
		}
	}
}

CSceneMgr::~CSceneMgr()
{
}


/*
if (m_rectVec[i]->GetObjectType() == Type::OBJECT_BUILDING)
{
if (m_rectVec[j]->GetObjectType() == Type::OBJECT_CHARACTER)
{

}
else if (m_rectVec[j]->GetObjectType() == Type::OBJECT_ARROW)
{

}
}

if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER)
{
if (m_rectVec[j]->GetObjectType() == Type::OBJECT_BULLET)
{

}
else if (m_rectVec[j]->GetObjectType() == Type::OBJECT_ARROW)
{

}
}

if (m_rectVec[i]->GetObjectType() == Type::OBJECT_CHARACTER)
{
if (m_rectVec[j]->GetObjectType() == Type::OBJECT_BULLET)
{

}
else if (m_rectVec[j]->GetObjectType() == Type::OBJECT_ARROW)
{

}
}
*/