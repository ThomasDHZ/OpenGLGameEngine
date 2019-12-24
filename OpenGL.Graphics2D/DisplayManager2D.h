#pragma once
#include "Display2D.h"
#include "BackGroundLayer.h"
#include "Layer2D.h"
class DisplayManager2D
{
private:
	unsigned int Width;
	unsigned int Height;
	
	std::shared_ptr<Texture> ClearLayerTexture;

	Layer2D Layer;
	BackGroundLayer Background;
	Display2D Display2d;

	void ClearLayers();
public:
	DisplayManager2D();
	DisplayManager2D(unsigned int width, unsigned int height);
	~DisplayManager2D();

	void Update();
	void AddSprite(std::shared_ptr<Sprite> sprite);
	void AddBackGroundImage(std::shared_ptr<Texture> background);
};

