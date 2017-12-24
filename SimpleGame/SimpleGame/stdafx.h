#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <cmath>
#include <chrono>
#include <iostream>
#include <Windows.h>

#define MAX_OBJECTS_COUNT 100000
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 800

#define BuildingCreateBulletCoolTime 3
#define ArrowCoolTime 2
#define MyCharacterCoolTime 2
#define EnyCharacterCoolTime 4
#define MyAirCharacterCoolTime 4

#define BulletLife 20
#define ArrowLife 10
#define CharacterLife 100
#define AirCharacterLife 50

#define MAX_ANI_FRAME_WIDTH 8
#define MAX_ANI_FRAME_HEIGHT 2

#define CHAR_MOVE_PER_FRAME 60

#define BUILDING_MAX_NUMBER 3

#define MAX_PARTICLE_LIVE_TIME 1.0

#define  GLUT_STROKE_ROMAN
#define  GLUT_STROKE_MONO_ROMAN
#define  GLUT_BITMAP_9_BY_15   
#define  GLUT_BITMAP_8_BY_13
#define  GLUT_BITMAP_TIMES_ROMAN_10
#define  GLUT_BITMAP_TIMES_ROMAN_24
#define  GLUT_BITMAP_HELVETICA_10
#define  GLUT_BITMAP_HELVETICA_12
#define  GLUT_BITMAP_HELVETICA_18


enum class Type 
{
	Enemy_OBJECT_BUILDING,
	Enemy_OBJECT_CHARACTER,
	Enemy_OBJECT_BULLET,
	Enemy_OBJECT_ARROW,
	My_OBJECT_BUILDING,
	My_OBJECT_CHARACTER,
	My_OBJECT_BULLET,
	My_OBJECT_ARROW,
	MY_OBJECT_AIR_CHARACTER
};

struct AniSprites
{
	int Max_Width;
	int Max_Height;
};

struct AniType
{
	AniSprites MyChar{ 8,2 };
	AniSprites EnyChar{ 3,3 };
	AniSprites MyAirChar{ 4,2 };
};

struct Level
{
	float Level_Building = 0.1;
	float Level_Character = 0.2;
	float Level_Bullet = 0.3;
	float Level_Arrow = 0.3;
};

using namespace std;
