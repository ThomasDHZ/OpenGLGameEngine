#pragma once
#include <vector>
#include <string>
#include "../OpenGL.Graphics3D/shader_m.h"
#include "../OpenGL.Graphics3D/camera.h"

class SkyBox
{
private:

	unsigned int SkyboxVAO;
	unsigned int SkyboxVBO;
	unsigned int CubemapTexture;

	unsigned int LoadCubeMapTextures(std::vector<std::string> CubeMapFaces);

public:
	SkyBox();
	SkyBox(std::vector<std::string> CubeMapFaces);
	~SkyBox();

	void Update(Shader2 SkyBoxShader, Camera& camera, unsigned int WindowWidth, unsigned int WindowHeight);
	unsigned int GetCubemapTexture() { return CubemapTexture; };
};

