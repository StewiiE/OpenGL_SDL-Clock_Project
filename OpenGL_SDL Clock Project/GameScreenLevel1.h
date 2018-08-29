#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "object3DS.h"
#include "Pyramid.h"
#include "camera.h"
#include <sstream>
#include <string.h>

using namespace std;

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);

	void		SetLight();
	void		SetMaterial();

	void		ReadOBJ();

//--------------------------------------------------------------------------------------------------
private:
	
	float mCurrentTime;
	Pyramid* pyramid;
	float pyramidRotation;

	Object3DS* m_p3DSModel;
	float octopusRotation;
	Object3DS* m_ClockNumbers;
	Object3DS* m_ClockMinuteHand;
	Object3DS* m_ClockHourHand;
	float clockRotationMinute;
	float clockRotationHour;

	stringstream ss;
	stringstream controlsText;
	stringstream clockControlsText;
	int health;
	int score;
	float framesPerSecond;

	Camera* camera;
};


#endif //_GAMESCREENLEVEL1_H