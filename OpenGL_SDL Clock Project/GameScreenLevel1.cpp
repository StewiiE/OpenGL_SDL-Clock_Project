#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Texture.h"
#include "object3DS.h"
#include "camera.h"
#include "objLoader.h"
#include <iostream>

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//clear background colour.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	pyramid = new Pyramid();
	pyramidRotation = 30.0f;

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);
	Texture2D* texture = new Texture2D();
	texture->Load("Penguins.raw", 512, 512);

	glBindTexture(GL_TEXTURE_2D, texture->GetID());

	//set some paramaters so it renders correctly
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Octopus
	m_p3DSModel = new Object3DS(Vector3D(0.0f, 3.0f, 0.0f), "Octopus.3ds");
	octopusRotation = 30.0f;

	//Clock
	m_ClockNumbers = new Object3DS(Vector3D(0.0f, 8.0f, 0.0f), "ClockNumbers.3ds");
	m_ClockMinuteHand = new Object3DS(Vector3D(0.0f, -2.0f, 0.0f), "ClockMinuteHand.3ds");
	m_ClockHourHand = new Object3DS(Vector3D(0.0f, -2.0f, 0.0f), "ClockMinuteHand.3ds");
	clockRotationHour = 10.0f;
	clockRotationMinute = 10.0f;

//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	camera = new Camera();
	camera->GetInstance();

	health = 10;
	score = 30;
}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	

}

//--------------------------------------------------------------------------------------------------

//Tutorial - Primitives - Polygons
void Draw2DSquare()
{

/*glBegin(GL_POLYGON);
		glVertex3f(-0.5f,  0.0f, 0.0f);
		glVertex3f( 0.5f,  0.0f, 0.0f);
		glVertex3f( 0.5f, -1.0f, 0.0f);
		glVertex3f(-0.5f, -1.0f, 0.0f);
	glEnd(); */

}

void GameScreenLevel1::SetLight()
{
	lighting light =
	{
		{ 0.8f, 0.8f, 0.8f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	};
	// position of the light in homogeneous coordinates (x, y, z, w)
	// w should be 0 for directional lights, and 1 for spotlights
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void GameScreenLevel1::SetMaterial()
{
	material material =
	{
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}


void DrawTextured2DSquare()
{
	 /*glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glEnd(); */
}

void GameScreenLevel1::ReadOBJ()
{
	// Read our .obj file
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.
	bool res = loadOBJ("cube.obj", vertices, uvs, normals);
}

void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f,
		      0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);
			  */
//--------------------------------------------------------------------------------------------------
	/*Tutorial - Primitives - POINTS
	float pointSize = 0.5f;

	//Draw a line of points of increasing size
	for (float point = -4.0f; point < 5.0f; point += 0.5f)
	{
		//Set the point size.
		glPointSize(pointSize);

		//Draw the point.
		glBegin(GL_POINTS);
		glVertex3f(point, 0.0f, 0.0f);
		glEnd();

		//Increase the size of the point.
		pointSize += 0.7f;

		glColor3f(1.0f, 0.0f, 0.0f);
	} */
//--------------------------------------------------------------------------------------------------
	/*//Tutorial - Primitives - Lines
	float lineWidth = 0.5f;

	//Enable stippling.
	//glEnable(GL_LINE_STIPPLE);

	//Draw a series of lines of increasing width.
	for (float line = 0.0f; line < 7.0f; line += 0.5f)
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		//Set the line width.
		glLineWidth(lineWidth);

		glBegin(GL_LINES);
			glVertex3f(-0.5f, line - 3.0f, 0.0f);
			glVertex3f(-4.5f, line - 3.0f, 0.0f);
		glEnd();

		//Increase the line width for the next line.
		lineWidth += 1.0f;

	}

	//Reset the line width.
	lineWidth = 0.5f;

	//Enable stippling.
	glEnable(GL_LINE_STIPPLE);

	// 0xAAAA = 1010 1010 1010 1010
	short stipplePattern = 0xAAAA;

	//Set the stipple pattern.
	glLineStipple(2, stipplePattern);

	//Draw a series of lines of increasing width.
	for (float line = 0.0f; line < 7.0f; line += 0.5f)
	{
		glColor3f(0.0f, 1.0f, 0.0f);

		//Set the line width.
		glLineWidth(lineWidth);

		glBegin(GL_LINES);
		glVertex3f(5.5f, line - 3.0f, 0.0f);
		glVertex3f(1.0f, line - 3.0f, 0.0f);
		glEnd();

		//Increase the line width for the next line.
		lineWidth += 1.0f;

	}

	glDisable(GL_LINE_STIPPLE); */
//--------------------------------------------------------------------------------------------------

	//Tutorial - Primitives - Poloygons
	/*

	static float angle = 0.0f;

	//Default setting.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Draw FRONT faces as lines.
	glPolygonMode(GL_FRONT, GL_LINE);
	glPushMatrix();
		glTranslatef(-4.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		Draw2DSquare();
	glPopMatrix();

	//Reset to default.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Draw BACK face as points.
	glPolygonMode(GL_BACK, GL_POINT);
	glPushMatrix();
		glTranslatef(-2.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		Draw2DSquare();
	glPopMatrix();

	//Reset to default.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Draw both faces.
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		Draw2DSquare();
	glPopMatrix();

	//Draw BACK face as lines.
	glPolygonMode(GL_BACK, GL_LINES);
	glPushMatrix();
		glTranslatef(2.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		Draw2DSquare();
	glPopMatrix();

	//Draw FRONT and BACK face as lines.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glPushMatrix();
		glTranslatef(4.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		Draw2DSquare();
	glPopMatrix();

	//Reset to default.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Alter the angle to ensure rotation.
	angle += 0.2f;
	
//----------------------------------------------------------------------------------------------
*/

//--------------------------------------------------------------------------------------------------
/*
glColor3f(1.0f, 1.0f, 1.0f);
glPushMatrix();
	glScalef(5.0f, 5.0f, 0.0f);
	DrawTextured2DSquare();
glPopMatrix();
*/

	SetLight();
	SetMaterial();

	//Pyramid
	glPushMatrix();
	glRotatef(pyramidRotation, 1, 1, 1);
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(2.5f, 2.5f, 2.5f);
	pyramid->Draw();
	glPopMatrix();

	//Octopus
	glPushMatrix();
	glRotatef(octopusRotation, 0, 1, 0);
	m_p3DSModel->Render();

	//Clock numbers
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glScalef(0.3f, 0.3f, 0.3f);
	m_ClockNumbers->Render();

	//Clock minute hand
	glPushMatrix();
	glTranslatef(0.0f, 9.0f, 0.0f);
	glScalef(0.9f, 0.9f, 0.9f);
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glRotatef(clockRotationMinute, 0, 0, 1);
	m_ClockMinuteHand->Render();
	

	//Clock hour hand

	glTranslatef(0.0f, 9.0f, 0.0f);
	glScalef(0.9f, 0.9f, 0.9f);
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glRotatef(clockRotationHour, 0, 0, 1);
	m_ClockHourHand->Render();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	ss;
	OutputLine(5, 95, ss.str());
	controlsText;
	OutputLine(5, 93, controlsText.str());
	clockControlsText;
	OutputLine(5, 91, clockControlsText.str());
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

//	glPushMatrix();
//	ReadOBJ();
//	glPopMatrix();

	camera->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;

	pyramidRotation += 1.0;

	m_p3DSModel->Update(deltaTime);
	octopusRotation += 1.0;

	m_ClockNumbers->Update(deltaTime);
	m_ClockMinuteHand->Update(deltaTime);
	m_ClockHourHand->Update(deltaTime);

	camera->Update(deltaTime, e);

	framesPerSecond = 1 / deltaTime;
	ss.str("");
	ss.clear();
	ss << "Score:  " << score << " " << "Health: " << health << " "  << "FPS: " << framesPerSecond << endl;

	controlsText.str("");
	controlsText.clear();
	controlsText << "Move the camera with WASD and rotate with the ARROW KEYS" << endl;

	clockControlsText.str("");
	clockControlsText.clear();
	clockControlsText << "Move the clock hands with 'Q' and 'E'" << endl;

	//Event Handler.
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_e:
			clockRotationMinute += 3.0;
			clockRotationHour += 0.28;
			break;

		case SDLK_q:
			clockRotationMinute -= 3.0;
			clockRotationHour -= 0.28;
			break;

		default:
			break;
		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------

void GameScreen::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y);  // where to start drawing
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}