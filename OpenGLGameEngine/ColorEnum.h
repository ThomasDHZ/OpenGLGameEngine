#pragma once

struct Color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Color()
	{
		r = 0;
		g = 0;
		b = 0;
	}

	Color(unsigned char Red, unsigned char Green, unsigned char Blue)
	{
		r = Red;
		g = Green;
		b = Blue;
	}
};