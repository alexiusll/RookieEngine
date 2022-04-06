#pragma once

class OpenGL_VertexIndexBuffer {

public:
    OpenGL_VertexIndexBuffer() : mVAO(0), mVBO(0)
    {
    }

    void create_buffers(const std::vector<float>& vertices , const std::vector<unsigned int>& indices);

    void delete_buffers();

    void bind();

    void unbind();

    void draw();

protected:
    GLuint mVBO; // 顶点缓冲对象(Vertex Buffer Objects, VBO)
    GLuint mVAO; // 顶点数组对象(Vertex Array Object, VAO)
    GLuint mEBO; // 索引缓冲对象(Element Buffer Object，EBO，也叫Index Buffer Object，IBO)
};