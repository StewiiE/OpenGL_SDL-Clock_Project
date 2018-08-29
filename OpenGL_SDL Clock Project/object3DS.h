#pragma once

#ifndef _OBJECT3DS_H_ 
#define _OBJECT3DS_H_ 

#include "Commons.h" 
#include <string> 
using std::string;

class Object3DS
{
public:
	Object3DS(Vector3D startPosition, string modelFileName);
	~Object3DS() {}

	void Update(float deltaTime);
	void Render();

	//Load 3ds file 
	void LoadModel();

	//Load texture for this model. 
	void LoadTexture();

private:
	Vector3D mPosition;
	float octopusRotation;
	float clockRotation;

	char fileName[20];
	char textureName[20];

	obj_type object;
};
#endif //_OBJECT3DS_H_
