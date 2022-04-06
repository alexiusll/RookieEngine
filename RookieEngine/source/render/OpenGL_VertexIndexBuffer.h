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
    GLuint mVBO; // ���㻺�����(Vertex Buffer Objects, VBO)
    GLuint mVAO; // �����������(Vertex Array Object, VAO)
    GLuint mEBO; // �����������(Element Buffer Object��EBO��Ҳ��Index Buffer Object��IBO)
};