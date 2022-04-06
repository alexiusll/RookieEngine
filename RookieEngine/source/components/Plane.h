#pragma once

#include "IComponent.h"
#include "shader/shader.h"
#include "render/OpenGL_VertexIndexBuffer.h"

class Plane : public IComponent {
public:
	void init();

	void create_buffers();

	void delete_buffers();

	void render();

	void bind();

	void unbind();

	/* ¸üÐÂ shader */
	void update(Shader* shader);

	void setVertices(std::vector<float>& Vertices, std::vector<unsigned int>& mVertexIndices) {
		this->mVertices = Vertices;
		this->mVertexIndices = mVertexIndices;
	}

	// ÑÕÉ«
	glm::vec3 color = glm::vec3(0.0f, 0.5f, 0.3f);

private:
	// Buffers manager
	std::unique_ptr<OpenGL_VertexIndexBuffer> openGL_VertexIndexBuffer;

	// Vertices and indices
	std::vector<float> mVertices;
	std::vector<unsigned int> mVertexIndices;
};