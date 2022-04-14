#include "stdafx.h"
#include "textPanel.h"

#include "imgui.h"

void TextPanel::render()
{
	// ImGui::Begin("Properties");
	// ImGui::ColorPicker3("Color", (float*)&scene->getPlane()->color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
	// ImGui::ColorEdit3("clear color", (float*)&color); // Edit 3 floats representing a color
	// ImGui::End();

	//ImGui::Begin("Scene Hierarchy"); 
	//ImGui::Text("Hello from another window!");
	//ImGui::End();

	ImGui::ShowDemoWindow();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
