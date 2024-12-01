#pragma once
#include <stdlib.h>
#include <windows.h>
#include "object.h"

#define width 30
#define height 25

enum map
{
	space, wall,item , start, enemy
};

class Map_Area 
{
private:
	
	wchar_t PlayTimeText[100];

	RECT box;
	RECT a;

	wchar_t bufi[128] = { 0, };

	int PlayTime = 0;

public:

	int map_area[width][height];
	int g_item = 0;
	int f_item = 0;

	void Setmap();
	void Getmap(HDC,HWND,RECT);
	void resetGame(std::unique_ptr<OBject>& object, HDC); // 게임 리셋
	void SetPlayTime();
};
