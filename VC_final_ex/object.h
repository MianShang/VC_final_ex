#pragma once
#include <stdlib.h>
#include <windows.h>
#include <random>


class OBject
{
private:
	int randomEnemyPlace;
	int area[30][25];

public:

	RECT enemyPlace = {940,790,970,820};
	RECT playerPlace = { 130,130,160,160 };
	RECT out;

	void setAreaCopy(int[][25]);
	void drawPlayer(HDC);
	void drawEnemy(HDC);
	void setPlayer(WPARAM, HWND);
	void setEnemy(HWND);

};