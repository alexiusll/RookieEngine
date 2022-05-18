#include "stdafx.h"

#include "imgui.h"

#include "Plane.h"

#include "render/OpenGL_VertexArray.h"
#include "render/OpenGL_VertexBuffer.h"
#include "render/OpenGL_IndexBuffer.h"

#include "scene/SceneManager.h"

#include "shader/Material.h"


Plane::Plane()
{
	init();
}

Plane::~Plane()
{

}

void Plane::init()
{
	name = "Plane";
	isRender = true;

	// 初始化 着色器
	mShader = std::make_shared<Shader>("first.vert", "first.frag");
	material.SetShader(mShader);

	// 初始化 材质
	auto temp = {
		std::make_shared<MaterialElement<glm::vec3>>("color", MaterialDataType::Color, glm::vec3(0.5,0.5,0.5)),
	};
	std::shared_ptr<MaterialLayout> materialLayout = std::make_shared<MaterialLayout>(temp);
	material.SetMaterialLayout(materialLayout);

	openGL_VertexArray = std::make_unique<OpenGL_VertexArray>();
}

void Plane::create_buffers(std::vector<float>& Vertices, std::vector<unsigned int>& mVertexIndices)
{
	// openGL_VertexArray->create_buffers(mVertices , mVertexIndices);

	std::shared_ptr<OpenGL_VertexBuffer> openGL_VertexBuffer = std::make_shared<OpenGL_VertexBuffer>(Vertices.data(), Vertices.size() * sizeof(float));
	BufferLayout layout = {
		{ShaderDataType::Float3, "a_Position"},
	};
	openGL_VertexBuffer->SetLayout(layout);
	openGL_VertexArray->AddVertexBuffer(openGL_VertexBuffer);

	std::shared_ptr<OpenGL_IndexBuffer> openGL_IndexBuffer = std::make_shared<OpenGL_IndexBuffer>(mVertexIndices.data(), mVertexIndices.size());
	openGL_VertexArray->SetIndexBuffer(openGL_IndexBuffer);
}

void Plane::delete_buffers()
{
	openGL_VertexArray->delete_buffers();
}

void Plane::render()
{
	mShader->use();

	updateShader();

	openGL_VertexArray->draw();
}

MaterialLayout materialLayout({
	std::make_shared<MaterialElement<glm::vec3>>("color", MaterialDataType::Color, glm::vec3(0.5,0.5,0.5)),
});

void Plane::DrawUi()
{

	// ImGui::ColorPicker3("Color", (float*)&color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
	// materialLayout.GetElements()[0]->drawUi();

	material.drawUi();

	if (ImGui::TreeNodeEx("transform" , ImGuiTreeNodeFlags_DefaultOpen)) {

		draw_vec3_widget("Position", transform.Translation, 80.0f);

		glm::vec3 rotation = glm::degrees(transform.Rotation);
		draw_vec3_widget("Rotation", rotation, 80.0f);
		transform.Rotation = glm::radians(rotation);

		draw_vec3_widget("Scale", transform.Scale, 80.0f);

		ImGui::TreePop();
	}

}

void Plane::bind()
{
	openGL_VertexArray->bind();
}

void Plane::unbind()
{
	openGL_VertexArray->unbind();
}

void Plane::updateShader()
{
	// 设置 plane 色彩
	// mShader->setVec3("color", color);

	// --- mvp 矩阵 ---
	const glm::vec2 WindowSize = SceneManager::Instance().getWindowSize();
	std::shared_ptr<Camera> camera = SceneManager::Instance().getCamera();

	// 使用透视投影
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)WindowSize.x / (float)WindowSize.y, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();

	// glm::mat4 model = glm::mat4(1.0f);
	// model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));

	glm::mat4 model = transform.GetTransform();

	mShader->setMat4("projection", projection);
	mShader->setMat4("view", view);
	mShader->setMat4("model", model);
}

