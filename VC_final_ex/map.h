#pragma once
#include <stdlib.h>
#include <windows.h>

#define width 30
#define height 25

enum map
{
	space, wall, item, start
};

class Map_Area 
{
private:


public:

	int map_area[width][height];
	RECT box = { 0,0,30,30 };
	void Setmap();
	void Getmap(HDC hdc);

};
