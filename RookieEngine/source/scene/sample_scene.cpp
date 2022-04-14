#include "stdafx.h"
#include "sample_scene.h"

#include "imgui.h"

void Sample_Scene::render()
{
	// 所有需要渲染的物体
	for (auto component : ComponentList) {
		if(component->isRender)
			component->render();
	}
}
