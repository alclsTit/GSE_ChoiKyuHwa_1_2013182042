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

#define BuildingCoolTime 10
#define ArrowCoolTime 3
#define MyCharacterCoolTime 7
#define EnyCharacterCoolTime 5

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
};

using namespace std;
