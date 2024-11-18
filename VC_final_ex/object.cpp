#include "object.h"



void OBject::drawPlayer(HDC memDC)
{
	Ellipse(memDC, playerPlace.left, playerPlace.top, playerPlace.right, playerPlace.bottom);
}

void OBject::setPlayer(WPARAM wParam)
{	
	
	switch (wParam)
	{
	case VK_RIGHT:
	{	
		playerPlace.left += 30;
		playerPlace.right = playerPlace.left + 30;
	}
	break;
	case VK_UP:
	{
		playerPlace.top -= 30;
		playerPlace.bottom = playerPlace.top + 30;
	}
	break;
	case VK_LEFT:
	{
		playerPlace.left -= 30;
		playerPlace.right = playerPlace.left + 30;
	}
	break;
	case VK_DOWN:
	{
		playerPlace.top += 30;
		playerPlace.bottom = playerPlace.top + 30;
	}
	break;
	}
	
}