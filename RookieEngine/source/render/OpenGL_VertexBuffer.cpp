#include "stdafx.h"
#include "OpenGL_VertexBuffer.h"

OpenGL_VertexBuffer::OpenGL_VertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
{
	glDeleteBuffers(1, &mVBO);
}

void OpenGL_VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
}

void OpenGL_VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGL_VertexBuffer::SetData(const void* data, uint32_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
