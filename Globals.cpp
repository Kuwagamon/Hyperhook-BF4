#include "stdafx.h"
#include "Globals.h"
#include "xorstr.hpp"

//Globals

namespace G
{
	bool			isMenuVisible	= false;
	bool			shouldExit		= false;
	ImVec2			screenSize		= { -1, -1 };
	ImVec2			screenCenter	= { -1, -1 };
	D3DXVECTOR2		viewPos2D		= { -1, -1 };
	D3DXVECTOR3		viewPos			= { -1, -1, -1 };
	bool			targetLock		= false;
	HINSTANCE		hInst			= NULL;
}

namespace DX
{
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11Device* pDevice = nullptr;

	ImFont* Verdana8  = nullptr;
	ImFont* Verdana12 = nullptr;
	ImFont* Verdana18 = nullptr;
	ImFont* Verdana24 = nullptr;
	ImFont* Verdana48 = nullptr;

	ImFont* Digital10 = nullptr;
	ImFont* Digital12 = nullptr;
	ImFont* Digital24 = nullptr;
	ImFont* Digital36 = nullptr;
}

namespace F
{
	std::unique_ptr<Visuals> pVisuals;
	std::unique_ptr<IniParser> pConfig;
}

namespace PreUpdate
{
	UpdateData_s preUpdatePlayersData;
	PredictionData_s predictionData;
	WeaponData_s weaponData;

	std::array<Vector, 8> points;
	bool visible;

	bool isValid;
	bool isPredicted;
}

namespace PlayerList
{
	std::array<ClientPlayer*, 70> list;
}