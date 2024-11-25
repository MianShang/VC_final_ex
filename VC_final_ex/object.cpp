#include "object.h"

int a, b;

void OBject::setAreaCopy(int area[][25])
{
	for (int i = 0; i < 30; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{
			this->area[i][j] = area[i][j];
		}
	}
}

void OBject::drawPlayer(HDC memDC)
{	
	HBRUSH myBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH osBrush = (HBRUSH)SelectObject(memDC, myBrush);
	Ellipse(memDC, playerPlace.left, playerPlace.top, playerPlace.right, playerPlace.bottom);
	SelectObject(memDC, osBrush);
	DeleteObject(osBrush);
	DeleteObject(myBrush);
}

void OBject::drawEnemy(HDC memDC)
{	
	HBRUSH myBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH osBrush = (HBRUSH)SelectObject(memDC, myBrush);
	Ellipse(memDC, enemyPlace.left, enemyPlace.top, enemyPlace.right, enemyPlace.bottom);
	SelectObject(memDC, osBrush);
	DeleteObject(osBrush);
	DeleteObject(myBrush);
}

void OBject::setPlayer(WPARAM wParam,HWND hWnd)
{		
	a = (playerPlace.left -100 ) / 30;
	b = (playerPlace.top - 100) / 30;

	switch (wParam)
	{
	case VK_RIGHT:
	{	
		if (area[a + 1][b] == 1) 
		{
			break;
		}
		playerPlace.left += 30;
		playerPlace.right = playerPlace.left + 30;

	}
	break;
	case VK_UP:
	{	
		if (area[a][b-1] == 1)
		{
			break;
		}
			playerPlace.top -= 30;
			playerPlace.bottom = playerPlace.top + 30;
	}
	break;
	case VK_LEFT:
	{	
		if (area[a-1][b] == 1)
		{
			break;
		}
			playerPlace.left -= 30;
			playerPlace.right = playerPlace.left + 30;
	}
	break;
	case VK_DOWN:
	{	
		if (area[a][b + 1] == 1)
		{
			break;
		}
			playerPlace.top += 30;
			playerPlace.bottom = playerPlace.top + 30;
	}
	break;
	}

	if (IntersectRect(&out, &playerPlace, &enemyPlace))
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, L"적에게 당했습니다", L"게임종료", MB_OK);
	}

}

void OBject::setEnemy(HWND hWnd) 
{
	a = (enemyPlace.left - 100) / 30;
	b = (enemyPlace.top - 100) / 30;

	randomEnemyPlace = rand() % 4;
	
	switch (randomEnemyPlace)
	{
	case 0:
	{
		if (area[a + 1][b] == 1)
		{
			break;
		}
		enemyPlace.left += 30;
		enemyPlace.right = enemyPlace.left + 30;

	}
	break;
	case 1:
	{
		if (area[a][b - 1] == 1)
		{
			break;
		}
		enemyPlace.top -= 30;
		enemyPlace.bottom = enemyPlace.top + 30;
	}
	break;
	case 2:
	{
		if (area[a - 1][b] == 1)
		{
			break;
		}
		enemyPlace.left -= 30;
		enemyPlace.right = enemyPlace.left + 30;
	}
	break;
	case 3:
	{
		if (area[a][b + 1] == 1)
		{
			break;
		}
		enemyPlace.top += 30;
		enemyPlace.bottom = enemyPlace.top + 30;
	}
	break;

	}


	if (IntersectRect(&out, &playerPlace, &enemyPlace))
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, L"적에게 당했습니다", L"게임종료", MB_OK);
	}
}

void OBject::bfs(int start_x, int start_y ) 
{

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			visited[i][j] = false;
		}
	}

	/*std::queue<pair<int,int>> q;
	q.push({ start_x,start_y });*/

	
}