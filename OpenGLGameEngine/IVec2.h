#pragma once
struct IVec2
{
	unsigned int x;
	unsigned int y;

	IVec2()
	{
		x = 0;
		y = 0;
	}

	IVec2(unsigned int X, unsigned int Y)
	{
		x = X;
		y = Y;
	}

	IVec2& operator=(const IVec2& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return* this;
	}
};

