#pragma once
#include "stdafx.h"
#include "Rectangle.h"
#include "ObjectCollision.h"
#include "Renderer.h"
#include "CreateSounds.h"
#include "CWeatherEffect.h"
#include <vector>
#include <random>

class CSceneMgr
{
private:
	vector<CRectangle*> m_rectVec;
	vector<CRectangle*> m_topVec;

	CObjectCollision *m_objColl{ nullptr };
	CRectangle *m_building{ nullptr };

	CRectangle *m_obj{ nullptr };

	CreateSounds *m_backBGM{ nullptr };

	CWeatherEffect *m_weather{ nullptr };

	bool m_flagOut{ false };

	float m_buildingTime{ 0.0f };
	float m_enyCharTime{ 0.0f };
	float m_myCharTime{ 0.0f };
	float m_myAirCharTime{ 0.0f };

	bool m_createMyChar{ false };
	bool m_cancCreChar{ true };

	int m_hpDownTerm{ 0 };
	int m_myCharTag{ 0 };
	int m_enyCharTag{ 0 };
	int m_myAirCharTag{ 0 };
	int m_t_seta{ 0 };

	Renderer *m_render{ nullptr };

	GLuint m_texEnemyBuilding;
	GLuint m_texMyBuilding;
	GLuint m_texBackground;

	GLuint m_texAnimationSp;
	GLuint m_texEnyAnimationSp;
	GLuint m_texAirAnimationSp;

	GLuint m_texParticle;
	GLuint m_texEnyParticle;
	GLuint m_texMyCharParticle;
	GLuint m_texEnemyCharParticle;
	GLuint m_texMyAirCharParticle;

	Level m_objLevel;
	
	int m_tswing{ 0 };
public:
	CSceneMgr();
	void CreateBuilding(vector<CRectangle*>& vec, Vec3f pos, Color color, 
		int size, int life, float lifeTime, Type type, char* imagePath);
	void CreateBullet(Vec3f createPos, Color color, Type type);
	void CreateArrow(CRectangle *rect);
	void CreateMyCharacter(float posX, float posY);
	void CreateEnemyCharacter();
	void Update(float elapsedTime);
	void Draw();
	int GetCurRectNum() const { return m_rectVec.size(); }

	void CreateMyAirCharacter();
	void DrawSceneText(float posX, float posY, void *font, float r, float g, float b, char* text);
	float GetLength(const CRectangle& v1, const CRectangle& v2);

	~CSceneMgr();

};

