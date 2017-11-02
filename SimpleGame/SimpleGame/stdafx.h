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
#define WINDOW_HEIGHT 500

enum class Type {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW
};

using namespace std;
