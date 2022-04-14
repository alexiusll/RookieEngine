#include "stdafx.h"
#include "OpenGL_VertexArray.h"

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
	}

	DEBUG_LOG("Unknown ShaderDataType!");
	return 0;
}

void OpenGL_VertexArray::SetIndexBuffer(const std::shared_ptr<OpenGL_IndexBuffer>& indexBuffer)
{
	glBindVertexArray(mVAO);
	indexBuffer->bind();

	m_IndexBuffer = indexBuffer;
}

void OpenGL_VertexArray::AddVertexBuffer(const std::shared_ptr<OpenGL_VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(mVAO);
	vertexBuffer->bind();

	const auto& layout = vertexBuffer->GetLayout();

	for (const auto& element : layout)
	{
		switch (element.Type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		{
			DEBUG_LOG("m_VertexBufferIndex:%d", m_VertexBufferIndex);
			DEBUG_LOG("element.GetComponentCount():%d", element.GetComponentCount());


			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
			break;
		}
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
		case ShaderDataType::Bool:
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribIPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
			break;
		}
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
		{
			uint8_t count = element.GetComponentCount();
			for (uint8_t i = 0; i < count; i++)
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					count,
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)(element.Offset + sizeof(float) * count * i));
				glVertexAttribDivisor(m_VertexBufferIndex, 1);
				m_VertexBufferIndex++;
			}
			break;
		}
		default:
			DEBUG_LOG("Unknown ShaderDataType!");
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
}



/* ���ã������ο� */
void OpenGL_VertexArray::create_buffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
{
	// �ο�
	// https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/

	// ����
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO); // �� VAO

	// glBufferData()
	// ��һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ�
	// �ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵�sizeof������������ݴ�С���С�
	// ����������������ϣ�����͵�ʵ�����ݡ�
	// ���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// glVertexAttribPointer()
	// ��һ������ָ������Ҫ���õĶ������ԡ��Ѷ������Ե�λ��ֵ����Ϊ0
	// �ڶ�������ָ���������ԵĴ�С��
	// ����������ָ�����ݵ�����
	// �¸��������������Ƿ�ϣ�����ݱ���׼��(Normalize)
	// �����������������(Stride)�������������������Ķ���������֮��ļ����
	// ���һ��������������void*��������Ҫ���ǽ��������ֵ�ǿ������ת��.����ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // �Զ�������λ��ֵ��Ϊ���������ö�������

	glBindVertexArray(0);// ��� VAO ��
}

void OpenGL_VertexArray::delete_buffers()
{

}

void OpenGL_VertexArray::bind()
{
	glBindVertexArray(mVAO);
}

void OpenGL_VertexArray::unbind()
{
	glBindVertexArray(0);
}

void OpenGL_VertexArray::draw()
{
	bind();

	// ��Ⱦ
	// glDrawArrays(GL_TRIANGLES, 0, 3);

	// ��һ������ָ�������ǻ��Ƶ�ģʽ �ڶ������������Ǵ�����ƶ���ĸ�����������6��Ҳ����˵����һ����Ҫ����6�����㡣
	// ���������������������ͣ�������GL_UNSIGNED_INT�����һ�����������ǿ���ָ��EBO�е�ƫ����
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	uint32_t count = m_IndexBuffer->GetCount();
	// DEBUG_LOG("draw count:%d", count);

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	// glBindTexture(GL_TEXTURE_2D, 0);

	unbind();
}
