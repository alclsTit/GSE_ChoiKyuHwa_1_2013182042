#include "stdafx.h"
#include <cmath>
#include "CWeatherEffect.h"


CWeatherEffect::CWeatherEffect(char *texPath, Renderer* m_render)
{
	m_weatherTexID = m_render->CreatePngTexture(texPath);
}

void CWeatherEffect::Draw(Renderer* m_render)
{
	m_render->DrawParticleClimate
	(
		0.0f, 0.0f, 0.0f,
		5.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, m_weatherTexID,
		m_elapsedTime, 0.0f
	);
}

void CWeatherEffect::Update(float elapsedTime)
{
	m_elapsedTime += (elapsedTime / 1000.0f);

	// ���� �Ȱ����ְ� ���⸸ ���ص� ����ǥ���� �޶���
	m_angle += (m_angle + 1) % 360;

	//x��
	m_dir.dirX = m_rad * cos(m_angle);

	//y��
	m_dir.dirY = m_rad * sin(m_angle);
}


CWeatherEffect::~CWeatherEffect()
{
}
