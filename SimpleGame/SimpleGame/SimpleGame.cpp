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

Renderer *g_Renderer = NULL;
CRectangle rect;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	// 사이즈는 픽셀단위로 맞춘다
	g_Renderer->DrawSolidRect(
		rect.GetPosition().GetPositionX(),rect.GetPosition().GetPositionY(),
		rect.GetPosition().GetPositionZ(), rect.GetSquareLength(),
		rect.GetRectColor().r, rect.GetRectColor().g,
		rect.GetRectColor().b, rect.GetRectColor().a);

	glutSwapBuffers();
}

void InitRectPos()
{
	// Initialize RectInfo
	rect.SetPosition(0, 100, 0);
	rect.SetRectColor(1.0f, 0.0f, 0.0f, 0.0f);
	rect.SetSquareLength(80);
}

void Idle(void)
{
	rect.MovePosPerUpdate(0.01f, 1);
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
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

	InitRectPos();

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

