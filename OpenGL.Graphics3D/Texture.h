#pragma once
class Texture
{
private:
	unsigned int TextureID;
	int Width;
	int Height;
	int ColorChannels;

public:
	Texture();
	Texture(unsigned int width, unsigned int height);
	Texture(char const* FilePath);
	~Texture();

	void ReleaseTexture();

	Texture& operator=(const Texture& rhs);
	unsigned int GetTextureID() { return TextureID; }
	int GetWidth() { return Width; }
	int GetHeight() { return Height; }
};

