#pragma once

#include "IComponent.h"
#include "shader/shader.h"
#include "render/OpenGL_VertexArray.h"
#include "camera.h"

#include "shader/Material.h"

class Plane : public IComponent {
public:
	Plane();
	~Plane();

	void init();
	void render() override;
	void DrawUi() override;

	/* ���� shader */
	void updateShader();
	void create_buffers(std::vector<float>& Vertices, std::vector<unsigned int>& mVertexIndices);

	// ��ɫ
	// glm::vec3 color = glm::vec3(0.0f, 0.5f, 0.3f);

private:
	void bind();
	void unbind();
	void delete_buffers();

	// transform
	TransformComponent transform;

	// Buffers manager
	std::unique_ptr<OpenGL_VertexArray> openGL_VertexArray;

	// ���ʲ�
	Material material;

	// ��ɫ��
	std::shared_ptr<Shader> mShader; 
};