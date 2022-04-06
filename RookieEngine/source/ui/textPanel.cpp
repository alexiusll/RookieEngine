#include "stdafx.h"
#include "textPanel.h"

#include "imgui.h"

void TextPanel::render(Sample_Scene* scene)
{
	ImGui::Begin("TextPanel");
	ImGui::Text("This is some useful text.");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::ColorPicker3("Color", (float*)&scene->getPlane()->color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
	// ImGui::ColorEdit3("clear color", (float*)&color); // Edit 3 floats representing a color

	ImGui::End();

	ImGui::Begin("Another Window 2"); 
	ImGui::Text("Hello from another window!");
	ImGui::End();

	ImGui::Begin("Another Window 3");
	ImGui::Text("Hello from another window!");
	ImGui::End();
}
