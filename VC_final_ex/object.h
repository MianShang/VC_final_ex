#pragma once
#include <stdlib.h>
#include <windows.h>
#include <random>
#include <vector>
#include <queue>
#include <utility>

#define Maze_Size 30

class OBject
{
private:

	RECT enemyPlace = { 940,790,970,820 };

	int area[30][25];

	std::vector<RECT>enemyplaces;
	std::pair<int, int> bfs(int start_x, int start_y);
	std::pair<int, int> nextMove;
	

public:

	RECT playerPlace = { 130,130,160,160 };
	RECT out;

	
	void setAreaCopy(int[][25]);
	void drawPlayer(HDC);
	void drawEnemy(HDC);
	void setPlayer(WPARAM, HWND);
	void setEnemy(HWND);

};