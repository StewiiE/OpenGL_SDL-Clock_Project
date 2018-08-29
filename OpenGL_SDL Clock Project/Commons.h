#pragma once

//3DS Max Object type details.
#define MAX_VERTICES 15000
#define MAX_POLYGONS 15000

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width  = initialWidth;
		height = initialHeight;
	}
};

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3D(float initialX, float initialY, float initialZ)
	{
		x = initialX;
		y = initialY;
		z = initialZ;
	}

	Vector3D operator* (float scaler) 
	{
		return Vector3D(x * scaler, y * scaler, z * scaler);
	}

	Vector3D operator+ (const Vector3D& other) 
	{ 
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

	Vector3D operator+= (const Vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3D operator-= (const Vector3D& other)
	{ 
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
};

struct TexCoord
{
	float u;
	float v;
};

struct Vertex3D
{
	float x;
	float y;
	float z;
};

struct lighting
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
};

struct material
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
};


// The polygon (triangle), 3 numbers that aim 3 vertices 
struct Triangle
{
	int a;
	int b;
	int c;
};

// The object type 
typedef struct
{
	char name[20];
	int vertices_qty;
	int triangles_qty;
	Vertex3D vertex[MAX_VERTICES];
	Triangle triangle[MAX_POLYGONS];
	TexCoord texcoord[MAX_VERTICES];
	int id_texture;
} obj_type, *obj_type_ptr;