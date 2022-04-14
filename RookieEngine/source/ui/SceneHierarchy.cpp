#include "stdafx.h"
#include "SceneHierarchy.h"

SceneHierarchy::SceneHierarchy():m_SelectionCom(-1)
{
}

SceneHierarchy::~SceneHierarchy()
{
}

SceneHierarchy& SceneHierarchy::Instance()
{
	static SceneHierarchy instance;
	return instance;
}

void SceneHierarchy::drawComponentsList()
{
	ImGui::Begin("SceneHierarchy");
	if (scene->getComponentList().size() > 0) {
		for (int i = 0; i < scene->getComponentList().size(); i++) {

			char label[128];
			sprintf_s(label, "%d:%s",i, scene->getComponentList()[i]->getName().c_str());

			if (ImGui::Selectable(label, m_SelectionCom == i))
			{
				m_SelectionCom = i;
			}
		}
	}
	ImGui::End();
}

void SceneHierarchy::drawComponentsProperties()
{
	ImGui::Begin("Properties");
	if (m_SelectionCom >= 0 )
	{
		scene->getComponentList()[m_SelectionCom]->DrawUi();
	}
	ImGui::End();
}

void SceneHierarchy::initScene(std::shared_ptr<SceneBase> scene)
{
	this->scene = scene;
}

