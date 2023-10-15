#pragma once

#include <string>

namespace ImGui {
    IMGUI_API bool  ButtonNoFrame(const char* label, const ImVec2& size = ImVec2(0, 0));   // button without frame
    IMGUI_API bool  InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
}