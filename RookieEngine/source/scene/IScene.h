#pragma once
#include <components/IComponent.h>

class SceneBase
{
public:
	/* ��Ⱦ���� */
	virtual void render() = 0;
	std::vector<std::shared_ptr<IComponent>>& getComponentList() { return ComponentList; };
protected:
	std::vector<std::shared_ptr<IComponent>> ComponentList;
};