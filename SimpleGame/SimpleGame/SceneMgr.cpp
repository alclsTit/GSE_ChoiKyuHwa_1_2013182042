#include "stdafx.h"
#include "SceneMgr.h"
#include <cmath>

CSceneMgr::CSceneMgr()
{
	m_render = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_objColl = new CObjectCollision();

	m_obj = new CRectangle();

	//�������
	m_backBGM = new CreateSounds("./Sounds/BackgroundBGM/MapleStoryTitle.mp3", 1.0f, true);

	//����
	m_weather = new CWeatherEffect("./Resources/Particles/snow.png", m_render);

	//�Ʊ� ���� - ����
	this->CreateBuilding(m_rectVec, { -150.0f, -250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
						100, 500, 5000, Type::My_OBJECT_BUILDING, "./Resources/Objects/minion.png");

	this->CreateBuilding(m_rectVec, { 0.0f, -250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::My_OBJECT_BUILDING, "./Resources/Objects/minion.png");

	this->CreateBuilding(m_rectVec, { 150.0f, -250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::My_OBJECT_BUILDING, "./Resources/Objects/minion.png");

	
	//�� ���� - ž
	this->CreateBuilding(m_topVec, { -150.0f, 250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
						100, 500, 5000, Type::Enemy_OBJECT_BUILDING, "./Resources/Objects/bear.png");

	this->CreateBuilding(m_topVec, { 0.0f, 250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::Enemy_OBJECT_BUILDING, "./Resources/Objects/bear.png");

	this->CreateBuilding(m_topVec, { 150.0f, 250.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },
		100, 500, 5000, Type::Enemy_OBJECT_BUILDING, "./Resources/Objects/bear.png");

	m_texBackground = m_render->CreatePngTexture("./Resources/Background/background.png");

	m_texAnimationSp = m_render->CreatePngTexture("./Resources/Characters/Character01.png");
	m_texEnyAnimationSp = m_render->CreatePngTexture("./Resources/Characters/Character02.png");

	m_texParticle = m_render->CreatePngTexture("./Resources/Particles/particle03.png");
	m_texEnyParticle = m_render->CreatePngTexture("./Resources/Particles/particle02.png");

	m_texMyCharParticle = m_render->CreatePngTexture("./Resources/Particles/particle05.png");
	m_texEnemyCharParticle = m_render->CreatePngTexture("./Resources/Particles/particle06.png");

	m_texAirAnimationSp = m_render->CreatePngTexture("./Resources/Characters/Character03.png");

	m_texMyAirCharParticle = m_render->CreatePngTexture("./Resources/Particles/particle07.png");
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
	m_building->SetObjectLevel(m_objLevel.Level_Building);
	m_building->SetObjectOriginalLife(life);

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
	bullet->SetObjectLife(BulletLife);
	bullet->SetObjectLifeTime(500);
	bullet->SetObjectType(type);
	bullet->SetObjectLevel(m_objLevel.Level_Bullet);
	bullet->SetObjectOriginalLife(BulletLife);

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
	arrow->SetObjectLife(ArrowLife);
	arrow->SetCharacterTag(rect->GetCharacterTag());
	arrow->SetObjectLevel(m_objLevel.Level_Arrow);
	arrow->SetObjectOriginalLife(ArrowLife);

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
			30
		);
		//rect->SetObjectDirection
		//(
		//	(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		//	(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
		//	1.0f
		//);
		rect->SetObjectDirection
		(
			1.0f,
			1.0f,
			1.0f
		);

		rect->SetObjectSpeed(100.0f);
		rect->SetObjectLife(CharacterLife);
		rect->SetObjectType(Type::My_OBJECT_CHARACTER);
		rect->SetObjectLifeTime(1000);
		rect->SetCharacterTag(m_myCharTag);
		rect->SetObjectLevel(m_objLevel.Level_Character);
		rect->SetObjectOriginalLife(CharacterLife);

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
		30
	);
	//rect->SetObjectDirection
	//(
	//	(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
	//	(1 - 2 * (rand() % 2)) * (rand() % 100 / 100.0f),
	//	1.0f
	//);
	rect->SetObjectDirection
	(
		1.0f,
		-1.0f,
		1.0f
	);

	rect->SetObjectSpeed(100.0f);
	rect->SetObjectLife(CharacterLife);
	rect->SetObjectType(Type::Enemy_OBJECT_CHARACTER);
	rect->SetObjectLifeTime(1000);
	rect->SetCharacterTag(m_enyCharTag);
	rect->SetObjectLevel(m_objLevel.Level_Character);
	rect->SetObjectOriginalLife(CharacterLife);

	m_topVec.push_back(rect);
}

void CSceneMgr::CreateMyAirCharacter()
{
	//�Ʊ� ���� ĳ���� ����
	m_myAirCharTag += 1;

	CRectangle * rect;
	rect = new CRectangle
	(
		rand() % 400 - 200, rand() % 250 + 200, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		30
	);

	rect->SetObjectDirection
	(
		1.0f,
		1.0f,
		1.0f
	);

	rect->SetObjectSpeed(150.0f);
	rect->SetObjectLife(AirCharacterLife);
	rect->SetObjectType(Type::MY_OBJECT_AIR_CHARACTER);
	rect->SetObjectLifeTime(1000);
	rect->SetCharacterTag(m_myAirCharTag);
	rect->SetObjectLevel(m_objLevel.Level_Character);
	rect->SetObjectOriginalLife(AirCharacterLife);

	m_obj->SetCanCreateMyCharacter(false);

	m_rectVec.push_back(rect);
}

void CSceneMgr::Update(float elapsedTime)
{
	int temp, temp_other;

	//--------------------------------------------------------------------------------- 
	//�� ĳ����, ��� ĳ����, ���� �ֱ� ����

	//m_buildingTime += (elapsedTime / 1000.0f);
	m_weather->Update(elapsedTime);

	m_enyCharTime += (elapsedTime / 1000.0f);
	m_myAirCharTime += (elapsedTime / 1000.0f);

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

	//if (m_myAirCharTime >= MyAirCharacterCoolTime)
	//{
	//	this->CreateMyAirCharacter();
	//	m_myAirCharTime = 0.0f;
	//}
	
	//---------------------------------------------------------------------------------
	// ĳ���� ���� �� ȭ���� �ֱ� ����

	float compDis = 100000.0f;
	int t_bCnt = 0, t_where = -1;
	bool t_flag = false;
	int compVal = 1000000;

	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_CHARACTER)
		{
			for (int k = 0; k < m_topVec.size(); ++k)
			{
				if (m_topVec[k]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
				{
					++t_bCnt;
					if (compDis != GetLength(*m_rectVec[i], *m_topVec[k]) && GetLength(*m_rectVec[i], *m_topVec[k]) <= compDis)
						t_flag = true;
					else
						t_flag = false;

					if (t_flag)
						t_where += 1;

					compDis = min(compDis, GetLength(*m_rectVec[i], *m_topVec[k]));
				}
				else break;
			}

			if (t_bCnt > 0)
			{
				float n_x = m_topVec[t_where]->GetObjectPosX() - m_rectVec[i]->GetObjectPosX();
				float n_y = m_topVec[t_where]->GetObjectPosY() - m_rectVec[i]->GetObjectPosY();
				float n_len = GetLength(*m_rectVec[i], *m_topVec[t_where]);

				float ret_x = n_x / n_len;
				float ret_y = n_y / n_len;

				m_rectVec[i]->SetObjectDirection
				(
					ret_x,
					ret_y,
					1.0f
				);
			}
		}

		compDis = 100000.0f;
		t_bCnt = 0, t_where = -1;
		t_flag = false;
		compVal = 1000000;

		if (m_rectVec[i]->GetObjectType() == Type::MY_OBJECT_AIR_CHARACTER)
		{
			for (int i = 0; i < m_topVec.size(); ++i)
			{
				if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
				{
					++t_bCnt;
					if (compVal != m_topVec[i]->GetObjectLife() && m_topVec[i]->GetObjectLife() <= compVal)
						t_flag = true;
					else
						t_flag = false;

					if (t_flag)
						t_where += 1;

					compVal = min(m_topVec[i]->GetObjectLife(), compVal);

					//t_store = m_rectVec[i];
				}
				else break;
			}

			if (t_bCnt > 0)
			{
				float n_x = m_topVec[t_where]->GetObjectPosX() - m_rectVec[i]->GetObjectPosX();
				float n_y = m_topVec[t_where]->GetObjectPosY() - m_rectVec[i]->GetObjectPosY();
				float n_len = GetLength(*m_rectVec[i], *m_topVec[t_where]);

				float ret_x = n_x / n_len;
				float ret_y = n_y / n_len;

				m_rectVec[i]->SetObjectDirection
				(
					ret_x,
					ret_y,
					1.0f
				);
			}
		}

		t_bCnt = 0, compVal = 1000000, t_where = -1;
		t_flag = false;

		if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_CHARACTER)
		{
			m_rectVec[i]->SetCharParticleTime(elapsedTime);
			m_rectVec[i]->SetCharParticleSeta();
		}

		if (m_rectVec[i]->GetObjectType() == Type::MY_OBJECT_AIR_CHARACTER)
		{
			m_rectVec[i]->SetCharParticleTime(elapsedTime);
			m_rectVec[i]->SetCharParticleSeta();
		}
			
		m_rectVec[i]->Update(elapsedTime);

		if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_CHARACTER)
		{
			if (m_rectVec[i]->SetObjectArrowCoolTime(elapsedTime))
				this->CreateArrow(m_rectVec[i]);
		
			if (m_rectVec[i]->IsCanCharAniToNext())					//ĳ���� �ִϸ��̼� ���� �ֱ� - 30�����Ӹ��� 1���� �ִϸ��̼�
				m_rectVec[i]->SetCharAniMove(m_rectVec[i]->GetObjectType());
		}
		else if (m_rectVec[i]->GetObjectType() == Type::MY_OBJECT_AIR_CHARACTER && m_myAirCharTime != 0.0f)
		{
			if (m_rectVec[i]->IsCanCharAniToNext())					//ĳ���� �ִϸ��̼� ���� �ֱ� - 30�����Ӹ��� 1���� �ִϸ��̼�
				m_rectVec[i]->SetCharAniMove(m_rectVec[i]->GetObjectType());
		}
		else if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BULLET)
		{
			//0���� �ʱ�ȭ�� �ҷ��� Ÿ�̸ӿ� �ð����� ���Ѵ�.
			m_rectVec[i]->SetBulletObjectTime(elapsedTime);
		}
		else if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BUILDING)
		{
			if (m_rectVec[i]->IsCanCreateBulletTime(elapsedTime))
				this->CreateBullet
				(
					m_rectVec[i]->GetObjectPosXYZ(), m_rectVec[i]->GetObjectColorRGBA(), Type::My_OBJECT_BULLET
				);
		}
	}

	//---------------------------------------------------------------------------------------

	t_bCnt = 0, t_where = -1;
	t_flag = false;
	compVal = 1000000;

	for (int i = 0; i < m_topVec.size(); ++i)
	{
	     if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
		 {
			for (int i = 0; i < m_rectVec.size(); ++i)
			{
				if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BUILDING)
				{
					++t_bCnt;
					if (compVal != m_rectVec[i]->GetObjectLife() && m_rectVec[i]->GetObjectLife() <= compVal)
						t_flag = true;
					else
						t_flag = false;

					if (t_flag)
						t_where += 1;

					compVal = min(m_rectVec[i]->GetObjectLife(), compVal);

					//t_store = m_rectVec[i];
				}
				else break;
			}

			if (t_bCnt > 0)
			{
				float n_x = m_rectVec[t_where]->GetObjectPosX() - m_topVec[i]->GetObjectPosX();
				float n_y = m_rectVec[t_where]->GetObjectPosY() - m_topVec[i]->GetObjectPosY();
				float n_len = GetLength(*m_topVec[i], *m_rectVec[t_where]);

				float ret_x = n_x / n_len;
				float ret_y = n_y / n_len;

				m_topVec[i]->SetObjectDirection
				(
					ret_x,
					ret_y,
					1.0f
				);
			}
		}

		t_bCnt = 0, compVal = 1000000, t_where = -1;
		t_flag = false;

		if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
		{
			m_topVec[i]->SetCharParticleTime(elapsedTime);
			m_topVec[i]->SetCharParticleSeta();
		}

		m_topVec[i]->Update(elapsedTime);

		if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER && m_enyCharTime != 0.0f)
		{
			if (m_topVec[i]->SetObjectArrowCoolTime(elapsedTime))
				this->CreateArrow(m_topVec[i]);
			
			if (m_topVec[i]->IsCanCharAniToNext())
				m_topVec[i]->SetCharAniMove(m_topVec[i]->GetObjectType());
		}
		else if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_BULLET)
		{
			m_topVec[i]->SetBulletObjectTime(elapsedTime);
		}
		else if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
		{
			if (m_topVec[i]->IsCanCreateBulletTime(elapsedTime))
				this->CreateBullet
				(
					m_topVec[i]->GetObjectPosXYZ(), m_topVec[i]->GetObjectColorRGBA(), Type::Enemy_OBJECT_BULLET
				);
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
						m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_ARROW	||
						m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BULLET))
				{
					m_rectVec[i]->SetObjectLife(temp);
					m_topVec[j]->SetObjectLife(temp_other);

					//cout << "��" << i << "��° ������ ü�� = " <<  m_rectVec[i]->GetObjectLife() << endl;
				}

				//���� �ҷ��� ����� ����, ĳ���� �浹
				if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BULLET
					&& (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER ||
						m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BUILDING))
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

				//if (m_rectVec[i]->GetObjectType() == Type::MY_OBJECT_AIR_CHARACTER
				//	&& (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER ||
				//		m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BUILDING))
				//{
				//	if (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
				//	{
				//		m_rectVec[i]->SetObjectLife(temp);
				//		m_topVec[j]->SetObjectLife(temp_other);
				//	}
				//
				//	if (m_topVec[j]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
				//	{
				//		m_topVec[j]->SetObjectLife(temp_other);
				//	}
				//}
				
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
			//��ƼŬ ����
			//if ((*iter)->GetObjectType() == Type::My_OBJECT_BULLET)
			//{
			//	if ((*iter)->GetBulletObjectTime() >= MAX_PARTICLE_LIVE_TIME)
			//		iter = m_rectVec.erase(iter);
			//}

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
			//��ƼŬ ����
			//if ((*iter)->GetObjectType() == Type::My_OBJECT_BULLET)
			//{
			//	if ((*iter)->GetBulletObjectTime() >= MAX_PARTICLE_LIVE_TIME)
			//		iter = m_topVec.erase(iter);
			//}

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
	//float temp = 0.0f;

	AniType anitype;

	// ����̹���
	m_render->DrawTexturedRect
	(
		0, 0,
		1,
		1000, 
		1.0f, 1.0f, 1.0f, 1.0f, 
		m_texBackground,
		0.4f
	);

	DrawSceneText(-120.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, 1.0f, 1.0f, 1.0f, "Created by monoTree");

	m_weather->Draw(m_render);

	for (int i = 0; i < m_rectVec.size(); ++i)
	{
		if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BUILDING)
		{
			float LeftHp = static_cast<float>(m_rectVec[i]->GetObjectLife()) / static_cast<float>(m_rectVec[i]->GetObjectOriginalLife());
			
			m_render->DrawTexturedRect
			(
				m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), 
				m_rectVec[i]->GetObjectPosZ(),
				m_rectVec[i]->GetSquareSize(), 1.0f, 1.0f, 1.0f, 1.0f, m_texMyBuilding,
				m_rectVec[i]->GetObjectLevel()
			);
			
			m_render->DrawSolidRectGauge
			(
				m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY() + 50, m_rectVec[i]->GetObjectPosZ(),
				100, 10, 
				0.0f, 0.0f, 1.0f, 1.0f, 
				static_cast<float>(m_rectVec[i]->GetObjectLife()) / static_cast<float>(m_rectVec[i]->GetObjectOriginalLife()),
				m_rectVec[i]->GetObjectLevel()
			);
			
			//if (static_cast<int>(LeftHp) % 20 == 0)
			//{
				if (m_tswing == 0)
				{
					m_render->SetSceneTransform(20.0f, 5.0f, 1.0f, 1.0f);
					m_tswing = 1;
				}
				
				if (m_tswing == 1)
				{
					m_render->SetSceneTransform(20.0f, 10.0f, 1.0f, 1.0f);
					m_tswing = 0;
				}
			//}
			
		}
		else
		{
			if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_BULLET)
			{
				m_render->DrawParticle
				(
					m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
					8.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					-m_rectVec[i]->GetObjectDirection().x, -m_rectVec[i]->GetObjectDirection().y, 
					m_texParticle,
					m_rectVec[i]->GetBulletObjectTime(), m_rectVec[i]->GetObjectLevel()
				);
			}
			else if (m_rectVec[i]->GetObjectType() == Type::My_OBJECT_CHARACTER)
			{
				m_render->DrawTexturedRectSeq
				(
					m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
					m_rectVec[i]->GetSquareSize(), 
					1.0f, 1.0f, 1.0f, 0.5f, 
					m_texAnimationSp, 
					m_rectVec[i]->GetCharacterAniMove().w_move, m_rectVec[i]->GetCharacterAniMove().h_move, 
					anitype.MyChar.Max_Width, anitype.MyChar.Max_Height, 
					m_rectVec[i]->GetObjectLevel()
				);

				m_render->DrawSolidRectGauge
				(
					m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY() + 20, m_rectVec[i]->GetObjectPosZ(),
					25, 5, 
					0.0f, 0.0f, 1.0f, 1.0f, 
					static_cast<float>(m_rectVec[i]->GetObjectLife()) / static_cast<float>(m_rectVec[i]->GetObjectOriginalLife()),
					m_rectVec[i]->GetObjectLevel()
				);

				m_render->DrawParticle
				(
					m_rectVec[i]->GetObjectPosX() + cos(m_rectVec[i]->GetCharParticleSeta()) * 20, m_rectVec[i]->GetObjectPosY() + sin(m_rectVec[i]->GetCharParticleSeta()) * 20, m_rectVec[i]->GetObjectPosZ(),
					10.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					cos(m_rectVec[i]->GetCharParticleSeta()) / 15, sin(m_rectVec[i]->GetCharParticleSeta()) / 15,
					m_texMyCharParticle,
					m_rectVec[i]->GetCharParticleTime(), m_rectVec[i]->GetObjectLevel()
				);

			}
			else if (m_rectVec[i]->GetObjectType() == Type::MY_OBJECT_AIR_CHARACTER)
			{
				//m_render->DrawTexturedRectSeq
				//(
				//	0, 0, m_rectVec[i]->GetObjectPosZ(),
				//	m_rectVec[i]->GetSquareSize(),
				//	1.0f, 1.0f, 1.0f, 0.5f,
				//	m_texAirAnimationSp,
				//	m_rectVec[i]->GetCharacterAniMove().w_move, m_rectVec[i]->GetCharacterAniMove().h_move,
				//	anitype.MyAirChar.Max_Width, anitype.MyAirChar.Max_Height,
				//	m_rectVec[i]->GetObjectLevel()
				//);


				//m_render->DrawTexturedRectSeq
				//(
				//	m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
				//	m_rectVec[i]->GetSquareSize(),
				//	1.0f, 1.0f, 1.0f, 0.5f,
				//	m_texAirAnimationSp,
				//	m_rectVec[i]->GetCharacterAniMove().w_move, m_rectVec[i]->GetCharacterAniMove().h_move,
				//	anitype.MyAirChar.Max_Width, anitype.MyAirChar.Max_Height,
				//	m_rectVec[i]->GetObjectLevel()
				//);

				//m_render->DrawSolidRectGauge
				//(
				//	m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY() + 20, m_rectVec[i]->GetObjectPosZ(),
				//	25, 5,
				//	0.0f, 0.0f, 1.0f, 1.0f,
				//	static_cast<float>(m_rectVec[i]->GetObjectLife()) / static_cast<float>(m_rectVec[i]->GetObjectOriginalLife()),
				//	m_rectVec[i]->GetObjectLevel()
				//);
				//
				//m_render->DrawParticle
				//(
				//	m_rectVec[i]->GetObjectPosX() + cos(m_rectVec[i]->GetCharParticleSeta()) * 20, m_rectVec[i]->GetObjectPosY() + sin(m_rectVec[i]->GetCharParticleSeta()) * 20, m_rectVec[i]->GetObjectPosZ(),
				//	10.0f,
				//	1.0f, 1.0f, 1.0f, 1.0f,
				//	cos(m_rectVec[i]->GetCharParticleSeta()) / 15, sin(m_rectVec[i]->GetCharParticleSeta()) / 15,
				//	m_texMyAirCharParticle,
				//	m_rectVec[i]->GetCharParticleTime(), m_rectVec[i]->GetObjectLevel()
				//);

			}
			else
			{
				m_render->DrawSolidRect
				(
					m_rectVec[i]->GetObjectPosX(), m_rectVec[i]->GetObjectPosY(), m_rectVec[i]->GetObjectPosZ(),
					m_rectVec[i]->GetSquareSize(),
					m_rectVec[i]->GetObjectColorRGBA().r, m_rectVec[i]->GetObjectColorRGBA().g,
					m_rectVec[i]->GetObjectColorRGBA().b, m_rectVec[i]->GetObjectColorRGBA().a,
					m_rectVec[i]->GetObjectLevel()
				);
			}
		}
	}

	for (int i = 0; i < m_topVec.size(); ++i)
	{
		if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_BUILDING)
		{
			float LeftHp = static_cast<float>(m_topVec[i]->GetObjectLife()) / static_cast<float>(m_topVec[i]->GetObjectOriginalLife());
			
			m_render->DrawTexturedRect
			(
				m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY(), 
				m_topVec[i]->GetObjectPosZ(),
				m_topVec[i]->GetSquareSize(), 1.0f, 1.0f, 1.0f, 1.0f, m_texEnemyBuilding,
				m_topVec[i]->GetObjectLevel()
			);
			
			m_render->DrawSolidRectGauge
			(
				m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY() + 50, m_topVec[i]->GetObjectPosZ(),
				100, 10,
				1.0f, 0.0f, 0.0f, 1.0f,
				LeftHp,
				m_topVec[i]->GetObjectLevel()
			);
			
			if (static_cast<int>(LeftHp) % 20 == 0)
				m_render->SetSceneTransform(10.0f, 10.0f, 1.0f, 1.0f);
		}
		else
		{
			if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_BULLET)
			{
				m_render->DrawParticle
				(
					m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY(), m_topVec[i]->GetObjectPosZ(),
					8.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					-m_topVec[i]->GetObjectDirection().x, -m_topVec[i]->GetObjectDirection().y,
					m_texEnyParticle,
					m_topVec[i]->GetBulletObjectTime(), m_topVec[i]->GetObjectLevel()
				);
			}
			else if (m_topVec[i]->GetObjectType() == Type::Enemy_OBJECT_CHARACTER)
			{
				m_render->DrawTexturedRectSeq
				(
					m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY(), m_topVec[i]->GetObjectPosZ(),
					m_topVec[i]->GetSquareSize(), 
					1.0f, 1.0f, 1.0f, 0.5f, 
					m_texEnyAnimationSp, 
					m_topVec[i]->GetCharacterAniMove().w_move, m_topVec[i]->GetCharacterAniMove().h_move, 
					anitype.EnyChar.Max_Width, anitype.EnyChar.Max_Height, 
					m_topVec[i]->GetObjectLevel()
				);

				m_render->DrawSolidRectGauge
				(
					m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY() + 20, m_topVec[i]->GetObjectPosZ(),
					25, 5, 
					1.0f, 0.0f, 0.0f, 1.0f, 
					static_cast<float>(m_topVec[i]->GetObjectLife()) / static_cast<float>(m_topVec[i]->GetObjectOriginalLife()),
					m_topVec[i]->GetObjectLevel()
				);

				m_render->DrawParticle
				(
					m_topVec[i]->GetObjectPosX() + cos(m_topVec[i]->GetCharParticleSeta()) * 20, m_topVec[i]->GetObjectPosY() + sin(m_topVec[i]->GetCharParticleSeta()) * 20, m_topVec[i]->GetObjectPosZ(),
					10.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					cos(m_topVec[i]->GetCharParticleSeta()) / 15, sin(m_topVec[i]->GetCharParticleSeta()) / 15,
					m_texEnemyCharParticle,
					m_topVec[i]->GetCharParticleTime(), m_topVec[i]->GetObjectLevel()
				);
			}
			else
			{
				m_render->DrawSolidRect
				(
					m_topVec[i]->GetObjectPosX(), m_topVec[i]->GetObjectPosY(), m_topVec[i]->GetObjectPosZ(),
					m_topVec[i]->GetSquareSize(),
					m_topVec[i]->GetObjectColorRGBA().r, m_topVec[i]->GetObjectColorRGBA().g,
					m_topVec[i]->GetObjectColorRGBA().b, m_topVec[i]->GetObjectColorRGBA().a,
					m_topVec[i]->GetObjectLevel()
				);
			}

		}
	}
}


void CSceneMgr::DrawSceneText(float posX, float posY, void *font, float r, float g, float b, char* text)
{
	m_render->DrawTextW(posX, posY, font, r, g, b, text);
}

float CSceneMgr::GetLength(const CRectangle& v1, const CRectangle& v2)
{
	float t_x = (v2.GetObjectPosX() - v1.GetObjectPosX()) * (v2.GetObjectPosX() - v1.GetObjectPosX());
	float t_y = (v2.GetObjectPosY() - v1.GetObjectPosY()) * (v2.GetObjectPosY() - v1.GetObjectPosY());

	return sqrt(t_y + t_x);
}

CSceneMgr::~CSceneMgr()
{

}

