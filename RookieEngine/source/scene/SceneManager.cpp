#include "stdafx.h"
#include "SceneManager.h"

#include "scene/sample_scene.h"
#include "ui/SceneHierarchy.h"

SceneManager::SceneManager():mSize(800,600)
{
	init();
}

SceneManager::~SceneManager()
{

}

void SceneManager::init()
{
	// 创建帧缓冲
	mFrameBuffer = std::make_unique<OpenGL_FrameBuffer>();
	mFrameBuffer->create_buffers(800, 600);

	// 初始化 scene ，目前scene写死
	scene = std::make_shared<Sample_Scene>();
	SceneHierarchy::Instance().initScene(scene);

	// 初始化摄影机
	camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 1.0f));
}

void SceneManager::draw()
{
	mFrameBuffer->bind();

	// 渲染当前场景
	scene->render();

	mFrameBuffer->unbind();

	// --- 渲染Scene的窗口 ---
	ImGui::Begin("Scene");
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	// std::cout << viewportPanelSize.x << " " << viewportPanelSize.y << std::endl;

	mSize = { viewportPanelSize.x, viewportPanelSize.y };

	// add rendered texture to ImGUI scene window
	uint64_t textureID = mFrameBuffer->get_texture();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
}

void SceneManager::resize(int32_t width, int32_t height)
{
	mSize.x = width;
	mSize.y = height;

	mFrameBuffer->create_buffers((int32_t)mSize.x, (int32_t)mSize.y);
}

SceneManager& SceneManager::Instance()
{
	// TODO: 在此处插入 return 语句
	static SceneManager instance;
	return instance;
}




