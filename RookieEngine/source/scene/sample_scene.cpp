#include "stdafx.h"
#include "sample_scene.h"

#include "imgui.h"

void Sample_Scene::render()
{
	// ������Ҫ��Ⱦ������
	for (auto component : ComponentList) {
		if(component->isRender)
			component->render();
	}
}
