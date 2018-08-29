#include "camera.h"
#include "Constants.h"
#include <math.h>
#include "../gl/glut.h"

static Camera* instance = 0;
static float moveSpeed = 5.0f;
static float lookSpeed = 0.5f;


Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}

	return instance;
}

void Camera::Update(float deltaTime, SDL_Event e)
{
	// Forward Vector: Spherical coordinates to Cartesian coordinates
	// conversion(also known as the ‘look’ direction)
	forward = Vector3D(
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw));

	// Right vector
	right = Vector3D(
		sin(yaw - 3.14f / 2.0f),
		0,
		cos(yaw - 3.14f / 2.0f));

	// Up vector : perpendicular to both forward and right, calculate using
	// the cross product
	up = Vector3D((right.y*forward.z) - (right.z*forward.y),
		(right.z*forward.x) - (right.x*forward.z),
		(right.x*forward.y) - (right.y*forward.x));

	//Event Handler.
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			//move forwards
			movingForward = true;
			movingBackward = false;
			break;

		case SDLK_s:
			//add move backwards code using the forward vector
			movingBackward = true;
			movingForward = false;
			break;

		case SDLK_d:
			//add strafe right code using the right vector
			movingRight = true;
			movingLeft = false;
			break;

		case SDLK_a:
			//add strafe left code using the right vector
			movingRight = false;
			movingLeft = true;
			break;

		case SDLK_UP:
			//look up
			rotatingUp = true;
			rotatingDown = false;
			break;

		case SDLK_DOWN:
			//add look down code by adjusting the pitch
			rotatingDown = true;
			rotatingUp = false;
			break;

		case SDLK_LEFT:
			//add look left code by adjusting the yaw
			rotatingLeft = true;
			rotatingRight = false;
			break;

		case SDLK_RIGHT:
			//add look right code by adjusting the yaw
			rotatingRight = true;
			rotatingLeft = false;
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			movingForward = false;
			break;

		case SDLK_s:
			movingBackward = false;
			break;

		case SDLK_d:
			movingRight = false;
			break;

		case SDLK_a:
			movingLeft = false;
			break;

		case SDLK_UP:
			rotatingUp = false;
			break;

		case SDLK_DOWN:
			rotatingDown = false;
			break;

		case SDLK_LEFT:
			rotatingLeft = false;
			break;

		case SDLK_RIGHT:
			rotatingRight = false;
			break;
		}
	default:
		break;
	}


	if (movingForward == true)
	{
		position += (forward * moveSpeed) * deltaTime;
	}
	if (movingBackward == true)
	{
		position -= (forward * moveSpeed) * deltaTime;
	}
	if (movingRight == true)
	{
		position += (right * moveSpeed) * deltaTime;
	}
	if (movingLeft == true)
	{
		position -= (right * moveSpeed) * deltaTime;
	}
	if (rotatingUp == true)
	{
		pitch += lookSpeed * deltaTime;
	}
	if (rotatingDown == true)
	{
		pitch -= lookSpeed * deltaTime;
	}
	if (rotatingRight == true)
	{
		yaw -= lookSpeed * deltaTime;
	}
	if (rotatingLeft == true)
	{
		yaw += lookSpeed * deltaTime;
	}
}
void Camera::Render()
{
	Vector3D lookatPos = position + forward; // make sure we're always looking at a point infront of the camera
		glLoadIdentity();
		gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y, lookatPos.z, up.x, up.y, up.z);
}