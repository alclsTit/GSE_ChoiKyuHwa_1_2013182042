/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Rectangle.h"
#include "Renderer.h"
#include "SceneMgr.h"

//¾ø¾î¾ßµÊ
Renderer *g_Renderer = NULL;

CSceneMgr *CMgr = NULL;

bool IsLButtonDown = false;

DWORD g_PrevTime;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	DWORD curTime = timeGetTime();
	DWORD elapsedTime = curTime - g_PrevTime;
	g_PrevTime = curTime;

	CMgr->Update((float)elapsedTime);

	CMgr->Draw();

	glutSwapBuffers();
}

void InitRectPos()
{

}


void Idle(void)
{
	RenderScene();

}

//button
//GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON,GLUT_RIGHT_BUTTON
//state
//GLUT_UP, GLUT_DOWN
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		IsLButtonDown = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (IsLButtonDown)
		{
			//g_Rect.SetPosition((float)(x-250), (float)(-y + 500 - 250), 0.0f);
			CMgr->CreateMyCharacter(static_cast<float>(x),static_cast<float>(y));		
			
		}

		IsLButtonDown = false;
	}

}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
#pragma region [GluInit]

	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
#pragma endregion
	
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	//Initialize Renderer
	CMgr = new CSceneMgr();
	g_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

#pragma region [LoopFunc]

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	

#pragma endregion

	g_PrevTime = timeGetTime();

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

