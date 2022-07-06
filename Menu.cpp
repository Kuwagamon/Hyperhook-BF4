#include "stdafx.h"
#include "Menu.h"
#include "MenuBackground.h"
#include "Globals.h"
#include "xorstr.hpp"
#include "Cfg.h"
#include "Engine.h"
#include <D3DX11.h>
#include <D3D11.h>
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DX11.lib")
#include <array>

bool exitRn = false;

void Exit()
{
	static int alpha = 0;
	static bool reverse = true;
	if (reverse)
	{
		if (alpha < 255) alpha += 5;
		else
		{
			alpha = 255; reverse = false;
			G::isMenuVisible = false;
			Cfg::ESP::watermark = false;
			Cfg::ESP::enable = false;
			Cfg::AimBot::enable = false;
			Cfg::ESP::Radar::enable = false;
		}
	}
	else
	{
		if (alpha > 0) alpha -= 5;
		else alpha = 0;
	}
	if (alpha > 0)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled({ 0, 0 }, G::screenSize, ImColor::Black(alpha));
		ImGui::PushFont(DX::Verdana48);

		auto size = ImGui::CalcTextSize(xorstr_("SEE YOU SOON :)"));
		ImVec2 pos = { G::screenCenter.x - (size.x * .5f), G::screenCenter.y - (size.y * .5f) };

		ImGui::GetOverlayDrawList()->AddText(
			pos,
			ImColor::White(alpha),
			xorstr_("SEE YOU SOON :)"));
		ImGui::PopFont();
	}

	if (alpha == 0) G::shouldExit = true;
}

void Menu::HandleDragEvent(BoundingBox& item, DragEvent_s& staticData)
{
	auto cursorPos = ImGui::GetMousePos();
	const auto size = item.GetSize();

	if (ImGui::IsMouseHoveringRect(item.GetMin(), item.GetMax(), false) && IsMouseHeld() && G::isMenuVisible)
		staticData.wasDragging = true;

	if (staticData.wasDragging && IsMouseHeld() && G::isMenuVisible)
	{
		static Vector2D delta = { (cursorPos.x - item.left) , (cursorPos.y - item.top) };
		if (staticData.shouldRecalcDelta)
		{
			delta = { (cursorPos.x - item.left) , (cursorPos.y - item.top) };
			staticData.shouldRecalcDelta = false;
		}
		item.left = cursorPos.x - delta.x;
		item.top = cursorPos.y - delta.y;
		item.right = item.left + size.x;
		item.bot = item.top + size.y;
	}

	if (staticData.wasDragging && !IsMouseHeld())
	{
		staticData.wasDragging = false;
		staticData.shouldRecalcDelta = true;
	}
}

void Menu::RenderMenuAccentOverlay(const BoundingBox& bb)
{
	const auto& winPos = bb.GetMin();
	const auto& winSize = bb.GetSize();
	ImGui::GetBackgroundDrawList()->AddRect(
		{ winPos.x - 1, winPos.y - 1 },
		{ winPos.x + winSize.x + 1, winPos.y + winSize.y + 1 },
		ImColor(1, 1, 1));
	ImGui::GetBackgroundDrawList()->AddRect(
		{ winPos.x - 3, winPos.y - 3 },
		{ winPos.x + winSize.x + 3, winPos.y + winSize.y + 3 },
		ImColor(40, 40, 40), 0.f, 15, 3.f);
	ImGui::GetBackgroundDrawList()->AddRect(
		{ winPos.x - 5, winPos.y - 5 },
		{ winPos.x + winSize.x + 5, winPos.y + winSize.y + 5 },
		ImColor(60, 60, 60));
	ImGui::GetBackgroundDrawList()->AddRect(
		{ winPos.x - 6, winPos.y - 6 },
		{ winPos.x + winSize.x + 6, winPos.y + winSize.y + 6 },
		ImColor(1, 1, 1));

	ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(
		{ winPos.x, winPos.y },
		{ winPos.x + (winSize.x * 0.5f), winPos.y + 3 },
		ImColor(55, 177, 218), ImColor(201, 84, 192),
		ImColor(201, 84, 192), ImColor(55, 177, 218));
	ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(
		{ winPos.x + (winSize.x * 0.5f), winPos.y },
		{ winPos.x + winSize.x, winPos.y + 3 },
		ImColor(201, 84, 192), ImColor(204, 227, 54),
		ImColor(204, 227, 54), ImColor(201, 84, 192));

	ImGui::GetBackgroundDrawList()->AddLine(
		{ winPos.x, winPos.y + 3 }, { winPos.x + winSize.x, winPos.y + 3 },
		ImColor(1,1,1));
}

bool Menu::IsMouseHeld()
{
	return (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
}

bool Menu::IsKeyHeld(DWORD key)
{
	return (GetAsyncKeyState(key) & 0x8000);
}

bool Menu::IsMouseClicked()
{
	bool isHeld = IsMouseHeld();
	static int tick = 0;
	static bool wasPressed = false;

	if (isHeld) wasPressed = true;

	tick++;

	if (tick >= 2) wasPressed = false;

	if (!isHeld)
	{
		tick = 0;
		wasPressed = false;
	}
	return wasPressed;
}

bool Menu::IsKeyClicked(DWORD key)
{
	bool isHeld = IsKeyHeld(key);
	static int tick = 0;
	static bool wasPressed = false;

	if (isHeld) wasPressed = true;

	tick++;

	if (tick >= 2) wasPressed = false;

	if (!isHeld)
	{
		tick = 0;
		wasPressed = false;
	}
	return wasPressed;
}

void Menu::ManageMenuOpacity()
{
	if (G::isMenuVisible)
	{
		if (alpha < 180)
			alpha += 10;
	}
	else
	{
		if (alpha > 0)
		alpha -= 10;
	}

	alpha = std::clamp(alpha, 0, 180);

	Renderer::DrawRectFilled({ 0,0 }, G::screenSize, ImColor::Black(alpha));
}

void Menu::AimbotTab()
{
	
	AddCheckBox(xorstr_("Enable##ab"), &Cfg::AimBot::enable);
	if (AddCheckBox(xorstr_("Show FOV##ab"), &Cfg::ESP::aimbotFov, &Cfg::ESP::fovColor)) ImGui::SetTooltip(xorstr_("Displays aimbot FOV circle."));
	if (AddCheckBox(xorstr_("Auto JDAM##ab"), &Cfg::AimBot::autoBombs)) ImGui::SetTooltip(xorstr_("Drop JDAM bomb automatically when min. dmg. is over 40%."));
	if (AddCheckBox(xorstr_("Jet speed ctrl##ab"), &Cfg::DBG::jetSpeedCtrl)) ImGui::SetTooltip(xorstr_("Keeps the speed at ~314 when holding SPACE or AUTOPILOTING."));
	
	AddSliderFloat(xorstr_("Trigger radius##ab"), &Cfg::AimBot::radius, 1.0f, G::screenCenter.y * 0.5f);
	if (ImGui::IsItemHovered()) ImGui::SetTooltip(xorstr_("Aimbot FOV in pixels."));

	AddSliderFloat(xorstr_("Smooth soldier##ab"), &Cfg::AimBot::smoothSoldier, 1.0f, 7.f);
	if (ImGui::IsItemHovered()) ImGui::SetTooltip(xorstr_("Smoothing aimbot when on foot."));

	AddSliderFloat(xorstr_("Smooth vehicle##ab"), &Cfg::AimBot::smoothVehicle, 1.0f, 7.f);
	if (ImGui::IsItemHovered()) ImGui::SetTooltip(xorstr_("Smoothing aimbot when in vehicle."));
}

void Menu::VisualsTab()
{
	AddCheckBox(xorstr_("Enable##esp"), &Cfg::ESP::enable, &Cfg::ESP::enemyColor);

	if (AddCheckBox(xorstr_("Players 3D box##esp"), &Cfg::ESP::use3DplayerBox, &Cfg::ESP::enemyColor))
		ImGui::SetTooltip(xorstr_("Shows players with 3D box mode."));

	if (AddCheckBox(xorstr_("Team##esp"), &Cfg::ESP::team, &Cfg::ESP::teamColor))
		ImGui::SetTooltip(xorstr_("ESP on teammates."));

	if (AddCheckBox(xorstr_("Lines##esp2"), &Cfg::ESP::lines, &Cfg::ESP::linesColor))
		ImGui::SetTooltip(xorstr_("2D lines from bottom center of the screen to players position."));

	if (AddCheckBox(xorstr_("Vehicles##esp"), &Cfg::ESP::vehicles, &Cfg::ESP::vehicleGroundColor))
		ImGui::SetTooltip(xorstr_("Shows vehicles with COLOR PICKER for ground units."));

	if (AddCheckBox(xorstr_("Vehicles type air##esp"), &Cfg::ESP::vehicles, &Cfg::ESP::vehicleAirColor))
		ImGui::SetTooltip(xorstr_("Shows vehicles with COLOR PICKER for air units."));

	if (AddCheckBox(xorstr_("Vehicles 3D box##esp"), &Cfg::ESP::use3DvehicleBox, nullptr))
		ImGui::SetTooltip(xorstr_("Shows vehicles with 3D box mode."));

	if (AddCheckBox(xorstr_("Vehicles center##esp"), &Cfg::ESP::vehicleCenter, nullptr))
		ImGui::SetTooltip(xorstr_("Visualisation of the center of the vehicle hitbox with diamond-like shape."));

	if (AddCheckBox(xorstr_("Vehicles Indicator##esp"), &Cfg::ESP::vehicleIndicator, nullptr))
		ImGui::SetTooltip(xorstr_("(Only when in vehicle) Shows 2D lines from bottom center of the screen to vehicles with corresponding COLOR."));

	if (AddCheckBox(xorstr_("Explosives##esp"), &Cfg::ESP::explosives, &Cfg::ESP::explosivesColor))
		ImGui::SetTooltip(xorstr_("Shows explosive charges from both teams."));

	if (AddCheckBox(xorstr_("Guided missile##esp"), &Cfg::ESP::ownMissile, &Cfg::ESP::missileColor))
		ImGui::SetTooltip(xorstr_("Shows local laser guided missile (helps when sniping flying vehicles from SRAW)"));

	if (AddCheckBox(xorstr_("Prediction##esp"), &Cfg::ESP::prediction, &Cfg::ESP::predictionCrossColor))
		ImGui::SetTooltip(xorstr_("Shows external crosshair where you have to aim to hit your target. COLOR PICKER for crosshair."));

	if (AddCheckBox(xorstr_("Override color##esp"), &Cfg::ESP::prediction, &Cfg::ESP::predictionCrossOverrideColor))
		ImGui::SetTooltip(xorstr_("Overrides prediction crosshair color to specified one when your crosshair is in prediction crosshair range"));

	if (AddCheckBox(xorstr_("Impact data##esp"), &Cfg::ESP::predictionImpactData, &Cfg::ESP::predictionDataColor))
		ImGui::SetTooltip(xorstr_("Shows additional information about your bullet, target and distance."));

	if (AddCheckBox(xorstr_("Bomb impact##esp"), &Cfg::ESP::predictionBombImpact, nullptr))
		ImGui::SetTooltip(xorstr_("Shows local JDAM bomb impact position."));

	if (AddCheckBox(xorstr_("Radar enable##esp"), &Cfg::ESP::Radar::enable, &Cfg::ESP::Radar::soldierColor))
		ImGui::SetTooltip(xorstr_("Shows external radar."));
	if (AddCheckBox(xorstr_("Radar only in vehicles##esp"), &Cfg::ESP::Radar::onlyInVehicle))
		ImGui::SetTooltip(xorstr_("Shows radar only when in vehicle."));
	if (AddCheckBox(xorstr_("Radar show vehicles##esp"), &Cfg::ESP::Radar::showVehicles))
		ImGui::SetTooltip(xorstr_("Shows vehicles in radar."));

	AddSliderFloat(xorstr_("Radar zoom"), &Cfg::ESP::Radar::zoom, 0.1f, 2.f);
	AddSliderInt(xorstr_("Radar radius"), &Cfg::ESP::Radar::radius, 50, 200);
	AddSliderInt(xorstr_("Radar icon scale"), &Cfg::ESP::Radar::iconScale, 16, 64);

	if (AddCheckBox(xorstr_("Spectators"), &Cfg::DBG::spectators))
		ImGui::SetTooltip(xorstr_("Shows current spectators ont the server. (They may or may not watching you)"));

	if (AddCheckBox(xorstr_("Vehicle cross"), &Cfg::DBG::vehicleCross))
		ImGui::SetTooltip(xorstr_("Shows external vehicle crosshair with red circle shape."));

	AddSliderInt(xorstr_("Pred. sim. iter."), &Cfg::ESP::_internalCurveIterationCount, 0, 16);
	if (ImGui::IsItemHovered()) ImGui::SetTooltip(xorstr_("Determines the accuracy of the prediction simulation (may eat up some FPS, set 0 to use linear prediction only)."));

	AddSliderFloat(xorstr_("Pred. sim. time"), &Cfg::ESP::_internalCurvePredTimeMultiplier, 1.f, 100.f, xorstr_("%.0f%%"));
	if (ImGui::IsItemHovered()) ImGui::SetTooltip(xorstr_("Specifies the maximum time span of the simulation (lower that if prediction gives you false results)."));
	
}

void Menu::SettingsTab()
{
	AddCheckBox(xorstr_("Show tooltips##set"), &ImGui::enableToolTip);
	if (AddCheckBox(xorstr_("Debug output##set"), &Cfg::DBG::debugOutput))
		ImGui::SetTooltip(xorstr_("Shows some additional infos about weapon, prediction, velocity, etc..."));

#ifdef _DEBUG
	AddCheckBox(xorstr_("Debug Entities##set"), &Cfg::DBG::debugEntities); //hide later
#endif
	AddCheckBox(xorstr_("Watermark##set"), &Cfg::DBG::watermark);

	AddDummy();

	ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - (checkBoxPad.x * 4.f));
	AddInputText(xorstr_("Set cutom name"), Cfg::DBG::spoofedName, 16, Cfg::DBG::_internalName);
	if (ImGui::IsItemHovered()) ImGui::SetTooltip(xorstr_("Change your name locally to specified one so you can stream/record in peace."));

	Cfg::DBG::_internalSpoof = AddButton(xorstr_("Spoof name"));
	Cfg::DBG::_internalRestore = AddButton(xorstr_("Restore name"));

	AddDummy();

	if (AddButton(xorstr_("Save config"))) F::pConfig->Write();
	if (AddButton(xorstr_("Load config"))) F::pConfig->Read();

	auto size = ImGui::GetItemRectSize();
	AddDummy({ size.x, size.y * 5 });

	if (AddButton(xorstr_("Unload DLL##set"))) exitRn = true;
	if (ImGui::IsItemHovered()) ImGui::SetTooltip(xorstr_("Exit cheat."));

	//I was testing some idea to display every player on the list and select THAT ONE and made him rage quit.
	//abandoned it long ago so maybe you will be able to to that :)

	/*itemCount++;
	ImGui::SetCursorPos(ImVec2(checkBoxPad.x, checkBoxPad.y * itemCount));

	static std::string preview = "";
	if (ImGui::BeginCombo(xorstr_("Player List"), preview.c_str()))
	{
		if (auto pManager = PlayerManager::GetInstance(); IsValidPtr(pManager) && !Cfg::ESP::_internalPlayerIDs.empty())
		{
			int i = 999;
			static bool items[70];
			Cfg::ESP::_internalSelectedPlayerIDs.resize(Cfg::ESP::_internalPlayerIDs.size(), 0);
			for (auto& it : Cfg::ESP::_internalPlayerIDs)
			{
				std::string label = "[";
				label += std::to_string(it).c_str();
				label += "] ";
				label += pManager->GetPlayerById(it)->m_Name;
				ImGui::Selectable(label.c_str(), &items[i], ImGuiSelectableFlags_DontClosePopups);
				if (items[i]) Cfg::ESP::_internalSelectedPlayerIDs[i] = it;
				else Cfg::ESP::_internalSelectedPlayerIDs[i] = 999;
				i++;
			}

			preview = "";
			for (auto& it : Cfg::ESP::_internalSelectedPlayerIDs)
			{
				if (it != 999)
				{
					preview += pManager->GetPlayerById(it)->m_Name;
					preview += ", ";
				}
			}
		}
	}
	ImGui::EndCombo();*/
}

void Menu::DebugTab()
{
	
	
}

bool Menu::AddCheckBox(const char* label, bool* value, ImColor* color)
{
	itemCount++;

	if (color)
	{
		auto flags = 
			ImGuiColorEditFlags_NoOptions
			| ImGuiColorEditFlags_AlphaBar
			| ImGuiColorEditFlags_NoInputs 
			| ImGuiColorEditFlags_NoLabel 
			| ImGuiColorEditFlags_PickerHueWheel 
			| ImGuiColorEditFlags_NoTooltip
			| ImGuiColorEditFlags_NoSidePreview;

		if (shouldSetCursor)
			ImGui::SetCursorPos({ checkBoxPad.x, checkBoxPad.y * itemCount });
		std::string hash = xorstr_("Color Picker##");

		bool isHovered = false;

		ImGui::ColorEdit4(hash.append(label).c_str(), &color->Value.x, flags);
		isHovered = ImGui::IsItemHovered();

		*color = ImGui::ColorConvertFloat4ToU32(*color);

		ImGui::SameLine(0, 10);

		ImGui::Checkbox(label, value);
		isHovered = ImGui::IsItemHovered();

		return isHovered;
	}
	if (shouldSetCursor)
		ImGui::SetCursorPos({checkBoxPad.x + 28, checkBoxPad.y * itemCount});

	ImGui::Checkbox(label, value);

	return ImGui::IsItemHovered(); 
}

void Menu::AddSliderInt(const char* label, int* value, const int min, const int max, const char* format)
{
	itemCount++;
	if (shouldSetCursor) 
	{
		ImGui::SetCursorPos({ checkBoxPad.x, checkBoxPad.y * itemCount });
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - (checkBoxPad.x * 2.f));
	}
	ImGui::SliderInt(label, value, min, max, format);
}

void Menu::AddSliderFloat(const char* label, float* value, const float min, const float max, const char* format)
{
	itemCount++;
	if (shouldSetCursor)
	{
		ImGui::SetCursorPos({ checkBoxPad.x, checkBoxPad.y * itemCount });
		ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - (checkBoxPad.x * 2.f));
	}
	ImGui::SliderFloat(label, value, min, max, format);
}

bool Menu::AddButton(const char* label)
{
	itemCount++; 
	if (shouldSetCursor)
		ImGui::SetCursorPos({ checkBoxPad.x, checkBoxPad.y * itemCount });
	return ImGui::Button(label);
}

bool Menu::AddInputText(const char* label, char* buf, size_t buf_size, const char* hint, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
	itemCount++;
	if (shouldSetCursor)
		ImGui::SetCursorPos(ImVec2(checkBoxPad.x, checkBoxPad.y * itemCount));
	if (hint) return ImGui::InputTextWithHint(label, hint, buf, buf_size, flags, callback, user_data);
	return ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
}

void Menu::AddDummy(const ImVec2 size)
{
	itemCount++;
	if (shouldSetCursor)
		ImGui::SetCursorPos(ImVec2(checkBoxPad.x, checkBoxPad.y * itemCount));
	ImGui::Dummy(size);
}

bool Menu::BeginGroup(const char* label, const ImVec2 pos, const ImVec2 size)
{
	//shouldSetCursor = false;
	//ImGui::SetCursorPos({ checkBoxPad.x, ImGui::GetCursorPosY() });
	checkBoxPad.x = 24.f;
	backupItemCount = itemCount;
	itemCount = 0;
	BoundingBox bb =
	{
		pos.x == 0 ? checkBoxPad.x : pos.x,
		pos.y == 0 ? ImGui::GetCursorPosY() : pos.y,
		size.x == 0 ? (workSpace[1].x - workSpace[0].x) * .5f : pos.x == 0 ? checkBoxPad.x : pos.x + size.x,
		size.y == 0 ? 200 : size.y
	};
	auto result = ImGui::BeginChild(label, { 0, 0 }, false);
	RenderMenuAccentOverlay(bb);
	return result;
}

void Menu::EndGroup()
{
	ImGui::EndChild();
	shouldSetCursor = true;
	checkBoxPad.x = 124.f;
	itemCount += backupItemCount;
}

Menu* Menu::GetContext()
{
	static std::unique_ptr<Menu> ctx = std::make_unique<Menu>();
	return ctx.get();
}

void Menu::Render()
{
	auto& io = ImGui::GetIO();
	if (auto pInput = BorderInputNode::GetInstance(); IsValidPtr(pInput))
	{
		if (IsValidPtr(pInput->m_pMouse) && IsValidPtr(pInput->m_pMouse->m_pDevice) && !pInput->m_pMouse->m_pDevice->m_CursorMode)
			io.MouseDrawCursor = G::isMenuVisible;
	}

	ManageMenuOpacity();
	
	if (exitRn) Exit();

	if (!G::isMenuVisible) return;

	static int tab = 0;
	static int maxTabs = 3;
	auto& style = ImGui::GetStyle();
	style.AntiAliasedFill = false;
	style.AntiAliasedLines = false;
	ImGui::SetNextWindowSize(menuSize);
	ImGui::SetNextWindowBgAlpha(1.f);
	ImGui::Begin(xorstr_("HyperHook##"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	const auto& winPos = ImGui::GetWindowPos(); 
	const auto& winSize = ImGui::GetWindowSize();
	{
		menuPos = winPos;
		auto* pWindow = ImGui::GetWindowDrawList();
		static ID3D11ShaderResourceView* pBackGround = nullptr;
		static ID3D11ShaderResourceView* pLogo = nullptr;
		static std::array<ID3D11ShaderResourceView*, 3> pIconsTx;
		static bool doOnce = true;
		if (doOnce && DX::pDevice)
		{
			doOnce = false;
			D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &MenuImages::Background, sizeof(MenuImages::Background), NULL, NULL, &pBackGround, NULL);
			D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &MenuImages::Aimbot, sizeof(MenuImages::Aimbot), NULL, NULL, &pIconsTx[0], NULL);
			D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &MenuImages::Visuals, sizeof(MenuImages::Visuals), NULL, NULL, &pIconsTx[1], NULL);
			D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &MenuImages::Settings, sizeof(MenuImages::Settings), NULL, NULL, &pIconsTx[2], NULL);
			D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &MenuImages::Logo, sizeof(MenuImages::Logo), NULL, NULL, &pLogo, NULL);
		}

		pWindow->AddImage((void*)pBackGround,
			winPos, { winPos.x + (winSize.x * 2.f), winPos.y + (winSize.y * 2.f) }, { 0, 0 }, { 1, 1 });
		const ImVec2 workCenter =
		{
			(winPos.x + 100) + ((winSize.x - 100) * 0.5f),
			(winPos.y) + (winSize.y * 0.5f)
		};

		static constexpr float logoScale = 1.2f;
		const ImVec2 logoPos[2] =
		{
			{ workCenter.x - (192 * 1.2f), workCenter.y - (64 * 1.2f) },
			{ workCenter.x + (192 * 1.2f), workCenter.y + (64 * 1.2f) }
		};
		pWindow->AddImage(pLogo, logoPos[0], logoPos[1], { 0, 0 }, { 1, 1 }, ImColor(255, 255, 255, 80));

		pWindow->AddRectFilledMultiColor(
			{ winPos.x, winPos.y },
			{ winPos.x + (winSize.x * 0.5f), winPos.y + 3 },
			ImColor(55, 177, 218), ImColor(201, 84, 192), 
			ImColor(201, 84, 192), ImColor(55, 177, 218));
		pWindow->AddRectFilledMultiColor(
			{ winPos.x + (winSize.x * 0.5f), winPos.y },
			{ winPos.x + winSize.x, winPos.y + 3 },
			ImColor(201, 84, 192), ImColor(204, 227, 54),
			ImColor(204, 227, 54), ImColor(201, 84, 192));

		const ImVec2 iconCenter = { winPos.x + 50, winPos.y + 50 };
		static const ImVec2 iconSize = { 64, 64 };
		static const float iconOffset = winSize.y / 4.f;
		static const int iconOffsetTop = 96; 

#pragma region Lines

		const auto dst = tab * iconOffset;
		static auto delta = tab * iconOffset;
		static auto prevTab = tab;
		if (prevTab != tab)
		{
			delta = (prevTab * iconOffset) - (tab * iconOffset);
			prevTab = tab;
		}

		auto FPS = ImGui::GetIO().Framerate;
		auto scaleWithFPS = 0.041f - ((FPS * 0.041f) / 200.f);

		if (abs(delta - dst + 0.1f) > 0.09f)
			delta -= delta * (0.041f + scaleWithFPS);

		delta = std::clamp(delta, -(maxTabs - 1) * iconOffset, (maxTabs - 1) * iconOffset);

		ImVec2 upperPoint = { winPos.x + 100, winPos.y + (dst + delta) + iconOffsetTop };
		ImVec2 lowerPoint = { winPos.x, winPos.y + (dst + delta) + (iconOffsetTop * 2) };

		pWindow->AddRectFilled(
			{ winPos.x, winPos.y + 4 },
			upperPoint,
			ImColor(16, 16, 16));

		pWindow->AddLine(
			{ upperPoint.x, winPos.y + 4 },
			{ upperPoint.x, upperPoint.y + 1 },
			ImColor(1, 1, 1));

		pWindow->AddLine(
			{ upperPoint.x + 1, winPos.y + 4 },
			{ upperPoint.x + 1, upperPoint.y + 2 },
			ImColor(60, 60, 60));

		pWindow->AddLine(
			{ winPos.x, upperPoint.y },
			upperPoint,
			ImColor(1, 1, 1));

		pWindow->AddLine(
			{ winPos.x, upperPoint.y + 1 },
			{ upperPoint.x + 1, upperPoint.y + 1 },
			ImColor(60, 60, 60));

		pWindow->AddRectFilled(
			{ winPos.x, lowerPoint.y },
			{ upperPoint.x, winPos.y + winSize.y },
			ImColor(16, 16, 16));

		pWindow->AddLine(
			{ upperPoint.x, lowerPoint.y - 1 },
			{ upperPoint.x, winPos.y + winSize.y },
			ImColor(1, 1, 1));

		pWindow->AddLine(
			{ upperPoint.x + 1, lowerPoint.y - 2 },
			{ upperPoint.x + 1, winPos.y + winSize.y },
			ImColor(60, 60, 60));

		pWindow->AddLine(
			{ winPos.x, lowerPoint.y - 1 },
			{ upperPoint.x, lowerPoint.y - 1 },
			ImColor(1, 1, 1));

		pWindow->AddLine(
			{ winPos.x, lowerPoint.y - 2 },
			{ upperPoint.x + 1, lowerPoint.y - 2 },
			ImColor(60, 60, 60));

#pragma endregion Lines

		auto AddTab = [&](ImTextureID id, const ImVec2& pos, int iter) -> bool
		{
			pWindow->AddImage(id, { pos.x - 32, pos.y - 32 }, { pos.x + 32, pos.y + 32 }, { 0, 0 }, { 1, 1 },
				tab == iter ?
				ImColor(200, 200, 200, 255) :
				ImGui::IsMouseHoveringRect({ pos.x - 32, pos.y - 32 }, { pos.x + 32, pos.y + 32 }) ?
				ImColor(180, 180, 180, 180) :
				ImColor(120, 120, 120, 120));

			std::string hash = xorstr_("tab_button##");
			ImGui::SetCursorPos({ 50 - 32, 50 + (iter * iconOffset) + 64 });
			return ImGui::InvisibleButton(hash.append(std::to_string(iter)).c_str(), iconSize);
		};

		for (int i = 0; i < pIconsTx.size(); i++)
		{
			//96
			if (AddTab(pIconsTx[i], { iconCenter.x, iconCenter.y + (iconOffset * i) + iconOffsetTop }, i))
				tab = i;
		}

		auto* pDraw = ImGui::GetBackgroundDrawList();
		pDraw->AddRect(
			{ winPos.x - 1, winPos.y - 1 },
			{ winPos.x + winSize.x + 1, winPos.y + winSize.y + 1 },
			ImColor(60, 60, 60));
		pDraw->AddRect(
			{ winPos.x - 3, winPos.y - 3 },
			{ winPos.x + winSize.x + 3, winPos.y + winSize.y + 3 },
			ImColor(40, 40, 40), 0.f, 15, 3.f);
		pDraw->AddRect(
			{ winPos.x - 5, winPos.y - 5 },
			{ winPos.x + winSize.x + 5, winPos.y + winSize.y + 5 },
			ImColor(60, 60, 60));
		pDraw->AddRect(
			{ winPos.x - 6, winPos.y - 6 },
			{ winPos.x + winSize.x + 6, winPos.y + winSize.y + 6 },
			ImColor(1, 1, 1));

		workSpace[0] = ImVec2(winPos.x + 100, winPos.y);
		workSpace[1] = ImVec2(winPos.x + winSize.x, winPos.y + winSize.y);

		style.AntiAliasedFill = true;
		style.AntiAliasedLines = true;

		BeginTab();
		switch (tab)
		{
			case 0: AimbotTab(); break;
			case 1: VisualsTab(); break;
			case 2: SettingsTab(); break;
			case 3: DebugTab(); break;
			default: AimbotTab();
		}
		EndTab();
	}
	ImGui::End();
}
