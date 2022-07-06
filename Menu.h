#pragma once
#include "imgui.h"
#include "Renderer.h"

class Menu
{
private:
	void ManageMenuOpacity();

	void AimbotTab();
	void VisualsTab();
	void SettingsTab();
	void DebugTab();

	bool AddCheckBox(const char* label, bool* value, ImColor* color = nullptr);
	void AddSliderInt(const char* label, int* value, const int min, const int max, const char* format = "%d");
	void AddSliderFloat(const char* label, float* value, const float min, const float max, const char* format = "%.1f");
	bool AddButton(const char* label);
	bool AddInputText(const char* label, char* buf, size_t buf_size, const char* hint = nullptr, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = 0, void* user_data = nullptr);
	void AddDummy(const ImVec2 size = ImGui::GetItemRectSize());

	void BeginTab() { ImGui::SetCursorPos(checkBoxPad); }
	void EndTab() { checkBoxPad = { 124, 24 }; itemCount = 1; }

	bool BeginGroup(const char* label, const ImVec2 pos = ImVec2(0, 0), const ImVec2 size = ImVec2(0, 0));
	void EndGroup();

	int alpha = 0;
	bool shouldSetCursor = true;
	int backupItemCount = 0;
	ImVec2 menuSize = { 660.f, 560.f };
	ImVec2 menuPos = { 660.f, 560.f };
	ImVec2 workSpace[2];

	int itemCount = 1;
	ImVec2 checkBoxPad = { 124, 24 };

public:
	struct DragEvent_s
	{
		bool wasDragging = false;
		bool shouldRecalcDelta = false;
	};

	static void RenderMenuAccentOverlay(const BoundingBox& bb);
	static bool IsMouseHeld();
	static bool IsMouseClicked();
	static bool IsKeyHeld(DWORD key);
	static bool IsKeyClicked(DWORD key);
	static void HandleDragEvent(BoundingBox& item, DragEvent_s& staticData);
	static Menu* GetContext();
	void Render();
	Menu() {};
};

