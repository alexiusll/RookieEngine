#include "stdafx.h"
#include "OpenGL_IndexBuffer.h"

OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
{
	glCreateBuffers(1, &mEBO);

	DEBUG_LOG("OpenGL_IndexBuffer count:%d", count);

	// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
	// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
	glBindBuffer(GL_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
{
	glDeleteBuffers(1, &mEBO);
}

void OpenGL_IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
}

void OpenGL_IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
}
