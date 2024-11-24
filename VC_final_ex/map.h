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
	
	RECT box;
	RECT a;

public:

	int map_area[width][height];
	
	void Setmap();

	void Getmap(HDC,HWND,RECT);

};
