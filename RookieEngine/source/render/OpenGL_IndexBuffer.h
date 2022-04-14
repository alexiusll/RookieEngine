#pragma once
class OpenGL_IndexBuffer
{
public:
	OpenGL_IndexBuffer(uint32_t* indices, uint32_t count);
	~OpenGL_IndexBuffer();

	void bind() const;
	void unbind() const;

	uint32_t GetCount() const { return m_Count; }

private:
	GLuint mEBO;
	uint32_t m_Count;
};

