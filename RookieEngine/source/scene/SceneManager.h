#pragma once
#include "components/camera.h"
#include "IScene.h"
#include "render/OpenGL_FrameBuffer.h"

// scene 管理类
// 使用单例模式，用来使场景中不同的 components 进行通信
// 例如场景中的物体需要知道主摄影机的位置, 光照的位置

class SceneManager
{
public:
	static SceneManager& Instance();
	void init();
	/* 渲染当前场景 */
	void draw();

	std::shared_ptr<SceneBase> getNativeScene() { return scene; };
	std::shared_ptr<Camera> getCamera() { return camera; };

	/* 重设帧缓冲大小 */
	void resize(int32_t width, int32_t height);

	/* 获取当前窗口大小 */
	glm::vec2& getWindowSize() { return mSize; };

	// 删除赋值和拷贝构造
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
private:
	// 设为私有
	SceneManager();
	~SceneManager();
private:
	// 认为一个场景中只会有一个相机，所以相机放在这里
	std::shared_ptr<Camera> camera;
	std::shared_ptr<SceneBase> scene; // 场景 

	// 使用 帧缓冲
	std::unique_ptr<OpenGL_FrameBuffer> mFrameBuffer;
	glm::vec2 mSize;
};

