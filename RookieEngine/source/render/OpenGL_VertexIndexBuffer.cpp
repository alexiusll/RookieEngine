#include "stdafx.h"
#include "OpenGL_VertexIndexBuffer.h"

void OpenGL_VertexIndexBuffer::create_buffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
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

void OpenGL_VertexIndexBuffer::delete_buffers()
{

}

void OpenGL_VertexIndexBuffer::bind()
{
	glBindVertexArray(mVAO);
}

void OpenGL_VertexIndexBuffer::unbind()
{
	glBindVertexArray(0);
}

void OpenGL_VertexIndexBuffer::draw()
{
	bind();

	// ��Ⱦ
	// glDrawArrays(GL_TRIANGLES, 0, 3);

	// ��һ������ָ�������ǻ��Ƶ�ģʽ �ڶ������������Ǵ�����ƶ���ĸ�����������6��Ҳ����˵����һ����Ҫ����6�����㡣
	// ���������������������ͣ�������GL_UNSIGNED_INT�����һ�����������ǿ���ָ��EBO�е�ƫ����
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	unbind();
}
