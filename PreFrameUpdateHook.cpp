#include "VMTHooking.h"
#include "Engine.h"
#include "Globals.h"
#include "Visuals.h"
#include "EntityPrediction.h"
#include "Cfg.h"
#include "Misc.h"
#include "Menu.h"
#include "xorstr.hpp"
#include "InputActions.h"

int __fastcall HooksManager::PreFrameUpdate(void* pThis, void* EDX, float deltaTime)
{
	static auto oPreFrameUpdate = HooksManager::Get()->pPreFrameHook->GetOriginal<PreFrameUpdate_t>(Index::PRE_FRAME_UPDATE);
	auto result = oPreFrameUpdate(pThis, EDX, deltaTime);

	if (auto pInput = BorderInputNode::GetInstance(); IsValidPtr(pInput) && IsValidPtr(pInput->m_pMouse))
	{
		if (IsValidPtr(pInput->m_pMouse->m_pDevice) && !pInput->m_pMouse->m_pDevice->m_CursorMode)
		{
			//FIX: Load last saved angles to prevent flip after closing menu
			pInput->m_pMouse->m_pDevice->m_UIOwnsInput = G::isMenuVisible;
			pInput->m_pMouse->m_pDevice->m_UseRawMouseInput = G::isMenuVisible;
		}
	}

	auto pDxRenderer = DxRenderer::GetInstance(); 
	if (!IsValidPtr(pDxRenderer)) return result;
	auto pScreen = pDxRenderer->m_pScreen;
	if (!IsValidPtr(pScreen)) return result;

	G::screenSize = { float(pScreen->m_Width), float(pScreen->m_Height) };
	G::screenCenter = { G::screenSize.x * .5f, G::screenSize.y * .5f };
	G::viewPos2D = G::screenCenter;

	auto pGameRenderer = GameRenderer::GetInstance();
	if (!IsValidPtr(pGameRenderer) || !IsValidPtr(pGameRenderer->m_pRenderView)) return result;
	G::viewPos = (Vector)&pGameRenderer->m_pRenderView->m_ViewInverse._41;

	auto pManager = PlayerManager::GetInstance(); 
	if (!IsValidPtr(pManager)) return result;
	auto pLocal = pManager->GetLocalPlayer();
	if (!IsValidPtr(pLocal) || !IsValidPtr(pLocal->GetSoldierEntity()) || !pLocal->GetSoldierEntity()->IsAlive()) 
		return result;

	pLocal->GetCurrentWeaponData(&PreUpdate::weaponData);

	Vector aimPoint = ZERO_VECTOR;
	auto& d = PreUpdate::preUpdatePlayersData;
	if (!IsValidPtr(d.pBestTarget)) return result;
	
	if (auto pTargetSoldier = d.pBestTarget->GetSoldierEntity(); IsValidPtr(pTargetSoldier))
	{
		if (!pTargetSoldier->IsAlive()) return result;
		if (!IsValidPtr(pTargetSoldier->m_pRagdollComponent) || !pTargetSoldier->m_pRagdollComponent->GetBone(UpdatePoseResultData::Head, aimPoint))
		{ 
			if (auto pVehicle = d.pBestTarget->GetVehicleEntity(); d.pBestTarget->InVehicle() && IsValidPtr(pVehicle))
			{
				Visuals::BoundingBox3D aabb3D;
				Visuals::GetEntityAABB(pVehicle, &aabb3D);
				aimPoint = aabb3D.GetCenter();
			}
		}
	}

	if (aimPoint == ZERO_VECTOR) return result; 
	
	PreUpdate::isPredicted = Prediction::GetPredictedAimPoint(
		pLocal, d.pBestTarget, aimPoint, &PreUpdate::predictionData, d.pMyMissile, &PreUpdate::weaponData);

	InputActions::Get()->HandleInput(
		PreUpdate::predictionData.hitPos, pLocal, PreUpdate::weaponData, aimPoint, d.pMyMissile);

	return result;
}