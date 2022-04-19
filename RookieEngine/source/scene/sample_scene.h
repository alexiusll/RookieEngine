#pragma once
#include "shader/shader.h"
#include "components/Plane.h"

#include "IScene.h"
#include "render/OpenGL_FrameBuffer.h"

#include "shader/Material.h"

static std::vector<float> _vertices = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

static std::vector<unsigned int> _indices = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

static std::vector<float> _vertices_2 = {
	1.0f, 1.0f, 0.0f,   // 右上角
	1.0f, 0.5f, 0.0f,  // 右下角
	0.0f, 0.5f, 0.0f, // 左下角
	0.0f, 1.0f, 0.0f   // 左上角
};

static std::vector<unsigned int> _indices_2 = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

// 最简单的场景
class Sample_Scene : public SceneBase
{
public:
	Sample_Scene() {
		// 创建一个 plane
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
