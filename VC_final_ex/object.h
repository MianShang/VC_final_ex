#pragma once

#include <stdlib.h>
#include <windows.h>
#include "resource.h"

class OBject
{
private:
	
	bool play = TRUE;

public:
	
	RECT playerPlace = { 130,130,160,160 };

	void drawPlayer(HDC);

	void setPlayer(WPARAM);

	
		
};