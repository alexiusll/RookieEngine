#include "stdafx.h"

#include "shader.h"
#include "Material.h"

void Material::updateShader() const
{
	for (auto& elements : m_Layout->GetElements()) {
		auto value = elements->getValue();
	}
}

void Material::drawUi()
{
	// ���� ������UI
	for (auto &elements : m_Layout->GetElements()) {
		elements->drawUi();
	}
}
