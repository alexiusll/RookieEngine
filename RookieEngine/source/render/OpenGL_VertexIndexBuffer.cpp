#include "stdafx.h"
#include "OpenGL_VertexIndexBuffer.h"

void OpenGL_VertexIndexBuffer::create_buffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
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

	// 渲染
	// glDrawArrays(GL_TRIANGLES, 0, 3);

	// 第一个参数指定了我们绘制的模式 第二个参数是我们打算绘制顶点的个数，这里填6，也就是说我们一共需要绘制6个顶点。
	// 第三个参数是索引的类型，这里是GL_UNSIGNED_INT。最后一个参数里我们可以指定EBO中的偏移量
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	unbind();
}
