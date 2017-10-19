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

Renderer *g_Renderer = NULL;
CRectangle g_Rect;
CSceneMgr *CMgr;
bool IsLButtonDown = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	CMgr->Draw();
	// Renderer Test
	// ������� �ȼ������� �����
	//g_Renderer->DrawSolidRect(
	//	g_Rect.GetPosition().GetPositionX(), g_Rect.GetPosition().GetPositionY(),
	//	g_Rect.GetPosition().GetPositionZ(), g_Rect.GetSquareLength(),
	//	g_Rect.GetRectColor().r, g_Rect.GetRectColor().g,
	//	g_Rect.GetRectColor().b, g_Rect.GetRectColor().a);

	glutSwapBuffers();
}

void InitRectPos()
{
	// Initialize RectInfo
	//g_Rect.SetPosition(200, 125, 0);
	//g_Rect.SetRectColor(1.0f, 0.0f, 0.0f, 0.0f);
	//g_Rect.SetSquareLength(80);
	
	CMgr->CreateRect();
}


void Idle(void)
{
	//auto past = chrono::system_clock::now();
	CMgr->Update();
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
			g_Rect.SetPosition((float)(x-250), (float)(-y + 500 - 250), 0.0f);
			CMgr->CreateRect();

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
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
#pragma endregion

	CMgr = new CSceneMgr();

	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
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

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

