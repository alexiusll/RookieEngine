#pragma once

#include <components/IComponent.h>
#include <scene/IScene.h>

// ʹ�õ���ģʽ
// �ɴ��Ȱ���ʾ�б����ʾ����item���߼�д��һ��

class SceneHierarchy
{
public:
	static SceneHierarchy& Instance();

	void drawComponentsList();

	void drawComponentsProperties();

	void initScene(std::shared_ptr<SceneBase> scene);

	// ɾ����ֵ�Ϳ�������
	SceneHierarchy(const SceneHierarchy&) = delete;
	SceneHierarchy& operator=(const SceneHierarchy&) = delete;

private:
	// ��Ϊ˽��
	SceneHierarchy();
	~SceneHierarchy();

	std::shared_ptr<SceneBase> scene;
	int m_SelectionCom;
};