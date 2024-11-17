#include "map.h"

class map 
{
private :
		int width;
		int height;

public:
	void setWidth(int width)
	{
		this->width = width;
	}

	int getWidth() 
	{
		return this->width;
	}
};