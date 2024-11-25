#pragma once
#include <stdlib.h>
#include <windows.h>
#include <random>
#include <vector>
#include <queue>

#define Maze_Size 30

class OBject
{
private:
	int randomEnemyPlace;
	int area[30][25];
	bool visited[30][25];

	/*std::vector<std::vector<int>> maze(Maze_Size, std::vector<int>(Maze_Size));
	std::vector<std::vector<bool>> visted(Maze_Size, std::vector<bool>(Maze_Size));
	std::vector<std::vector<std::pair<int, int>>> track(Maze_Size, std::vector<std::pair<int, int>>(Maze_Size));*/


public:

	RECT enemyPlace = {940,790,970,820};
	RECT playerPlace = { 130,130,160,160 };
	RECT out;

	void bfs(int, int);
	void setAreaCopy(int[][25]);
	void drawPlayer(HDC);
	void drawEnemy(HDC);
	void setPlayer(WPARAM, HWND);
	void setEnemy(HWND);

};