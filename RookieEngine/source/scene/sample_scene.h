#pragma once
#include "shader/shader.h"
#include "components/Plane.h"

#include "IScene.h"
#include "render/OpenGL_FrameBuffer.h"

static std::vector<float> _vertices = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
};

static std::vector<unsigned int> __indices = { // ע��������0��ʼ! 
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

// ��򵥵ĳ���
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

	/* ֡���� */
	void resize(int32_t width, int32_t height); 

	std::shared_ptr<Plane> getPlane() {
		return mPlane;
	}

private:
	std::unique_ptr<Shader> mShader; // ��ɫ��
	std::shared_ptr<Plane> mPlane;

	// ֡����
	std::unique_ptr<OpenGL_FrameBuffer> mFrameBuffer;
	glm::vec2 mSize; 
};
