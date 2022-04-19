#pragma once

#include "imgui.h"

enum class MaterialDataType // shader data 类型
{
	None = 0, Vec3
};

class MaterialElementBase {
public:
	virtual void drawUi() = 0;
};

template <typename T>
class MaterialElement: public MaterialElementBase
{
public:
	MaterialElement() = default;
	MaterialElement(const std::string& name, MaterialDataType type, T value): mName(name), mType(type), mValue(value) {}
	void drawUi() override {
		// 绘制UI界面
		if (mType == MaterialDataType::Vec3) {
			ImGui::ColorPicker3(mName.c_str(), (float*)&mValue, 0);
		}
	}
private:
	std::string mName;
	MaterialDataType mType;
	T mValue;
};

// layout
class MaterialLayout
{
public:
	MaterialLayout() {}
	MaterialLayout(std::initializer_list<std::shared_ptr<MaterialElementBase>> elements): m_Elements(elements){}
	const std::vector<std::shared_ptr<MaterialElementBase>>& GetElements() const { return m_Elements; }

	std::vector<std::shared_ptr<MaterialElementBase>>::iterator begin() { return m_Elements.begin(); }
	std::vector<std::shared_ptr<MaterialElementBase>>::iterator end() { return m_Elements.end(); }
	std::vector<std::shared_ptr<MaterialElementBase>>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<std::shared_ptr<MaterialElementBase>>::const_iterator end() const { return m_Elements.end(); }
private:
	std::vector<std::shared_ptr<MaterialElementBase>> m_Elements;
};

class Material
{
public:
	Material(){}
	~Material(){}

	void SetShader(std::shared_ptr<Shader> &shader) {
		mShader = shader;
	}

	std::shared_ptr<Shader> GetShader() const
	{
		return mShader;
	}

	// 绘制 Ui界面
	void drawUi();

private:
	// 着色器
	std::shared_ptr<Shader> mShader;
	// layout
	MaterialLayout m_Layout;
};