#pragma once
#include "shader/shader.h"
#include "components/Plane.h"

#include "IScene.h"
#include "render/OpenGL_FrameBuffer.h"

static std::vector<float> _vertices = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

static std::vector<unsigned int> __indices = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

// 最简单的场景
class Sample_Scene : public SceneBase
{
public:
	Sample_Scene() {
		mShader = std::make_unique<Shader>("first.vert", "first.frag");

		mFrameBuffer = std::make_unique<OpenGL_FrameBuffer>();
		mFrameBuffer->create_buffers(800, 600);

		mPlane = std::make_shared<Plane>();
		mPlane->setVertices(_vertices, __indices);
		mPlane->init();
	}

	void render();

	/* 帧缓冲 */
	void resize(int32_t width, int32_t height); 

	std::shared_ptr<Plane> getPlane() {
		return mPlane;
	}

private:
	std::unique_ptr<Shader> mShader; // 着色器
	std::shared_ptr<Plane> mPlane;

	// 帧缓冲
	std::unique_ptr<OpenGL_FrameBuffer> mFrameBuffer;
	glm::vec2 mSize; 
};
