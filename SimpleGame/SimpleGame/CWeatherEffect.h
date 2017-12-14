#pragma once
#include "Renderer.h"

struct Dir
{
	float dirX;
	float dirY;
};

class CWeatherEffect
{
private:
	int m_angle{ 0 };
	float m_rad{ 1.0f };
	float m_elapsedTime{ 0.0f };
	Dir m_dir{ 0.0f,0.0f };

	GLuint m_weatherTexID;
	Renderer *m_render;


public:
	CWeatherEffect(char *texPath, Renderer* m_render);
	void Draw(Renderer* m_render);
	void Update(float elapsedTime);
	~CWeatherEffect();
};

