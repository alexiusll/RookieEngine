#include "stdafx.h"
#include "sample_scene.h"

#include "imgui.h"

void Sample_Scene::render()
{
	mShader->use();

	mFrameBuffer->bind();

	if (mPlane) {
		mPlane->update(mShader.get()); // 这里要保证指针不会被修改
		mPlane->render();
	}

	mFrameBuffer->unbind();

	ImGui::Begin("Scene");

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	// std::cout << viewportPanelSize.x << " " << viewportPanelSize.y << std::endl;

	mSize = { viewportPanelSize.x, viewportPanelSize.y };

	// add rendered texture to ImGUI scene window
	uint64_t textureID = mFrameBuffer->get_texture();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();
}

void Sample_Scene::resize(int32_t width, int32_t height)
{
	mSize.x = width;
	mSize.y = height;

	mFrameBuffer->create_buffers((int32_t)mSize.x, (int32_t)mSize.y);
}
