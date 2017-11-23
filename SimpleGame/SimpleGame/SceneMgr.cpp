#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
{
	m_render = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_objColl = new CObjectCollision();

	m_obj = new CRectangle();

	//�Ʊ� ���� - ����
	this->CreateBuilding(m_rectVec, { -150.0f, -250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
						100, 500, 5000, Type::My_OBJECT_BUILDING, "./Resources/minion.png");

	this->CreateBuilding(m_rectVec, { 0.0f, -250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::My_OBJECT_BUILDING, "./Resources/minion.png");

	this->CreateBuilding(m_rectVec, { 150.0f, -250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::My_OBJECT_BUILDING, "./Resources/minion.png");

	
	//�� ���� - ž
	this->CreateBuilding(m_topVec, { -150.0f, 250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
						100, 500, 5000, Type::Enemy_OBJECT_BUILDING, "./Resources/bear.png");

	this->CreateBuilding(m_topVec, { 0.0f, 250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::Enemy_OBJECT_BUILDING, "./Resources/bear.png");

	this->CreateBuilding(m_topVec, { 150.0f, 250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::Enemy_OBJECT_BUILDING, "./Resources/bear.png");
}


void CSceneMgr::CreateBuilding(vector<CRectangle*>& vec, Vec3f pos, Color color, 
								int size, int life, float lifeTime, Type type, char* imagePath)
{
	// ȭ�鿡 �ǹ� 1���� ��ġ
	m_building = new CRectangle
	(
		pos.x, pos.y, pos.z,
		color.r, color.g, color.b, color.a,
		size
	);

	// ����
	m_building->SetObjectDirection(0.0f, 0.0f, 1.0f);
	m_building->SetObjectSpeed(0.0f);

	// ����
	m_building->SetObjectLife(life);
	m_building->SetObjectLifeTime(lifeTime);
	m_building->SetObjectType(type);

	vec.push_back(m_building);

	if (type == Type::Enemy_OBJECT_BUILDING)
		m_texEnemyBuilding = m_render->CreatePngTexture(imagePath);

	if (type == Type::My_OBJECT_BUILDING)
		m_texMyBuilding = m_render->CreatePngTexture(imagePath);
}


void CSceneMgr::CreateBullet(Vec3f createPos, Color color, Type type)
{
	CRectangle *bullet = nullptr;
	bullet = new CRectangle
	(
		createPos.x, createPos.y, createPos.z,
		color.r, color.g, color.b, color.a,
		2
	);

	bullet->SetObjectDirection
	(
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		1.0f
	);

	bullet->SetObjectSpeed(300.0f);
	bullet->SetObjectLife(20);
	bullet->SetObjectLifeTime(500);

	bullet->SetObjectType(type);

	if (type == Type::My_OBJECT_BULLET)
		m_rectVec.push_back(bullet);

	if (type == Type::Enemy_OBJECT_BULLET)
		m_topVec.push_back(bullet);
}



void CSceneMgr::CreateArrow(CRectangle *rect)
{
	Color color;
	if (rect->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
		color = { 0.5f,0.2f,0.7f,1.0f };
	if (rect->GetObjectType() == Type::My_OBJECT_CHARACTER)
		color = { 1.0f,1.0f,0.0f,1.0f };

	CRectangle *arrow = new CRectangle
	(
		rect->GetObjectPosXYZ(), 
		color, 
		2
	);

	arrow->SetObjectDirection
	(
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		1.0f
	);

	arrow->SetObjectSpeed(100.0f);
	arrow->SetObjectLife(10);
	arrow->SetCharacterTag(rect->GetCharacterTag());

	if (rect->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
	{
		arrow->SetObjectType(Type::Enemy_OBJECT_ARROW);
		m_topVec.push_back(arrow);
	}

	if (rect->GetObjectType() == Type::My_OBJECT_CHARACTER)
	{
		arrow->SetObjectType(Type::My_OBJECT_ARROW);
		m_rectVec.push_back(arrow);
	}
}



void CSceneMgr::CreateMyCharacter(float posX, float posY)
{
	// ĳ���� ����

	if ((posY >= 400 & m_cancCreChar) == 1)
	{
		m_myCharTag += 1;

		CRectangle * rect;
		rect = new CRectangle
		(
			posX - 250.0f, -posY + 800.0f - 400.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			10
		);
		rect->SetObjectDirection
		(
			(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
			(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
			1.0f
		);

		rect->SetObjectSpeed(300.0f);
		rect->SetObjectLife(10);
		rect->SetObjectType(Type::My_OBJECT_CHARACTER);
		rect->SetObjectLifeTime(1000);
		rect->SetCharacterTag(m_myCharTag);

		m_rectVec.push_back(rect);

		m_createMyChar = true;
		m_cancCreChar = false;

		m_obj->SetCanCreateMyCharacter(false);
	}
}

void CSceneMgr::CreateEnemyCharacter()
{
	//�� ĳ���� ����
	m_enyCharTag += 1;

	CRectangle * rect;
	rect = new CRectangle
	(
		rand() % 400 - 200, rand() % 250, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		10
	);
	rect->SetObjectDirection
	(
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		1.0f
	);

	rect->SetObjectSpeed(300.0f);
	rect->SetObjectLife(10);
	rect->SetObjectType(Type::Enemy_OBJECT_CHARACTER);
	rect->SetObjectLifeTime(1000);
	rect->SetCharacterTag(m_enyCharTag);

	m_topVec.push_back(rect);
}

void CSceneMgr::Update(float elapsedTime)
{
	int temp, temp_other;

	//--------------------------------------------------------------------------------- 
	//�� ĳ����, ��� ĳ����, ���� �ֱ� ����

	m_buildingTime += (elapsedTime / 1000.0f);
	m_enyCharTime += (elapsedTime / 1000.0f);

	if (m_createMyChar)
	{
		m_myCharTime += (elapsedTime / 1000.0f);

		if (m_myCharTime >= MyCharacterCoolTime)
		{
			m_myCharTime = 0.0f;
			m_createMyChar = false;
			m_cancCreChar = true;
		}
	}

	if (m_enyCharTime >= EnyCharacterCoolTime)
	{
		this->CreateEnemyCharacter();
		m_enyCharTime = 0.0f;
	}

	if (m_buildingTime >= BuildingCoolTime)
	{
		//������ ��ġ�� ��ȭ���� �����Ƿ� ��������� ����

		//bottom
		this->CreateBullet({ -150.0f, -250.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, Type::My_OBJECT_BULLET);
		this->CreateBullet({ 0.0f, -250.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, Type::My_OBJECT_BULLET);
		this->CreateBullet({ 150.0f, -250.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, Type::My_OBJECT_BULLET);

		//top
		this->CreateBullet({ -150.0f, 250.0f , 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, Type::Enemy_OBJECT_BULLET);
		this->CreateBullet({ 0.0f, 250.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, Type::Enemy_OBJECT_BULLET);
		this->CreateBullet({ 150.0f, 250.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, Type::Enemy_OBJECT_BULLET);

		m_buildingTime = 0.0f;
	}

	//---------------------------------------------------------------------------------
	// ĳ���� ���� �� ȭ���� �ֱ� ����

	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		m_rectVec[i]->Update(elapsedTime);
		if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_CHARACTER)
		{
			if (m_rectVec[i]->SetObjectArrowCoolTime(elapsedTime))
			{
				this->CreateArrow(m_rectVec[i]);
			}
		}
	}

	for (int i = 0; i < m_topVec.size(); ++i)
	{
		m_topVec[i]->Update(elapsedTime);
		if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER && m_enyCharTime != 0.0f)
		{
			if (m_topVec[i]->SetObjectArrowCoolTime(elapsedTime))
			{
				this->CreateArrow(m_topVec[i]);
			}
		}
	}

	//---------------------------------------------------------------------------------
	// ���� ������� �浹üũ

	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		for (int j = 0; j < m_topVec.size(); ++j)
		{
			if (m_objColl->SquareOtherCollision(m_rectVec[i]->GetObjectPosXYZ(), m_topVec[j]->GetObjectPosXYZ(),
											    m_rectVec[i]->GetSquareSize(), m_topVec[j]->GetSquareSize()))
			{
				temp = m_rectVec[i]->GetObjectLife() - m_topVec[j]->GetObjectLife();
				temp_other = m_topVec[j]->GetObjectLife() - m_rectVec[i]->GetObjectLife();

				//���� ������ ����� �ҷ�, ĳ���� �浹
				if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BUILDING
					&& (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER||
						m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_ARROW))
				{
					m_rectVec[i]->SetObjectLife(temp);
					m_topVec[j]->SetObjectLife(temp_other);

					//cout << "��" << i << "��° ������ ü�� = " <<  m_rectVec[i]->GetObjectLife() << endl;
				}

				//���� �ҷ��� ����� ����, ĳ���� �浹
				if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BULLET
					&& m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
				{
					m_rectVec[i]->SetObjectLife(temp);
					m_topVec[j]->SetObjectLife(temp_other);

					//cout << "��" << j << "��° ������ ü�� = " << m_topVec[j]->GetObjectLife() << endl;
				}

				
				//���� ĳ���Ϳ� ����� ����, �ҷ�, �ַο�� �浹
				if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_CHARACTER 
					&& (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BUILDING ||
						m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BULLET ||
						m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_ARROW))
				{
					m_rectVec[i]->SetObjectLife(temp);
					m_topVec[j]->SetObjectLife(temp_other);

					//if (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
					//	cout << "��" << j << "��° ������ ü�� = " << m_topVec[j]->GetObjectLife() << endl;
					//
					//if (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BULLET)
					//	cout << "��" << j << "��° �ҷ��� ü�� = " << m_topVec[j]->GetObjectLife() << endl;
					//
					//if (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_ARROW)
					//	cout << "��" << j << "��° �ַο��� ü�� = " << m_topVec[j]->GetObjectLife() << endl;
				}

				//���� �ַο�� ����� ĳ���� �浹
				if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_ARROW
					&& (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER ||
						m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BUILDING))
				{
					m_rectVec[i]->SetObjectLife(temp);
					m_topVec[j]->SetObjectLife(temp_other);

					//if (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
					//	cout << "��" << j << "��° ������ ü�� = " << m_topVec[j]->GetObjectLife() << endl;
					//
					//if (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
					//	cout << "��" << j << "��° ĳ������ ü�� = " << m_topVec[j]->GetObjectLife() << endl;

				}
				
			}
		}
	}

	//---------------------------------------------------------------------------------
	//������Ʈ ����
	//vector<CRectangle*>::iterator iter = m_rectVec.begin();

	if (m_rectVec.size() >= 1)
	{
		for (auto iter = m_rectVec.begin(); iter != m_rectVec.end();)
		{
			if ((*iter)->GetObjectLife() <= 0)
				iter = m_rectVec.erase(iter);
			else
				++iter;
		}
	}

	if (m_topVec.size() >= 1)
	{
		for (auto iter = m_topVec.begin(); iter != m_topVec.end();)
		{
			if ((*iter)->GetObjectLife() <= 0)
				iter = m_topVec.erase(iter);
			else
				++iter;
		}
	}

	//---------------------------------------------------------------------------------
}


void CSceneMgr::Draw()
{
	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BUILDING)
		{
			m_render->DrawTexturedRect
			(
				m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), 
				m_rectVec[i]->GetObjectPosZ(),
				m_rectVec[i]->GetSquareSize(), 0.0f, 0.0f, 0.0f, 0.5f, m_texMyBuilding
			);
		}
		else
		{
			m_render->DrawSolidRect
			(
				m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
				m_rectVec[i]->GetSquareSize(),
				m_rectVec[i]->GetObjectColorRGBA().r, m_rectVec[i]->GetObjectColorRGBA().g,
				m_rectVec[i]->GetObjectColorRGBA().b, m_rectVec[i]->GetObjectColorRGBA().a
			);
		}
	}

	for (int i = 0; i < m_topVec.size(); ++i)
	{
		if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
		{
			m_render->DrawTexturedRect
			(
				m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY(), 
				m_topVec[i]->GetObjectPosZ(),
				m_topVec[i]->GetSquareSize(), 0.0f, 0.0f, 0.0f, 0.5f, m_texEnemyBuilding
			);
		}
		else
		{
			m_render->DrawSolidRect
			(
				m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY(), m_topVec[i]->GetObjectPosZ(),
				m_topVec[i]->GetSquareSize(),
				m_topVec[i]->GetObjectColorRGBA().r, m_topVec[i]->GetObjectColorRGBA().g,
				m_topVec[i]->GetObjectColorRGBA().b, m_topVec[i]->GetObjectColorRGBA().a
			);
		}
	}
}


CSceneMgr::~CSceneMgr()
{

}

