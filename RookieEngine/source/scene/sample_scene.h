#pragma once
#include "shader/shader.h"
#include "components/Plane.h"

#include "IScene.h"
#include "render/OpenGL_FrameBuffer.h"

#include "shader/Material.h"

static std::vector<float> _vertices = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
};

static std::vector<unsigned int> _indices = { // ע��������0��ʼ! 
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

static std::vector<float> _vertices_2 = {
	1.0f, 1.0f, 0.0f,   // ���Ͻ�
	1.0f, 0.5f, 0.0f,  // ���½�
	0.0f, 0.5f, 0.0f, // ���½�
	0.0f, 1.0f, 0.0f   // ���Ͻ�
};

static std::vector<unsigned int> _indices_2 = { // ע��������0��ʼ! 
	0, 1, 3, // ��һ��������
	1, 2, 3  // �ڶ���������
};

// ��򵥵ĳ���
class Sample_Scene : public SceneBase
{
public:
	Sample_Scene() {
		// ����һ�� plane
		std::shared_ptr<Plane> mPlane = std::make_shared<Plane>();
		mPlane->create_buffers(_vertices, _indices);
		ComponentList.emplace_back(mPlane);

		//std::shared_ptr<Plane> mPlane2 = std::make_shared<Plane>();
		//mPlane2->create_buffers(_vertices_2, _indices_2);
		//ComponentList.emplace_back(mPlane2);

	}
	void render();
private:
};
