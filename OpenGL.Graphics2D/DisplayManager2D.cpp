#include "DisplayManager2D.h"

DisplayManager2D::DisplayManager2D()
{
}

DisplayManager2D::DisplayManager2D(unsigned int width, unsigned int height, unsigned int LayerCount)
{
	Width = width;
	Height = height;

	ClearLayerTexture = std::make_unique<Texture>(Width, Height);

	Display2d = Display2D(Width, Height);
	Display2d.InitializeFrameBuffer();

	for (int x = 0; x <= LayerCount - 1; x++)
	{
		LayerList.emplace_back(Layer2D(Width, Height));
	}

	Background = BackGroundLayer(Width, Height);

}

DisplayManager2D::~DisplayManager2D()
{
}

void DisplayManager2D::Update()
{
	ClearLayers();

	for (auto Layer : LayerList)
	{
		glCopyImageSubData(ClearLayerTexture->GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, Layer.GetLayerTexture()->GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, ClearLayerTexture->GetWidth(), ClearLayerTexture->GetHeight(), 1);
		Layer.Update();
	}
	
	Background.Update();
	Display2d.Update(Background.GetDisplayTexture()->GetTextureID(), LayerList);
}

void DisplayManager2D::SetBackGroundPosition(int X, int Y)
{
	Background.SetPosition(X, Y);
}

void DisplayManager2D::ClearLayers()
{
	glCopyImageSubData(ClearLayerTexture->GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, Background.GetDisplayTexture()->GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, ClearLayerTexture->GetWidth(), ClearLayerTexture->GetHeight(), 1);
}

void DisplayManager2D::AddSprite(std::shared_ptr<Sprite> sprite, unsigned int Layer)
{
	LayerList[Layer].AddSprite(sprite);
}

void DisplayManager2D::AddBackGroundImage(std::shared_ptr<Texture> background)
{
	Background.SetBackGroundexture(background);
}
