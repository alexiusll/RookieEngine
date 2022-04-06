#pragma once

class Shader
{
public:
	//构建函数和解构函数
	~Shader();

	// 程序ID
	unsigned int Program;

	// 构造器读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	// 使用/激活程序
	void use();

	// uniform工具函数
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