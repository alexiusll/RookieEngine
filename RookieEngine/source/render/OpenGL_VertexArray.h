#pragma once

#include "OpenGL_IndexBuffer.h"
#include "OpenGL_VertexBuffer.h"

class OpenGL_VertexArray {

public:
    OpenGL_VertexArray() : mVAO(0), mVBO(0), mEBO(0)
    {
        glCreateVertexArrays(1, &mVAO);
    }
    ~OpenGL_VertexArray() {
        glDeleteVertexArrays(1, &mVAO);
    }

    void SetIndexBuffer(const std::shared_ptr<OpenGL_IndexBuffer>& indexBuffer);

    void AddVertexBuffer(const std::shared_ptr<OpenGL_VertexBuffer>& vertexBuffer);

    /* 弃用，仅作参考 */
    void create_buffers(const std::vector<float>& vertices , const std::vector<unsigned int>& indices);

    void delete_buffers();

    void bind();

    void unbind();

    void draw();

protected:
    GLuint mVBO; // 顶点缓冲对象(Vertex Buffer Objects, VBO)
    GLuint mVAO; // 顶点数组对象(Vertex Array Object, VAO)
    GLuint mEBO; // 索引缓冲对象(Element Buffer Object，EBO，也叫Index Buffer Object，IBO)

    uint32_t m_VertexBufferIndex = 0;
    std::shared_ptr<OpenGL_IndexBuffer> m_IndexBuffer; // 索引缓冲对象(Element Buffer Object，EBO，也叫Index Buffer Object，IBO)
    std::vector<std::shared_ptr<OpenGL_VertexBuffer>> m_VertexBuffers; // 顶点缓冲对象(Vertex Buffer Objects, VBO)
};