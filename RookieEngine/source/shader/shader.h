#pragma once

class Shader
{
public:
	//���������ͽ⹹����
	~Shader();

	// ����ID
	unsigned int Program;

	// ��������ȡ��������ɫ��
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	// ʹ��/�������
	void use();

	// uniform���ߺ���
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;

private:
	const std::string SHADER_PATH = ".\\source\\shader\\shaders\\";

	void checkCompileErrors(unsigned int shader, std::string type);
};