//#include"collision.h"
//#include<iostream>
//#include<string>
//using namespace std;
//
//collision::collision()
//{
//	line = NULL;
//}
//
//collision::~collision()
//{
//	
//}
//
//bool collision::checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2)
//{
//	rect1.right = pos1.x + rect1.right - rect1.left;
//	rect1.left = pos1.x;
//	rect1.bottom = pos1.y + rect1.bottom - rect1.top;
//	rect1.top = pos1.y;
//
//	rect2.right = pos2.x + rect2.right - rect2.left;
//	rect2.left = pos2.x;
//	rect2.bottom = pos2.y + rect2.bottom - rect2.top;
//	rect2.top = pos2.y;
//
//	if (rect1.bottom < rect2.top) return false;
//	if (rect1.top > rect2.bottom) return false;
//	if (rect1.right < rect2.left) return false;
//	if (rect1.left > rect2.right) return false;
//
//	cout << "collide" << endl;
//	return true;
//}
//
//int collision::checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2)
//{
//	D3DXVECTOR2 offset = pos2 - pos1;
//	D3DXVec2Normalize(&offset, &offset);
//
//	if (abs(offset.x) > abs(offset.y))
//	{
//		if (offset.x > 0)
//		{
//			return 4;
//		}
//		else
//		{
//			return 3;
//		}
//	}
//	else
//	{
//		if (offset.y > 0)
//		{
//			return 2;
//		}
//		else
//		{
//			return 1;
//		}
//	}
//	return 0;
//}
