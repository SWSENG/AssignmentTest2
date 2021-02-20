#include "gameCollision.h"
#include <limits>
#include <minwindef.h>
#include <d3dx9.h>

Collision* Collision::instance = nullptr;
Collision* Collision::getInstance()
{
	if (instance)
	{
		return instance;
	}
	else
	{
		instance = new Collision();
		return instance;
	}
}


CollisionResult Collision::SweptAABB(Box b1, Box b2, float& normalX, float& normalY, float deltaTime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	CollisionResult result;
	result.isCollide = false;
	result.entryTime = 1.0f;
	result.sideX = result.sideY = 0;
	result.sideCollided = CollisionSide::Unknown;

	Box broadphaseBox = GetSweptBroadphaseBox(b1, deltaTime);
	if (!AABBCheck(broadphaseBox, b2))
	{
		return result;
	}

	// Find the distance of two objects between near and far edges.
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.width);
		xInvExit = (b2.x + b2.width) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.width) - b1.x;
		xInvExit = b2.x - (b1.x + b1.width);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.height);
		yInvExit = (b2.y + b2.height) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.height) - b1.y;
		yInvExit = b2.y - (b1.y + b1.height);
	}

	// Find time of collision and time of leaving for each axis.
	// (If statement is to prevent divide by zero.)
	// Time to enter collision.
	float xEntry, yEntry;
	// Time to exit collision.
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// Find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// If there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		return result;
	}
	else // If there was a collision
	{
		result.isCollide = true;
		result.entryTime = entryTime;

		// Calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalX = 1.0f;
				normalY = 0.0f;
				result.sideX = 1;
				result.sideY = 0;
				result.sideCollided = CollisionSide::Right;
			}
			else
			{
				normalX = -1.0f;
				normalY = 0.0f;
				result.sideX = -1;
				result.sideY = 0;
				result.sideCollided = CollisionSide::Left;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalX = 0.0f;
				normalY = 1.0f;
				result.sideX = 0;
				result.sideY = 1;
				result.sideCollided = CollisionSide::Top;
			}
			else
			{
				normalX = 0.0f;
				normalY = -1.0f;
				result.sideX = 0;
				result.sideY = -1;
				result.sideCollided = CollisionSide::Bottom;
			}
		}
		return result;
	}

	return result;
}

Box Collision::GetSweptBroadphaseBox(Box b, float deltaTime)
{
	D3DXVECTOR2 velocity = D3DXVECTOR2(b.vx * deltaTime, b.vy * deltaTime);
	Box broadphaseBox;

	//broadphaseBox.x = velocity.x > 0 ? b.x : b.x + b.vx * deltaTime;
	//broadphaseBox.y = velocity.y > 0 ? b.y : b.y + b.vy * deltaTime;
	//broadphaseBox.width = velocity.x > 0 ? b.vx * deltaTime + b.width : b.width - b.vx * deltaTime;
	//broadphaseBox.height = velocity.y > 0 ? b.vy * deltaTime + b.height : b.height - b.vy* deltaTime;
	broadphaseBox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphaseBox.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphaseBox.width = b.vx > 0 ? b.vx + b.width : b.width - b.vx;
	broadphaseBox.height = b.vy > 0 ? b.vy + b.height : b.height - b.vy;
	return broadphaseBox;
}

bool Collision::AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.width < b2.x ||
		b1.x > b2.x + b2.width ||
		b1.y + b1.height < b2.y ||
		b1.y > b2.y + b2.height);
}

bool Collision::willCollide(Box box, Box block, float& returnCollisionTime)
{
	//Box broadphaseBox = GetSweptBroadphaseBox(box);
	//if (AABBCheck(broadphaseBox, block))
	//{
	//	float normalX, normalY;
	//	float collisionTime = SweptAABB(box, block, normalX, normalY);
	//	box.x += box.vx * collisionTime;
	//	box.y += box.vy * collisionTime;

	//	if (collisionTime < 1.0f)
	//	{
	//		returnCollisionTime = collisionTime;
	//		return true;
	//	}
	//}
	return false;
}