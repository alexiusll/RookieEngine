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



/* 弃用，仅作参考 */
void OpenGL_VertexArray::create_buffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
{
	// 参考
	// https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/

	// 生成
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO); // 绑定 VAO

	// glBufferData()
	// 第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
	// 第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。
	// 第三个参数是我们希望发送的实际数据。
	// 第四个参数指定了我们希望显卡如何管理给定的数据。

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// glVertexAttribPointer()
	// 第一个参数指定我们要配置的顶点属性。把顶点属性的位置值设置为0
	// 第二个参数指定顶点属性的大小。
	// 第三个参数指定数据的类型
	// 下个参数定义我们是否希望数据被标准化(Normalize)
	// 第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。
	// 最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换.它表示位置数据在缓冲中起始位置的偏移量(Offset)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // 以顶点属性位置值作为参数，启用顶点属性

	glBindVertexArray(0);// 清空 VAO 绑定
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

	// 渲染
	// glDrawArrays(GL_TRIANGLES, 0, 3);

	// 第一个参数指定了我们绘制的模式 第二个参数是我们打算绘制顶点的个数，这里填6，也就是说我们一共需要绘制6个顶点。
	// 第三个参数是索引的类型，这里是GL_UNSIGNED_INT。最后一个参数里我们可以指定EBO中的偏移量
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	uint32_t count = m_IndexBuffer->GetCount();
	// DEBUG_LOG("draw count:%d", count);

	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	// glBindTexture(GL_TEXTURE_2D, 0);

	unbind();
}
