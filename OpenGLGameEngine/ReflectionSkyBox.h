#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../OpenGL.Graphics3D/camera.h"
#include "../OpenGL.Graphics3D/FrameBuffer.h"
#include "SkyBox.h"

class ReflectionSkyBox
{
private:
	glm::vec3 Center;
	std::vector<FrameBuffer> FrameBufferViews;
	std::vector<Camera> CameraViews;
	SkyBox skybox;
public:
	ReflectionSkyBox();
	ReflectionSkyBox(glm::vec3 center);
	~ReflectionSkyBox();

};

