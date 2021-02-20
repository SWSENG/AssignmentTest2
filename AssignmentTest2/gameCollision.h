#pragma once

struct Box {
	// Possition of top-left corner
	float x, y;

	// Dimensions
	float width;
	float height;

	// Velocity
	float vx, vy;
};

enum CollisionSide
{
	Left,
	Top,
	Right,
	Bottom,
	Unknown
};

struct CollisionResult
{
	bool isCollide;
	float entryTime;
	int sideX, sideY;
	CollisionSide sideCollided;
	CollisionResult() { isCollide = false; entryTime = 1.0f; sideX = sideY = 0; sideCollided = CollisionSide::Unknown; }
};

class Collision
{
private:
	static Collision* instance;
public:
	static Collision* getInstance();

	// Return a float (from 0.0 to 1.0) that prepresents the time when the collision happens.
	// 0.0 is the beginning time. 1.0 is the ending time.
	// For example:
	//		If the function returns 1.0, it means there is no collision.
	//		If the functions returns 0.5, it means collision happens in the middle of the on-going path.
	CollisionResult SweptAABB(Box b1, Box b2, float& normalX, float& normalY, float deltaTime);

	Box GetSweptBroadphaseBox(Box b, float deltaTime);

	bool AABBCheck(Box b1, Box b2);

	bool willCollide(Box box, Box block, float& returnCollisionTime);

	// Return true if two objects are colliding with each other. Return false if otherwise.
	bool isColliding(const Box& object, const Box& other)
	{
		float left = other.x - (object.x + object.width);
		float top = (other.y + other.height) - object.y;
		float right = (other.x + other.width) - object.x;
		float bottom = other.y - (object.y + object.height);

		return !(left > 0 || right < 0 || top < 0 || bottom > 0);
	}
	bool isCollisionEnemy(const Box& object, const Box& other)
	{
		float L, T, R, B;
		L = (object.x + (object.width / 2)) - (other.x - (other.width / 2));
		R = (object.x - (object.width / 2)) - (other.x + (other.width / 2));
		B = (object.y + (object.height / 2)) - (other.y - (other.height / 2));
		T = (object.y - (object.height / 2)) - (other.y + (other.height / 2));

		if (L >= 0 && R <= 0 && B >= 0 && T <= 0)
			return true;
		else
			return false;
	}

	bool isColliding(const RECT& object, const RECT& other)
	{

	}
};