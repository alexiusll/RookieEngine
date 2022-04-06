#include "stdafx.h"

#include "Plane.h"

void Plane::init()
{
	openGL_VertexIndexBuffer = std::make_unique<OpenGL_VertexIndexBuffer>();

	create_buffers();
}

void Plane::create_buffers()
{
	openGL_VertexIndexBuffer->create_buffers(mVertices , mVertexIndices);
}

void Plane::delete_buffers()
{
	openGL_VertexIndexBuffer->delete_buffers();
}

void Plane::render()
{
	openGL_VertexIndexBuffer->draw();
}

void Plane::bind()
{
	openGL_VertexIndexBuffer->bind();
}

void Plane::unbind()
{
	openGL_VertexIndexBuffer->unbind();
}

void Plane::update(Shader* shader)
{
	shader->setVec3("color", color);
}


