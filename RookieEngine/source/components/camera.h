#pragma once


// ��������ƶ��ļ�������ѡ��������󣬱���ʹ�ô���ϵͳ�ض������뷨
enum class Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Ĭ�ϵ��������
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// ���������
	glm::vec3 Position; // λ��
	glm::vec3 Front; // ǰ��
	glm::vec3 Up; // ����
	glm::vec3 Right; // �ұ�
	glm::vec3 WorldUp;

	// ŷ����
	float Yaw;
	float Pitch;

	// ���������
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// ���캯��
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;

		updateCameraVectors();
	}

	// ��ȡ�۲����
	glm::mat4 GetViewMatrix();

	// --- ������� ---

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

private:
	// �������(����)ŷ���Ǽ���ǰ����
	void updateCameraVectors();
};