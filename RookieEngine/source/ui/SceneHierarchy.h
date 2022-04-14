#pragma once

#include <components/IComponent.h>
#include <scene/IScene.h>

// 使用单例模式
// 干脆先把显示列表和显示单个item的逻辑写在一起

class SceneHierarchy
{
public:
	static SceneHierarchy& Instance();

	void drawComponentsList();

	void drawComponentsProperties();

	void initScene(std::shared_ptr<SceneBase> scene);

	// 删除赋值和拷贝构造
	SceneHierarchy(const SceneHierarchy&) = delete;
	SceneHierarchy& operator=(const SceneHierarchy&) = delete;

private:
	// 设为私有
	SceneHierarchy();
	~SceneHierarchy();

	std::shared_ptr<SceneBase> scene;
	int m_SelectionCom;
};