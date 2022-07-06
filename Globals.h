#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include <thread>
#include <map>
#include "imgui.h"
#include "IniParser.h"
#include "Visuals.h"
#include <D3DX11.h>

//#define GUI_TEST

namespace G
{
	extern bool isMenuVisible;
	extern bool shouldExit;
	extern ImVec2 screenSize;
	extern ImVec2 screenCenter;
	extern D3DXVECTOR2 viewPos2D;
	extern D3DXVECTOR3 viewPos;
	extern bool targetLock;
	extern HINSTANCE hInst;
}

namespace DX
{
	extern IDXGISwapChain* pSwapChain;
	extern ID3D11Device* pDevice;

	extern ImFont* Verdana8;
	extern ImFont* Verdana12;
	extern ImFont* Verdana18;
	extern ImFont* Verdana24;
	extern ImFont* Verdana48;

	extern ImFont* Digital10;
	extern ImFont* Digital12;
	extern ImFont* Digital24;
	extern ImFont* Digital36;
}

namespace F
{
	extern std::unique_ptr<Visuals> pVisuals;
	extern std::unique_ptr<IniParser> pConfig;
}

struct UpdateData_s
{
	ClientPlayer* pBestTarget = nullptr;
	VeniceClientMissileEntity* pMyMissile = nullptr;
	Vector origin = {};
};

namespace PreUpdate
{
	extern UpdateData_s preUpdatePlayersData;
	extern PredictionData_s predictionData;
	extern WeaponData_s weaponData;
	 
	extern std::array<Vector, 8> points;
	extern bool visible;

	extern bool isValid;
	extern bool isPredicted;
}

namespace PlayerList
{
	extern std::array<ClientPlayer*, 70> list;
}