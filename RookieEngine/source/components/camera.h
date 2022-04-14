#pragma once


// 定义相机移动的几个可能选项。用作抽象，避免使用窗口系统特定的输入法
enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// 默认的相机属性
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// 相机的属性
	glm::vec3 Position; // 位置
	glm::vec3 Front; // 前方
	glm::vec3 Up; // 上面
	glm::vec3 Right; // 右边
	glm::vec3 WorldUp;

	// 欧拉角
	float Yaw;
	float Pitch;

	// 相机的设置
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// 构造函数
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;

		updateCameraVectors();
	}

	// 获取观察矩阵
	glm::mat4 GetViewMatrix();

	// --- 处理操作 ---

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

private:
	// 从相机的(更新)欧拉角计算前向量
	void updateCameraVectors();
};