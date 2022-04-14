#pragma once
#include "components/camera.h"
#include "IScene.h"
#include "render/OpenGL_FrameBuffer.h"

// scene ������
// ʹ�õ���ģʽ������ʹ�����в�ͬ�� components ����ͨ��
// ���糡���е�������Ҫ֪������Ӱ����λ��, ���յ�λ��

class SceneManager
{
public:
	static SceneManager& Instance();
	void init();
	/* ��Ⱦ��ǰ���� */
	void draw();

	std::shared_ptr<SceneBase> getNativeScene() { return scene; };
	std::shared_ptr<Camera> getCamera() { return camera; };

	/* ����֡�����С */
	void resize(int32_t width, int32_t height);

	/* ��ȡ��ǰ���ڴ�С */
	glm::vec2& getWindowSize() { return mSize; };

	// ɾ����ֵ�Ϳ�������
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
private:
	// ��Ϊ˽��
	SceneManager();
	~SceneManager();
private:
	// ��Ϊһ��������ֻ����һ����������������������
	std::shared_ptr<Camera> camera;
	std::shared_ptr<SceneBase> scene; // ���� 

	// ʹ�� ֡����
	std::unique_ptr<OpenGL_FrameBuffer> mFrameBuffer;
	glm::vec2 mSize;
};

