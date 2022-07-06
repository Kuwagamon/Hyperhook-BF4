#include "Visuals.h"
#include "Globals.h"
#include "Misc.h"
#include "Cfg.h"
#include "xorstr.hpp"
#include "Menu.h"
#include "MenuBackground.h"
#include "EntityPrediction.h"
#include "InputActions.h"
#include "VMTHooking.h"

//#define AIMPOINT_DBG

bool targetLock = false;

struct ClassInfos_s
{
	ClassInfo* MissileEntity = nullptr;
	ClassInfo* ExplosionEntity = nullptr;
	ClassInfo* VehicleEntity = nullptr;
	ClassInfo* WarningComponent = nullptr;
}ClassInfos;

Vector Translation(const D3DXMATRIX& matrix)
{
	return Vector(matrix._41, matrix._42, matrix._43);
};

Visuals::Visuals()
{
	ClassInfos.MissileEntity = FindClassInfo(xorstr_("VeniceClientMissileEntity"));
	ClassInfos.ExplosionEntity = FindClassInfo(xorstr_("ClientExplosionPackEntity"));
	ClassInfos.VehicleEntity = FindClassInfo(xorstr_("ClientVehicleEntity"));
	ClassInfos.WarningComponent = FindClassInfo(xorstr_("ClientWarningSystemComponent"));
}

bool Visuals::WorldToScreen(const Vector& origin, Vector& screen)
{
	auto* pRenderer = GameRenderer::GetInstance();
	if (!pRenderer) return false;

	auto* pRenderView = pRenderer->m_pRenderView;;
	if (!pRenderView) return false;

	auto* pDxRenderer = DxRenderer::GetInstance();
	if (!pDxRenderer) return false;

	auto* pScreen = pDxRenderer->m_pScreen;
	if (!pScreen) return false;

	float mX = static_cast<float>(pScreen->m_Width * 0.5f);
	float mY = static_cast<float>(pScreen->m_Height * 0.5f);

	D3DXMATRIX screenTransform = pRenderView->m_ViewProjection;

	float w =
		screenTransform(0, 3) * origin.x +
		screenTransform(1, 3) * origin.y +
		screenTransform(2, 3) * origin.z +
		screenTransform(3, 3);

	if (w < 0.0001f)
	{
		screen.z = w;

		return false;
	}

	float x =
		screenTransform(0, 0) * origin.x +
		screenTransform(1, 0) * origin.y +
		screenTransform(2, 0) * origin.z +
		screenTransform(3, 0);

	float y =
		screenTransform(0, 1) * origin.x +
		screenTransform(1, 1) * origin.y +
		screenTransform(2, 1) * origin.z +
		screenTransform(3, 1);

	screen.x = mX + mX * x / w;
	screen.y = mY - mY * y / w;
	screen.z = w;

	return true;
}

bool Visuals::WorldToScreen(const Vector& origin, Vector2D& screen)
{
	auto* pRenderer = GameRenderer::GetInstance();
	if (!pRenderer) return false;

	auto* pRenderView = pRenderer->m_pRenderView;;
	if (!pRenderView) return false;

	auto* pDxRenderer = DxRenderer::GetInstance();
	if (!pDxRenderer) return false;

	auto* pScreen = pDxRenderer->m_pScreen;
	if (!pScreen) return false;

	float mX = static_cast<float>(pScreen->m_Width * 0.5f);
	float mY = static_cast<float>(pScreen->m_Height * 0.5f);

	D3DXMATRIX screenTransform = pRenderView->m_ViewProjection;

	float w =
		screenTransform(0, 3) * origin.x +
		screenTransform(1, 3) * origin.y +
		screenTransform(2, 3) * origin.z +
		screenTransform(3, 3);

	if (w < 0.0001f) return false;

	float x =
		screenTransform(0, 0) * origin.x +
		screenTransform(1, 0) * origin.y +
		screenTransform(2, 0) * origin.z +
		screenTransform(3, 0);

	float y =
		screenTransform(0, 1) * origin.x +
		screenTransform(1, 1) * origin.y +
		screenTransform(2, 1) * origin.z +
		screenTransform(3, 1);

	screen.x = mX + mX * x / w;
	screen.y = mY - mY * y / w;

	return true;
}

bool Visuals::WorldToScreen(const Vector& origin, ImVec2& screen)
{
	D3DXMATRIXA16 viewProj = GameRenderer::GetInstance()->m_pRenderView->m_ViewProjection;

	float mX = DxRenderer::GetInstance()->m_pScreen->m_Width * 0.5f;
	float mY = DxRenderer::GetInstance()->m_pScreen->m_Height * 0.5f;

	float w =
		viewProj(0, 3) * origin.x +
		viewProj(1, 3) * origin.y +
		viewProj(2, 3) * origin.z +
		viewProj(3, 3);

	if (w < 0.65f)
	{
		//ScreenPos->z = w;
		return false;
	}

	float x =
		viewProj(0, 0) * origin.x +
		viewProj(1, 0) * origin.y +
		viewProj(2, 0) * origin.z +
		viewProj(3, 0);

	float y =
		viewProj(0, 1) * origin.x +
		viewProj(1, 1) * origin.y +
		viewProj(2, 1) * origin.z +
		viewProj(3, 1);

	screen.x = mX + mX * x / w;
	screen.y = mY - mY * y / w;
	//ScreenPos->z = w;

	return true;
}

bool Visuals::WorldToScreen(Vector& origin)
{
	D3DXMATRIXA16 viewProj = GameRenderer::GetInstance()->m_pRenderView->m_ViewProjection;

	float mX = DxRenderer::GetInstance()->m_pScreen->m_Width * 0.5f;
	float mY = DxRenderer::GetInstance()->m_pScreen->m_Height * 0.5f;

	float w =
		viewProj(0, 3) * origin.x +
		viewProj(1, 3) * origin.y +
		viewProj(2, 3) * origin.z +
		viewProj(3, 3);

	if (w < 0.65f)
	{
		//ScreenPos->z = w;
		return false;
	}

	float x =
		viewProj(0, 0) * origin.x +
		viewProj(1, 0) * origin.y +
		viewProj(2, 0) * origin.z +
		viewProj(3, 0);

	float y =
		viewProj(0, 1) * origin.x +
		viewProj(1, 1) * origin.y +
		viewProj(2, 1) * origin.z +
		viewProj(3, 1);

	origin.x = mX + mX * x / w;
	origin.y = mY - mY * y / w;
	//ScreenPos->z = w;

	return true;
}

bool Visuals::IsValidTime(ClientPlayer* pLocal)
{
	static bool hasSpawned = false;
	static bool isAlive = false;
	static auto time = ImGui::GetTime();

	auto Reset = [&]() -> void
	{
		hasSpawned = false;
		isAlive = false;
		time = ImGui::GetTime();
	};

	if (!IsValidPtr(pLocal)) { Reset();  return false; }

	auto pSoldier = pLocal->GetSoldierEntity();
	if (!IsValidPtr(pSoldier)) { Reset();  return false; }


	if (!pSoldier->IsAlive())
	{
		time = ImGui::GetTime();
		isAlive = false;
		hasSpawned = false;
		targetLock = false;
		return false;
	}
	else isAlive = true;

	if (isAlive && !hasSpawned)
	{
		hasSpawned = true;
		time = ImGui::GetTime();
	}

	if (hasSpawned && (ImGui::GetTime() - time >= 2.0))
	{
		isAlive = false;
		return true;
	}
	return false;
}

BoundingBox Visuals::GetEntityAABB(ClientControllableEntity* pEntity, BoundingBox3D* pTransformed3D)
{
	TransformAABBStruct TransAABB;
	D3DXMATRIX matrix;
	pEntity->GetTransform(&matrix);
	pEntity->GetAABB(&TransAABB);

	auto min = Vector(TransAABB.AABB.m_Min.x, TransAABB.AABB.m_Min.y, TransAABB.AABB.m_Min.z);
	auto max = Vector(TransAABB.AABB.m_Max.x, TransAABB.AABB.m_Max.y, TransAABB.AABB.m_Max.z);

	auto MultiplyMat = [](const Vector& vec, D3DXMATRIX* mat) -> Vector
	{
		return Vector(mat->_11 * vec.x + mat->_21 * vec.y + mat->_31 * vec.z,
			mat->_12 * vec.x + mat->_22 * vec.y + mat->_32 * vec.z,
			mat->_13 * vec.x + mat->_23 * vec.y + mat->_33 * vec.z);
	};

	Vector points[] =
	{
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector pointsTransformed[8] = {};
	auto pos = Vector(matrix._41, matrix._42, matrix._43);
	for (int i = 0; i < 8; i++)
		pointsTransformed[i] = pos + MultiplyMat(points[i], &matrix);

	if (pTransformed3D)
	{
		for (int i = 0; i < 8; i++)
			pTransformed3D->points.at(i) = pointsTransformed[i];
		pTransformed3D->min = pos + MultiplyMat(min, &matrix);
		pTransformed3D->max = pos + MultiplyMat(max, &matrix);
	}

	Vector screenPoints[8] = {};
	for (int i = 0; i < 8; i++)
	{
		if (!WorldToScreen(pointsTransformed[i], screenPoints[i]))
			return BoundingBox::Zero();
	}

	auto left = screenPoints[0].x;
	auto top = screenPoints[0].y;
	auto right = screenPoints[0].x;
	auto bottom = screenPoints[0].y;

	for (int i = 1; i < 8; i++)
	{
		if (left > screenPoints[i].x)
			left = screenPoints[i].x;
		if (top < screenPoints[i].y)
			top = screenPoints[i].y;
		if (right < screenPoints[i].x)
			right = screenPoints[i].x;
		if (bottom > screenPoints[i].y)
			bottom = screenPoints[i].y;
	}

	return BoundingBox(left, bottom, right, top);
}

void Visuals::RenderPlayerNames(ClientPlayer* pPlayer)
{
	if (!IsValidPtr(pPlayer)) return;

	//TODO

}

void Visuals::RenderPlayerCorneredRect(const BoundingBox& bbEntity, const ImColor& color)
{
	BoundingBox bb = bbEntity;

	float width = abs(bb.GetSize().x * 0.2f);
	float height = abs(bb.GetSize().x * 0.2f);

	if (bb.GetSize().x <= width) width = bb.GetSize().x * 0.2f;
	if (bb.GetSize().x <= height) height = bb.GetSize().x * 0.2f;

	bb.left = std::floorf(bbEntity.left);
	bb.top = std::floorf(bbEntity.top);
	bb.right = std::floorf(bbEntity.right);
	bb.bot = std::floorf(bbEntity.bot);

	ImColor cBG = ImColor::Black((int)(color.Value.w * 255));
	ImColor cFG = color;

	/*	2			3
		 ____	____
	1	|a		   b|	4
		|			|



	8	|			|	5
		|d___	___c|

		7			6
	*/

	// 1
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMin().x - 1, bb.GetMin().y),
		ImVec2(bb.GetMin().x + 1, bb.GetMin().y + height + 1),
		cBG);

	// 2
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMin().x - 1, bb.GetMin().y - 1),
		ImVec2(bb.GetMin().x + width + 1, bb.GetMin().y + 1),
		cBG);

	// 3
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMax().x - width - 1, bb.GetMin().y - 1),
		ImVec2(bb.GetMax().x + 1, bb.GetMin().y + 1),
		cBG);

	// 4
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMax().x - 1, bb.GetMin().y - 1),
		ImVec2(bb.GetMax().x + 1, bb.GetMin().y + height + 1),
		cBG);

	// 5
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMax().x - 1, bb.GetMax().y - height - 1),
		ImVec2(bb.GetMax().x + 1, bb.GetMax().y),
		cBG);

	// 6
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMax().x - width - 1, bb.GetMax().y - 1),
		ImVec2(bb.GetMax().x + 1, bb.GetMax().y + 1),
		cBG);

	// 7
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMin().x - 1, bb.GetMax().y - 1),
		ImVec2(bb.GetMin().x + width + 1, bb.GetMax().y + 1),
		cBG);

	// 8
	Renderer::DrawRectFilled(
		ImVec2(bb.GetMin().x - 1, bb.GetMax().y - height - 1),
		ImVec2(bb.GetMin().x + 1, bb.GetMax().y + 1),
		cBG);

	// a
	Renderer::DrawLine(bb.GetMin(), ImVec2(bb.GetMin().x + width, bb.GetMin().y), cFG);
	Renderer::DrawLine(bb.GetMin(), ImVec2(bb.GetMin().x, bb.GetMin().y + height), cFG);

	// b
	Renderer::DrawLine(ImVec2(bb.GetMax().x - width, bb.GetMin().y), bb.GetMaxTop(), cFG);
	Renderer::DrawLine(ImVec2(bb.GetMax().x - 1, bb.GetMin().y + height - 1), ImVec2(bb.GetMaxTop().x - 1, bb.GetMaxTop().y), cFG);

	// c
	Renderer::DrawLine(ImVec2(bb.GetMax().x - width, bb.GetMax().y - 1), ImVec2(bb.GetMax().x, bb.GetMax().y - 1), cFG);
	Renderer::DrawLine(ImVec2(bb.GetMax().x - 1, bb.GetMax().y - height), ImVec2(bb.GetMax().x - 1, bb.GetMax().y), cFG);

	// d
	Renderer::DrawLine(ImVec2(bb.GetMinBot().x, bb.GetMinBot().y - 1), ImVec2(bb.GetMin().x + width, bb.GetMax().y - 1), cFG);
	Renderer::DrawLine(ImVec2(bb.GetMin().x, bb.GetMax().y - height), bb.GetMinBot(), cFG);
}

void Visuals::RenderPlayerHealth(const BoundingBox& bbEntity)
{
	//TODO:
}

void Visuals::RenderExplosives(ClientGameContext* pCtx)
{
	if (!IsValidPtr(pCtx->m_pLevel) || !IsValidPtr(pCtx->m_pLevel->m_pGameWorld)) return;

	auto* pGameWorld = pCtx->m_pLevel->m_pGameWorld;
	if (!IsValidPtr(pGameWorld)) return;

	if (ClassInfos.MissileEntity)
	{
		EntityIterator<ClientExplosionEntity> explosives(pGameWorld, ClassInfos.ExplosionEntity);

		if (explosives.front())
		{
			do
			{
				if (auto* pExplosives = explosives.front()->getObject(); IsValidPtr(pExplosives))
				{
					BoundingBox3D explosivesAABB3D;
					GetEntityAABB((ClientControllableEntity*)pExplosives, &explosivesAABB3D);
					std::array<ImVec2, 8> points2D;

					bool valid = true;
					for (int i = 0; i < 8; i++)
					{
						if (!WorldToScreen(explosivesAABB3D.points[i], points2D[i]))
						{
							valid = false;
							break;
						}
					}
					if (valid) Renderer::DrawBox(points2D, Cfg::ESP::explosivesColor);

				}

			} while (explosives.next());
		}
	}
}

void Visuals::RenderDebugEntities(ClientGameContext* pCtx, VeniceClientMissileEntity* pMissile, ClientPlayer* pLocal, WeaponData_s* pVehWeaponData)
{
	if (!pCtx->m_pLevel || !pCtx->m_pLevel->m_pGameWorld) return;

	auto* pGameWorld = pCtx->m_pLevel->m_pGameWorld;
	if (!pGameWorld) return;

	if (ClassInfos.VehicleEntity)
	{
		EntityIterator<ClientVehicleEntity> vehicles(pGameWorld, ClassInfos.VehicleEntity);

		float closest = FLT_MAX;
		ClientVehicleEntity* pBestVehicle = nullptr;
		Vector bestAimPoint = ZERO_VECTOR;
		auto viewPos = G::viewPos;
		auto pVeh = pLocal->GetClientVehicleEntity();

		if (vehicles.front())
		{
			do
			{
				if (auto* pVehicles = vehicles.front()->getObject(); pVehicles)
				{
					if (pVeh && pVeh == pVehicles) continue;

					BoundingBox3D explosivesAABB3D;
					auto center = explosivesAABB3D.GetCenter();
					GetEntityAABB(pVehicles, &explosivesAABB3D);

					std::array<ImVec2, 8> points2D;
					bool valid = true;
					for (int i = 0; i < 8; i++)
					{
						if (!WorldToScreen(explosivesAABB3D.points[i], points2D[i]))
						{
							valid = false;
							break;
						}

					}
					if (valid)
					{

						//Renderer::DrawBox(points2D, ImColor::Orange());
					}

					Vector2D aimPoint2D;
					/*if*/ (WorldToScreen(center, aimPoint2D));
						//Renderer::DrawString(aimPoint2D, StringFlag::CENTER_X | StringFlag::CENTER_Y,
						//	ImColor::Green(), xorstr_("%s"), pVehicles->GetVehicleName().c_str());
					const auto delta = Misc::GetAbsDeltaAtGivenPoints(G::screenCenter, aimPoint2D);

					//if (delta < closest)
					{
						closest = delta;
						pBestVehicle = pVehicles;
						bestAimPoint = center;

					}


				}

			} while (vehicles.next());
		}

		if (!pBestVehicle) return;

		ImVec2 cent2D;
		WorldToScreen(bestAimPoint, cent2D);
		Renderer::DrawRectOutlined(cent2D - 5, cent2D + 5, ImColor::Cyan());

		static Vector targetVelocity = Vector(2, 0, -3);
		float bulletVelocity = 0.f, bulletGravity = 0.f;
		auto startPosition = viewPos;
		float rocketData = 0.0f;
		auto pFiring = pLocal->GetSoldierEntity()->GetFiringData();

		if (pFiring && pFiring->m_ShotConfigData.m_ProjectileData)
		{
			auto rectionType = pFiring->m_ShotConfigData.m_ProjectileData->m_HitReactionWeaponType;
			if (rectionType == ProjectileEntityData::AntHitReactionWeaponType_Explosion)
			{
				auto pMissileData = reinterpret_cast<MissileEntityData*>(pFiring->m_ShotConfigData.m_ProjectileData);
				if (IsValidPtr(pMissileData) && !pLocal->InVehicle())
				{
					const auto isLG = pMissileData->IsLaserGuided();
					const auto& ignTime = pMissileData->m_EngineTimeToIgnition;
					const auto& initSpd = pFiring->m_ShotConfigData.m_Speed.z;
					const auto& accel = pMissileData->m_EngineStrength;
					const auto& maxSpd = pMissileData->m_MaxSpeed;
					startPosition = (!isLG) ? G::viewPos : (pMissile != nullptr) ? pMissile->m_Position : G::viewPos;
					auto dst = Misc::Distance3D(startPosition, bestAimPoint);

					//Calculating final velocity first time to solve 't' at given 'dst' to target
					bulletVelocity = Prediction::ComputeMissileFinalVelocity(initSpd, maxSpd, accel, ignTime, dst, &rocketData);

					//Calculate where target will be after 't' seconds
					//const auto posAfterTime = bestAimPoint + (targetVelocity * rocketData);
					//dst = Misc::Distance3D(posAfterTime, bestAimPoint);

					//Calculate final velocity again for new target position 
					//bulletVelocity = Prediction::ComputeMissileFinalVelocity(initSpd, maxSpd, accel, ignTime, dst);
					bulletGravity = pMissileData->m_Gravity > 0.f ? 0.0f : pMissileData->m_Gravity;
				}
				if (pLocal->InVehicle() && IsValidPtr(pVehWeaponData))
				{
					bulletGravity = pVehWeaponData->gravity;
					bulletVelocity = pVehWeaponData->speed.z;

					static bool refresh = false;
					static int prevWeaponID = pVehWeaponData->gunID;

					if (IsValidPtr(pMissile) && IsValidPtr(pMissile->m_pMissileEntityData)
						&& pMissile->m_pMissileEntityData->IsLaserGuided())
					{
						const auto isLG = pMissileData->IsLaserGuided();
						const auto& ignTime = pMissileData->m_EngineTimeToIgnition;
						const auto& initSpd = pFiring->m_ShotConfigData.m_Speed.z;
						const auto& accel = pMissileData->m_EngineStrength;
						const auto& maxSpd = pMissileData->m_MaxSpeed;
						startPosition = pMissile->m_Position;
						auto dst = Misc::Distance3D(G::viewPos, startPosition);

						bulletVelocity = Prediction::ComputeMissileFinalVelocity(initSpd, maxSpd, accel, ignTime, dst);
						//const auto posAfterTime = (bestAimPoint - startPosition) + (targetVelocity * rocketData.airTime);
						//auto afterTimeDst = Misc::Distance3D(posAfterTime, bestAimPoint);

						//bulletVelocity = ComputeMissileFinalVelocity(initSpd, maxSpd, accel, ignTime, afterTimeDst);
						bulletGravity = 0.0;

					}
					else refresh = false;
				}
			}
		}

		if (pVeh)
		{
			if (pVeh->IsTVGuidedMissile())
			{
				bulletGravity = 0.0f;
				bulletVelocity = D3DXVec3Length(&pVeh->m_VelocityVec);
			}
		}

		if (Cfg::DBG::debugOutput)
		{
			/*if (pMissile)
			{
				auto targetDist = Misc::Distance3D(G::viewPos, bestAimPoint);
				auto missileViewDist = Misc::Distance3D(G::viewPos, pMissile->m_Position);
				auto targetMissileDist = Misc::Distance3D(pMissile->m_Position, bestAimPoint);

				if (missileViewDist <= targetDist)
					Renderer::DrawCircleProgressBar(
						G::viewPos2D, 30.f, 32.f,
						fabsf(targetMissileDist - targetDist),
						targetDist - (targetDist / 7.f), ImColor::Cyan(), 2.f);
			}*/


			Renderer::DrawString({ 20, G::screenSize.y - 50 }, 0, ImColor::Green(), xorstr_("From computing:"));
			Renderer::DrawString({ 20, G::screenSize.y - 35 }, 0, ImColor::Green(), xorstr_("Bullet: V: %dm/s G: %.1f"),
				(int)bulletVelocity, bulletGravity);
		}

		Prediction::AngularPredictionData_s angData;
		angData.angularVelocity = { -3.00, 6.44, -4.00 };
		targetVelocity = { -40.93, 40.99, -4.98 };
		Matrix m; pBestVehicle->GetTransform(&m);
		D3DXQuaternionRotationMatrix(&angData.orientation, &m);
		angData.valid = true;

		PredictionData_s data;
		if (Prediction::ComputePredictedPointInSpace(startPosition, bestAimPoint, targetVelocity, bulletVelocity, bulletGravity, &data, rocketData, 0.0f, &angData))
		{
			//Cfg::ESP::predictionCrossColor = ImColor(23, 206, 176);
			RenderAimPoint(data);
		}

		//InputActions::Get()->HandleInput(
		//	PreUpdate::predictionData.hitPos, pLocal, PreUpdate::weaponData, bestAimPoint);
	}
}

void Visuals::RenderVehicleInfo(ClientPlayer* pLocal, WeaponData_s* pData)
{
	if (!IsValidPtr(pLocal) || !IsValidPtr(pData)) return;

	if (Cfg::ESP::aimbotFov && !pLocal->InVehicle())
		Renderer::DrawCircleOutlined(G::viewPos2D, Cfg::AimBot::radius, 0, Cfg::ESP::fovColor);
	
	if (pData->isValid)
	{
		Renderer::DrawString({ 20, 140 }, 0, ImColor::Yellow(), xorstr_("%s:"), pData->gunName.data());
		Renderer::DrawString({ 20, 155 }, 0, ImColor::Yellow(), xorstr_("Gravity  = %.1f."), pData->gravity);
		Renderer::DrawString({ 20, 170 }, 0, ImColor::Yellow(), xorstr_("Velocity = %dm/s."), (int)pData->speed.z);

		if (auto pFiring = WeaponFiring::GetInstance(); IsValidPtr(pFiring) && pFiring->m_FirstSlotBullets > -1)
			Renderer::DrawString({ 20, 185 }, 0, ImColor::Yellow(), xorstr_("Ammo: %d / %d"),
				pFiring->m_FirstSlotBullets, pFiring->m_SecondSlotBullets);
	}

	auto pVehicle = pLocal->GetClientVehicleEntity();
	if (IsValidPtr(pVehicle) && IsValidPtr(pVehicle->m_pData) && IsValidPtr(pVehicle->m_pHealthComp))
	{
		float maxHp = pVehicle->m_pData->m_MaxHealth;
		float curHp = pVehicle->m_pHealthComp->m_VehicleHealth;
		int percHp = static_cast<int>((curHp * 100) / maxHp);
		auto healthColor =
			ImColor(
				255 - (int)((percHp * 255) / 100),
				0 + (int)((percHp * 255) / 100),
				0,
				255);
		float vLenght = D3DXVec3Length(&pVehicle->m_VelocityVec) * 3.6f;

		ImGui::PushFont(DX::Digital10);
		Renderer::DrawSpeedometer({ G::screenSize.x * 3.f / 4.f, G::screenSize.y - 90.f }, 0.25f, 0,
			pVehicle->m_pData->IsInJet() ? 420.f : pVehicle->m_pData->IsInHeli() ? 220.f : 150.f, vLenght);
		ImGui::PopFont();

		Renderer::DrawString({ G::screenCenter.x, 220 }, StringFlag::CENTER_X, ImColor::Green(), xorstr_("Speed = %dkm/h"), (int)vLenght);
		Renderer::DrawString({ G::screenCenter.x, 235 }, StringFlag::CENTER_X, healthColor, xorstr_("Health = %d%%"), percHp);
	}
	else if (auto pLocalSoldier = pLocal->GetSoldierEntity(); IsValidPtr(pLocalSoldier) && IsValidPtr(pLocalSoldier->m_pHealthComp))
	{
		float maxHp = pLocalSoldier->m_pHealthComp->m_MaxHealth;
		float curHp = pLocalSoldier->m_pHealthComp->m_Health;
		int percHp = static_cast<int>((curHp * 100) / maxHp);
		auto healthColor =
			ImColor(
				255 - (int)((percHp * 255) / 100),
				0 + (int)((percHp * 255) / 100),
				0,
				255);
		Renderer::DrawString({ 40, 230 }, StringFlag::CENTER_X | StringFlag::CENTER_Y, ImColor::White(), xorstr_("%d"), percHp);
		Renderer::DrawCircleProgressBar({ 40, 230 }, 20, 32, (float)percHp, 97.f, healthColor, 2.f);
	}

	if (auto pFiring = WeaponFiring::GetInstance(); IsValidPtr(pFiring) && pLocal->InVehicle() && pData->isValid)
	{
		if (pData->speed.z >= 500.f && pFiring->m_FirstSlotBullets == -1) 
		{
			auto overheatColor = ImColor(0.0f + pFiring->m_Overheat, 1.f - pFiring->m_Overheat, 0.0f, 1.f);
			if (pFiring->m_IsCoolingDown) overheatColor = ImColor(0, 128, 255, 144);
			Renderer::DrawProgressBar({ G::screenCenter.x, 205 }, { 200, 10 }, pFiring->m_Overheat, 1.f, overheatColor);
		}
		else
		{
			static float maxTime = 0.01f;
			static int weaponID = pData->gunID;
			auto outOfAmmo = !pFiring->m_FirstSlotBullets && !pFiring->m_SecondSlotBullets;
			auto color = outOfAmmo ? ImColor(255, 128, 0, 144) : ImColor(0, 128, 255, 144);

			if (pFiring->m_ReloadTimer > maxTime || pData->gunID != weaponID)
			{
				weaponID = pData->gunID;
				maxTime = pFiring->m_ReloadTimer;
			}

			ImGui::PushFont(DX::Verdana24);
			if (pFiring->m_ReloadTimer > 0.0f)
			{
				static ImColor warning = ImColor::Red();
				auto& a = warning.Value.w;
				static bool flip = false;

				if (!flip)
				{
					if (a >= 0.1f) a -= 0.05f;
					else { a = 0.1f; flip = true; }
				}
				else
				{
					if (a <= 1.0f) a += 0.05f;
					else { a = 1.0f; flip = false; }
				}

				Renderer::DrawString({ G::screenCenter.x, 205 - 5 }, StringFlag::CENTER_X | StringFlag::TOP_Y,
					warning, xorstr_("RELOADING"));

			}
			else if (outOfAmmo)
				Renderer::DrawString({ G::screenCenter.x, 205 - 5 }, StringFlag::CENTER_X | StringFlag::TOP_Y,
					ImColor::Red(), xorstr_("OUT OF AMMO"));

			Renderer::DrawString({ G::screenCenter.x - 100, 205 - 5 }, StringFlag::TOP_Y, color, xorstr_("%d"), pFiring->m_FirstSlotBullets);
			Renderer::DrawString({ G::screenCenter.x + 100, 205 - 5 }, StringFlag::TOP_Y | StringFlag::RIGHT_X, color, xorstr_("%d"), pFiring->m_SecondSlotBullets);
			ImGui::PopFont();

			Renderer::DrawProgressBar({ G::screenCenter.x, 205 }, { 200, 10 }, pFiring->m_ReloadTimer, maxTime);

			if (pFiring->m_ReloadTimer <= 0.0f)
			{
				Renderer::DrawRectFilled({ G::screenCenter.x - 100, 205 }, { G::screenCenter.x + 100, 215 }, ImColor::Black(190));
				Renderer::DrawRectFilled({ G::screenCenter.x - 98, 207 }, { G::screenCenter.x + 98, 213 }, color);
			}
		}
	}
}

void Visuals::RenderRadar(ClientPlayer* pLocal, ClientPlayer* pPlayer, int i)
{
	if (!IsValidPtr(pLocal) || !IsValidPtr(pPlayer)) return;
	if (Cfg::ESP::Radar::onlyInVehicle && !pLocal->InVehicle()) return;

	static std::array<ID3D11ShaderResourceView*, 5> pIcons;
	static bool doOnce = true;
	if (doOnce)
	{
		doOnce = false;
		D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &RadarIcons::Jet, sizeof(RadarIcons::Jet), NULL, NULL, &pIcons[1], NULL);
		D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &RadarIcons::Heli, sizeof(RadarIcons::Heli), NULL, NULL, &pIcons[0], NULL);
		D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &RadarIcons::Tank, sizeof(RadarIcons::Tank), NULL, NULL, &pIcons[2], NULL);
		D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &RadarIcons::AntiAir, sizeof(RadarIcons::AntiAir), NULL, NULL, &pIcons[3], NULL);
		D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &RadarIcons::Boat, sizeof(RadarIcons::Boat), NULL, NULL, &pIcons[4], NULL);
	}

	auto RotatePoint = [](const Vector2D& point, const Vector2D& center, float angle) -> Vector2D
	{
		float _cos = std::cosf(D3DXToRadian(angle));
		float _sin = std::sinf(D3DXToRadian(angle));

		Vector2D relative = { point.x - center.x,  point.y - center.y };

		Vector2D rotated =
		{
			_cos * (relative.x) - _sin * (relative.y),
			_sin * (relative.x) + _cos * (relative.y)
		};

		rotated += center;

		return rotated;
	};

	auto RotateArrow = [&RotatePoint](std::vector<ImVec2>& pointsToRotate, const ImVec2& center, float angle) -> void
	{
		for (auto& it : pointsToRotate)
			it = RotatePoint(it, center, angle);
	};

	auto RenderArrow = [&RotateArrow](const ImVec2& center, const ImColor& color, const float rotation)
	{
		//Arrow points
		std::vector<ImVec2> arrow =
		{
			ImVec2(center.x, center.y + 4),
			ImVec2(center.x - 7, center.y - 10),
			ImVec2(center.x, center.y - 7),
			ImVec2(center.x + 7, center.y - 10),
		};
		std::vector<ImVec2> arrowOutline =
		{
			ImVec2(center.x, center.y + 5),
			ImVec2(center.x - 8, center.y - 11),
			ImVec2(center.x, center.y - 8),
			ImVec2(center.x + 8, center.y - 11),
		};

		RotateArrow(arrow, center, rotation);
		RotateArrow(arrowOutline, center, rotation);

		//Render arrow
		ImGui::GetBackgroundDrawList()->AddConvexPolyFilled(arrowOutline.data(), arrowOutline.size(), ImColor::Black(color.Value.w * 255));
		ImGui::GetBackgroundDrawList()->AddConvexPolyFilled(arrow.data(), arrow.size(), color);
	};

	auto pTurret = VehicleTurret::GetInstance();
	if (!IsValidPtr(pTurret)) return;

	static Vector2D localPos = { G::viewPos.x, G::viewPos.z };
	static float yaw = pTurret->m_Angles.x;
	static auto radarCenter = Vector2D(Cfg::ESP::Radar::posX, Cfg::ESP::Radar::posY);
	const float radarRadius = Cfg::ESP::Radar::radius;
	static int iterator = 0;
	bool isOutOfRange = false;
	static BoundingBox dragMenu;
	VehicleData::VehicleType entityType = VehicleData::VehicleType::UNUSED;
	VehicleData::VehicleCategory entityCat = VehicleData::VehicleCategory::UNUSED;

	//Do once 
	if (i == 0)
	{
		if (G::isMenuVisible)
		{
			dragMenu =
			{
				radarCenter.x - radarRadius - 10,
				radarCenter.y - radarRadius - 10,
				radarCenter.x + radarRadius + 10,
				radarCenter.y + radarRadius + 10
			};

			static Menu::DragEvent_s data;
			Menu::HandleDragEvent(dragMenu, data);

			Renderer::DrawRectGradient(dragMenu,
				ImColor(40, 40, 40), ImColor(40, 40, 40),
				ImColor(20, 20, 20), ImColor(20, 20, 20));

			Menu::RenderMenuAccentOverlay(dragMenu);
		}

		if (dragMenu.IsValid())
		{
			radarCenter = dragMenu.GetMin() + dragMenu.GetCenter();
			Cfg::ESP::Radar::posX = radarCenter.x;
			Cfg::ESP::Radar::posY = radarCenter.y;
		}

		Renderer::DrawLine(
			{ radarCenter.x - radarRadius, radarCenter.y },
			{ radarCenter.x + radarRadius, radarCenter.y },
			ImColor::White(150));
		Renderer::DrawLine(
			{ radarCenter.x, radarCenter.y - radarRadius },
			{ radarCenter.x, radarCenter.y + radarRadius },
			ImColor::White(150));

		Renderer::DrawCircleOutlined(radarCenter, radarRadius, 32.f, ImColor::White());
		Renderer::DrawCircleFilled(radarCenter, radarRadius - 1.f, 32.f, ImColor::Black(150));
		localPos = { G::viewPos.x, G::viewPos.z };

		yaw = pTurret->m_Angles.y;
		if (pTurret->m_Angles.y > 180.f) yaw -= 360.f;
	}

	if (pLocal == pPlayer) return;

	bool isInTeam = pLocal->m_TeamId == pPlayer->m_TeamId;
	if (!Cfg::ESP::team && isInTeam) return;

	Vector2D playerPos = ZERO_VECTOR2D;
	float playerYaw = 0.0f;

	if (auto pVeh = pPlayer->GetClientVehicleEntity(); Cfg::ESP::Radar::showVehicles && IsValidPtr(pVeh))
	{
		TransformAABBStruct mat;
		D3DXMATRIX mat2;
		pVeh->GetAABB(&mat);
		pVeh->GetTransform(&mat2);
		playerPos = { mat2._41, mat2._43 };
		entityType = pVeh->m_pData->GetVehicleType();
		entityCat = pVeh->m_pData->GetVehicleCategory();

		float forwardYaw = D3DXToDegree(std::asinf(mat.Transform.data[0][0])) * -1.f + 90.0f;
		if (mat.Transform.data[0][2] > 0.0f) forwardYaw *= -1.f;
		playerYaw = forwardYaw;
	}
	else if (auto pSoldier = pPlayer->GetSoldierEntity(); IsValidPtr(pSoldier))
	{
		if (!pSoldier->IsAlive()) return;
		D3DXMATRIX mat2;
		TransformAABBStruct mat;
		pSoldier->GetAABB(&mat); //<---- here
		pSoldier->GetTransform(&mat2);
		playerPos = { mat2._41, mat2._43 };
		entityType = VehicleData::VehicleType::PLAYER;

		float forwardYaw = D3DXToDegree(std::asinf(mat.Transform.data[0][0])) * -1.f + 90.0f;
		if (mat.Transform.data[0][2] > 0.0f) forwardYaw *= -1.f;
		playerYaw = forwardYaw;
	}

	if (playerPos == ZERO_VECTOR2D) return;

	Vector2D relativePos = localPos - playerPos;
	relativePos *= Cfg::ESP::Radar::zoom;
	if (D3DXVec2Length(&relativePos) >= radarRadius)
	{
		//Normalization...
		auto length = D3DXVec2Length(&relativePos);
		if (length != 0.0f) relativePos /= length;

		relativePos *= radarRadius;
		isOutOfRange = true;
	}

	relativePos += radarCenter;
	relativePos = RotatePoint(relativePos, radarCenter, yaw);
	float relativeYaw = yaw - playerYaw;
	auto& pos = relativePos;

	if (entityType == VehicleData::VehicleType::PLAYER
		&& entityType != VehicleData::VehicleType::UNUSED)
	{
		ImColor color = isInTeam ? Cfg::ESP::teamColor : Cfg::ESP::Radar::soldierColor;
		if (isOutOfRange) { color = ImColor::Grey(); color.Value.w = 0.5f; }

		RenderArrow(pos, color, relativeYaw - 180.0f);
	}
	else if (entityType != VehicleData::VehicleType::UNUSED)
	{
		Vector2D size = { (float)Cfg::ESP::Radar::iconScale, (float)Cfg::ESP::Radar::iconScale };

		ImColor color = ImColor::White();

		int id = -1;

		switch (entityType)
		{

			//You could change that colors as well, I've forgot to add that to the menu, sorry.
		case VehicleData::VehicleType::TANKAA: { color = ImColor::Red(); id = 3; break; }
		case VehicleData::VehicleType::HELIATTACK:
		case VehicleData::VehicleType::HELISCOUT:
		case VehicleData::VehicleType::HELITRANS: { color = ImColor::Cyan(); id = 0; break; }
		case VehicleData::VehicleType::JET:
		case VehicleData::VehicleType::JETBOMBER: { color = ImColor::Cyan(); id = 1; break; }
		case VehicleData::VehicleType::BOAT: { color = ImColor::Orange(); id = 4; break; }
		default: { color = ImColor::White(); id = -1; }
		}

		if (entityCat == VehicleData::VehicleCategory::GROUND)
		{
			color = ImColor::Orange(); id = 2;
		}

		if (isOutOfRange) { color = ImColor::Grey(); color.Value.w = 0.5f; }

		if (id > -1)
			Renderer::DrawImageRotated(pIcons[id], pos, size, D3DXToRadian(relativeYaw), color);
	}
}

void Visuals::RenderAimPoint(const PredictionData_s& data, ClientPlayer* pTargetData)
{
	ImVec2 predAimPoint, currPos;
#ifndef AIMPOINT_DBG
	if (!WorldToScreen(data.hitPos, predAimPoint)) return;
	WorldToScreen(data.origin, currPos);
#endif

#ifdef AIMPOINT_DBG
	predAimPoint = { 200, 400 };
	currPos = { 269, 600 };
#endif

	ImVec2 lastCurvePoint;
	if (Cfg::DBG::_internalUseCurve && Cfg::ESP::_internalCurveIterationCount > 0)
	{
		const auto& points = Cfg::DBG::_internalPredictionCurve;
		auto colorDelta = 255 / points.size();
		for (int i = 0; i < Cfg::ESP::_internalCurveIterationCount - 1; i++)
		{
			ImVec2 screen, screen2;
			if (WorldToScreen(points.at(i), screen) && WorldToScreen(points.at(i + 1), screen2))
			{
				auto color = ImColor(255 - (colorDelta * i), 0 + (colorDelta * i), 128);
				ImGui::GetBackgroundDrawList()->AddLine(screen, screen2, ImColor::Black(255 * Cfg::ESP::predictionCrossColor.Value.w), 2.0f);
				Renderer::DrawLine(screen, screen2, color);
				lastCurvePoint = screen2;
			}
		}

		if (IsValidPtr(pTargetData) && !pTargetData->InVehicle()) lastCurvePoint = currPos;
	}
	else lastCurvePoint = currPos; 

	Vector2D crossDelta;
	Vector2D tmp = { predAimPoint.x, predAimPoint.y };
	D3DXVec2Subtract(&crossDelta, &G::viewPos2D, &tmp);

	const ImVec2& p1 = predAimPoint;
	const ImVec2& p2 = lastCurvePoint;

	float angle;
	auto v = ImVec2(p2.x - p1.x, p2.y - p1.y);

	const float a = fabsf(p2.y - p1.y);
	const float b = fabsf(p2.x - p1.x);
	const float c = sqrtf((v.x * v.x) + (v.y * v.y));
	const auto& rad = Cfg::ESP::predictionCrossRadius;
	static constexpr float quarterPI = D3DXToRadian(90.f);

	if (c > rad)
	{
		//Cancer way of rotating point around the circle...
		if (p2.y <= p1.y)
		{
			if (p2.x >= p1.x) angle = asinf(a / c);
			else angle = acosf(a / c) + quarterPI;
		}
		else
		{
			if (p2.x <= p1.x) angle = acosf(b / c) + 2 * quarterPI;
			else angle = asinf(b / c) + 3 * quarterPI;
		}

		ImVec2 point =
		{
			p1.x + (rad * cosf(-angle)),
			p1.y + (rad * sinf(-angle))
		};

		ImGui::GetBackgroundDrawList()->AddLine(point, lastCurvePoint, ImColor::Black(255 * Cfg::ESP::predictionCrossColor.Value.w), 2.0f);
		Renderer::DrawLine(point, lastCurvePoint, Cfg::ESP::predictionCrossColor);
		Renderer::DrawCircleFilled(lastCurvePoint, 2, 0, Cfg::ESP::predictionCrossColor);
	}

	const bool release = D3DXVec2Length(&crossDelta) <= rad;
	ImColor crossColor = release ? Cfg::ESP::predictionCrossOverrideColor : Cfg::ESP::predictionCrossColor;

	if (pTargetData)
	{
		float maxHp = 0.0f, currHp = 0.0f;
		if (auto pVeh = pTargetData->GetClientVehicleEntity(); pTargetData->InVehicle() && IsValidPtr(pVeh) && IsValidPtr(pVeh->m_pData) && IsValidPtr(pVeh->m_pHealthComp))
		{
			maxHp = pVeh->m_pHealthComp->m_MaxHealth;
			currHp = pVeh->m_pHealthComp->m_VehicleHealth;
		}
		else if (auto pSold = pTargetData->GetSoldierEntity(); IsValidPtr(pSold) && IsValidPtr(pSold->m_pHealthComp))
		{
			maxHp = pSold->m_pHealthComp->m_MaxHealth;
			currHp = pSold->m_pHealthComp->m_Health;
		}

		currHp = std::clamp(currHp, 0.0f, maxHp);
		const auto percHp = (currHp * maxHp) / 100.f;

		if (percHp < 100.f && percHp > 0.f)
		{
			auto hpCol = Cfg::ESP::predictionCrossColor(190);
			BoundingBox bbHp = { { p1.x - rad, p1.y - rad - 20.f }, { p1.x + rad, p1.y - rad - 16.f } };

			Renderer::DrawRectFilled(bbHp.GetMin(), { bbHp.GetMax().x + 2, bbHp.GetMax().y + 1}, ImColor::Black(120));
			Renderer::DrawRectFilled(
				bbHp.GetMin() + 1.f,
				{ bbHp.GetMin().x + 1.f + (currHp * bbHp.GetSize().x / maxHp), bbHp.GetMax().y },
				hpCol);
		}
	}

	ImVec2 lastPoint[2];
	Renderer::DrawCircleFilled(p1, rad, 25, ImColor::Black(50));
	Renderer::DrawCircle(p1, 2, 25, crossColor);
	Renderer::DrawCircleOutlined(p1, rad, 25, crossColor);
	Renderer::DrawCircleProgressBar(p1, rad - 2, 25, data.travelTime, 4.f, crossColor, 1.0f, false, lastPoint);
	Renderer::DrawLine(lastPoint[1], lastPoint[0], crossColor);

	//Cross
	ImGui::GetBackgroundDrawList()->AddLine({ p1.x - 20, p1.y }, { p1.x - rad, p1.y }, ImColor::Black(255 * Cfg::ESP::predictionCrossColor.Value.w), 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine({ p1.x + rad, p1.y }, { p1.x + 20, p1.y }, ImColor::Black(255 * Cfg::ESP::predictionCrossColor.Value.w), 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine({ p1.x, p1.y - rad }, { p1.x, p1.y - 20 }, ImColor::Black(255 * Cfg::ESP::predictionCrossColor.Value.w), 2.0f);
	ImGui::GetBackgroundDrawList()->AddLine({ p1.x, p1.y + rad }, { p1.x, p1.y + 20 }, ImColor::Black(255 * Cfg::ESP::predictionCrossColor.Value.w), 2.0f);

	Renderer::DrawLine({ p1.x - 20, p1.y }, { p1.x - rad, p1.y }, crossColor);
	Renderer::DrawLine({ p1.x + rad, p1.y }, { p1.x + 20, p1.y }, crossColor);
	Renderer::DrawLine({ p1.x, p1.y - rad }, { p1.x, p1.y - 20 }, crossColor);
	Renderer::DrawLine({ p1.x, p1.y + rad }, { p1.x, p1.y + 20 }, crossColor);

	if (Cfg::ESP::predictionImpactData)
	{
		ImGui::PushFont(DX::Verdana8);
		Renderer::DrawString({ p1.x + 30, p1.y - 13 }, 0, Cfg::ESP::predictionDataColor, xorstr_("T: %.1fs."), data.travelTime);
		Renderer::DrawString({ p1.x + 30, p1.y - 4 }, 0, Cfg::ESP::predictionDataColor, xorstr_("D: %dm."), (int)data.distance);
		Renderer::DrawString({ p1.x + 30, p1.y + 5 }, 0, Cfg::ESP::predictionDataColor, xorstr_("V: %dm/s."), (int)data.bulletVel);
		ImGui::PopFont();
	}

	if (targetLock)
	{
		Renderer::DrawString({ p1.x - 32, p1.y - 2 }, StringFlag::RIGHT_X | StringFlag::CENTER_Y, ImColor::Black(), xorstr_("LOCKED"));
		Renderer::DrawString({ p1.x - 30, p1.y }, StringFlag::RIGHT_X | StringFlag::CENTER_Y, ImColor(223, 32, 32), xorstr_("LOCKED"));
	}
}

void Visuals::RenderBombImpact(const Vector& targetPos, WeaponData_s* pDataIn)
{
	if (Cfg::ESP::predictionBombImpact && IsValidPtr(pDataIn))
	{
		if (pDataIn->isValid)
		{
			if (pDataIn->gravity == 0.0f && pDataIn->speed.z == 0.0f)
			{
				auto pBomb = reinterpret_cast<ClientIndirectFireWeapon*>(pDataIn->pWeapon);
				if (IsValidPtr(pBomb))
				{
					auto impactPos = Vector(pBomb->landingpos.x, pBomb->landingpos.y, pBomb->landingpos.z);
					bool inRange = false;

					if (targetPos != ZERO_VECTOR)
						inRange = Misc::Distance2D(Vector2D(targetPos.x, targetPos.z), Vector2D(impactPos.x, impactPos.z)) <= 5.f;;

					ImVec2 impactPos2D, target2D;
					WorldToScreen(impactPos, impactPos2D);

					if (inRange)
					{
						Renderer::DrawString({ impactPos2D.x, impactPos2D.y - Cfg::ESP::predictionCrossRadius - 10.f },
							StringFlag::CENTER_X, ImColor::Black(), xorstr_("DROP NOW!"));
						Renderer::DrawString({ impactPos2D.x + 1, impactPos2D.y - Cfg::ESP::predictionCrossRadius - 9.f },
							StringFlag::CENTER_X, ImColor::Red(), xorstr_("DROP NOW!"));
					}

					Renderer::DrawCircleFilled(impactPos2D, Cfg::ESP::predictionCrossRadius, 0,
						inRange ? ImColor::Green(120) : ImColor::Red(120));
					Renderer::DrawCircleOutlined(impactPos2D, Cfg::ESP::predictionCrossRadius, 0, ImColor::White(120));

					if (targetPos != ZERO_VECTOR)
					{
						WorldToScreen(targetPos, target2D);

						if (target2D != ImVec2(0, 0))
							Renderer::DrawLine(impactPos2D, target2D, ImColor::Green(120));
					}
				}
			}
		}
	}
}

void Visuals::RenderOffScreenTarget(ClientPlayer* pTarget, const Vector& viewPos)
{

	//TODO: I was thinking about making arrow with direction to the players behind me.

}

void Visuals::RenderWatermark()
{
	//If you want to make some Gay's like watermark, use code from below as color for rendering:

	/*static ImColor color;
	static float timer = 0.f;
	if (timer > 360.f) timer = 0.f;
	timer += .2f;
	color.SetHSV(timer / 360.f, 1.f, 1.f);*/

	static ID3D11ShaderResourceView* pLogo = nullptr;
	if (!pLogo)
		D3DX11CreateShaderResourceViewFromMemory(DX::pDevice, &MenuImages::Logo, sizeof(MenuImages::Logo), NULL, NULL, &pLogo, NULL);

	ImGui::GetBackgroundDrawList()->AddImage(pLogo, { 5, 5 }, { 225, 70 }, { 0,0 }, { 1,1 }, ImColor::White(120));

	ImGui::PushFont(DX::Verdana18);
	Renderer::DrawString(ImVec2(10, 80), StringFlag::CENTER_Y, ImColor(130, 180, 255), xorstr_("Time:"), Misc::GetSystemTime().c_str());

	static double curTime = ImGui::GetTime();
	static float fps = ImGui::GetIO().Framerate;
	if (ImGui::GetTime() - curTime >= 0.1f)
	{
		curTime = ImGui::GetTime();
		fps = ImGui::GetIO().Framerate;
	}

	Renderer::DrawString(ImVec2(10, 80 + 18), StringFlag::CENTER_Y, ImColor(130, 180, 255), xorstr_("FPS:"));
	ImGui::PopFont();

	ImGui::PushFont(DX::Digital10);

	Renderer::DrawString(ImVec2(10 + ImGui::CalcTextSize(xorstr_("Time: ")).x, 80 - 8), 0, ImColor(130, 180, 255), xorstr_("%s"), Misc::GetSystemTime().c_str());
	Renderer::DrawString(ImVec2(10 + ImGui::CalcTextSize(xorstr_("FPS: ")).x, 80 - 8 + 18), 0, ImColor(130, 180, 255), xorstr_("%d"), int(fps));

	ImGui::PopFont();
}

void Visuals::SpoofNameClientSided(ClientPlayer* pLocal)
{
	//Call that in your loop (in visuals or PreFrame)

	static bool autoBackup = true, spoofed = false, wasAlive = false;
	static int queueSpoofCount = 0;
	if (autoBackup && pLocal->m_Name[0] != '\0')
	{
		strcpy(Cfg::DBG::_internalName, pLocal->m_Name);
		autoBackup = false;
	}

	auto isAlive = IsValidPtr(pLocal->GetSoldierEntity()) ? pLocal->GetSoldierEntity()->IsAlive() : false;

	if (Cfg::DBG::_internalSpoof) queueSpoofCount++;

	if (wasAlive && spoofed && isAlive)
	{
		wasAlive = false;
		spoofed = false;
	}

	if (queueSpoofCount && !spoofed && isAlive && (strcmp(pLocal->m_Name, Cfg::DBG::spoofedName) != NULL))
	{
		queueSpoofCount = 0;
		wasAlive = true;
		spoofed = true;
		strcpy(pLocal->m_Name, Cfg::DBG::spoofedName);
		strcpy(pLocal->m_NamePtr, Cfg::DBG::spoofedName);
		strcpy(pLocal->m_Name2, Cfg::DBG::spoofedName);
	}

	if (Cfg::DBG::_internalRestore)
	{
		strcpy(pLocal->m_Name, Cfg::DBG::_internalName);
		strcpy(pLocal->m_NamePtr, Cfg::DBG::_internalName);
		strcpy(pLocal->m_Name2, Cfg::DBG::_internalName);
	}
}

VeniceClientMissileEntity* Visuals::GetMissileEntity(ClientGameContext* pCtx, ClientPlayer* pLocal)
{
	if (!IsValidPtr(pCtx->m_pLevel) || !IsValidPtr(pCtx->m_pLevel->m_pGameWorld)) return nullptr;

	auto* pGameWorld = pCtx->m_pLevel->m_pGameWorld;
	if (!IsValidPtr(pGameWorld)) return nullptr;

	if (ClassInfos.MissileEntity)
	{
		EntityIterator<VeniceClientMissileEntity> missiles(pGameWorld, ClassInfos.MissileEntity);
		VeniceClientMissileEntity* pMyMissile = nullptr;

		//Finding own missile
		if (missiles.front())
		{
			do
			{
				if (auto* pMissile = missiles.front()->getObject(); IsValidPtr(pMissile))
				{
					if (pMissile->m_pOwner.GetData() == pLocal)
					{
						pMyMissile = pMissile;
						break;
					}
				}

			} while (missiles.next());
		}

		if (!IsValidPtr(pMyMissile)) return nullptr;
		if (!IsValidPtr(pMyMissile->m_pMissileEntityData)) return nullptr;

		if (pMyMissile->m_pMissileEntityData->IsLockable()) return nullptr;

		const bool isLG = pMyMissile->m_pMissileEntityData->IsLaserGuided();

		if (Cfg::ESP::ownMissile && isLG)
		{
			const auto& missileBB = GetEntityAABB((ClientControllableEntity*)pMyMissile);
			ImVec2 scrn = missileBB.GetMin() + missileBB.GetCenter();

			std::vector<ImVec2> points =
			{
				ImVec2(scrn.x, scrn.y - 5),
				ImVec2(scrn.x + 5, scrn.y),
				ImVec2(scrn.x, scrn.y + 5),
				ImVec2(scrn.x - 5, scrn.y),
				ImVec2(scrn.x, scrn.y - 5),
			};

			auto fill = Cfg::ESP::missileColor;
			fill.Value.w = std::clamp(Cfg::ESP::missileColor.Value.w - 0.5f, 0.0f, 1.0f);
			ImGui::GetForegroundDrawList()->AddConvexPolyFilled(points.data(), points.size(), fill);
			Renderer::DrawLine(points, Cfg::ESP::missileColor);

		}

		return pMyMissile;
	}
	return nullptr;
}

void Visuals::RenderVisuals()
{
#ifdef GUI_TEST
	return;
#endif

#ifdef AIMPOINT_DBG
	PredictionData_s d;
	d.bulletDrop = -9.8f;
	d.bulletVel = 900.f;
	d.distance = 1337.f;
	d.hitPos = { 0,0,0 };
	d.origin = { 0,0,0 };
	d.travelTime = 3.1f;
	RenderAimPoint(d, nullptr);
#endif

	if (Menu::IsKeyClicked(0x42)) targetLock = !targetLock;

	if (Cfg::DBG::watermark)
		RenderWatermark();

	if (Cfg::DBG::_internalFFSS > 0)
	{
		Renderer::DrawString({ 20, 125 }, 0, ImColor::Pink(),
			xorstr_("FairFight just took screenshot %d time(s)!"), Cfg::DBG::_internalFFSS);
	}

	auto pMain = Main::GetInstance();
	if (!IsValidPtr(pMain)) return;

	auto pClient = pMain->m_pClient;
	if (!IsValidPtr(pClient)) return;

	auto pGameCtx = pClient->m_pGameContext;
	if (!IsValidPtr(pGameCtx)) return;

	auto pPlayerMgr = pGameCtx->m_pPlayerManager;
	if (!IsValidPtr(pPlayerMgr)) return;

	static bool reHook = false;
	auto pLocal = pPlayerMgr->GetLocalPlayer();

	//Didn't came up with better idea then rehooking PreFrameUpdate vmTable to prevent 
	//crashes when leaving the server.
	if (!IsValidPtr(pLocal)) //nullptr when loading to the server
	{
		if (!reHook)
		{
			reHook = true;
			HooksManager::Get()->pPreFrameHook->Release();
		}
		return;
	}
	else if (reHook) //fully loaded
	{
		reHook = false;
		HooksManager::Get()->pPreFrameHook->Setup(BorderInputNode::GetInstance()->m_pInputNode);
		HooksManager::Get()->pPreFrameHook->Hook(Index::PRE_FRAME_UPDATE, HooksManager::PreFrameUpdate);
	}

	//Cfg::ESP::_internalPlayerIDs.clear();
	//SpoofNameClientSided(pLocal);

	auto pLocalSoldier = pLocal->GetSoldierEntity();
	if (!IsValidPtr(pLocalSoldier) || !pLocalSoldier->IsAlive()) return;

	if (!Cfg::ESP::enable) return;

	if (auto pVehicleTurret = VehicleTurret::GetInstance(); IsValidPtr(pVehicleTurret) && pLocal->InVehicle())
	{
		G::viewPos = pVehicleTurret->GetVehicleCameraOrigin();
		WorldToScreen(pVehicleTurret->GetVehicleCrosshair(), G::viewPos2D);
	}

	auto pMyMissile = GetMissileEntity(pGameCtx, pLocal);
	if (Cfg::ESP::explosives)
		RenderExplosives(pGameCtx);

	if (Cfg::DBG::vehicleCross && pLocal->InVehicle())
	{
		static auto prevPos = G::viewPos2D;
		auto delta = Misc::GetAbsDeltaAtGivenPoints(G::viewPos2D, prevPos);
		if (delta > 3)
		{
			Vector2D d = G::viewPos2D - prevPos;
			prevPos += d / 6.f;
		}
		else { prevPos = G::viewPos2D; }

		Renderer::DrawCircleOutlined(prevPos, 5, 15, ImColor::Red());
		Renderer::DrawRectFilled(prevPos, { prevPos.x + 1.f, prevPos.y + 1.f }, ImColor::Red());
	}

	//TESTING
	if (Cfg::DBG::debugEntities)
		RenderDebugEntities(pGameCtx, pMyMissile, pLocal, &PreUpdate::weaponData);

	if (Cfg::DBG::debugOutput)
		RenderVehicleInfo(pLocal, &PreUpdate::weaponData);

	//Disaplays every key press (useful when debugging)
	/*ImGui::PushFont(DX::Verdana12);
	float y = 0, x = 0;
	for (int i = 0; i < ConceptSize; i++)
	{
		auto& val = BorderInputNode::GetInstance()->m_inputCache->flInputBuffer[i];
		Renderer::DrawString({ 200 + x, y }, 0, val != 0.0f ? ImColor::Red() : ImColor::White(), "Inp[ %d ] = %.1f", 
			i, val);
		y += 8.f;
		if (y >= G::screenSize.y - 10) { y = 0; x += 150; }
	}
	ImGui::PopFont();*/

	
	static ClientPlayer*	pTargetPlayer = nullptr;
	static Vector			aimPoint3D = ZERO_VECTOR;
	static float			longestDelta = FLT_MAX;
	static int				targetID = -1;

	if (!targetLock)
	{
		pTargetPlayer = nullptr;
		aimPoint3D = ZERO_VECTOR;
		longestDelta = FLT_MAX;
		targetID = -1;
	}

	//TESTING SPECTATOR COUNTER
	float count = 0.f;

	for (int i = 0; i < 70; i++)
	{
		auto* pPlayer = pPlayerMgr->GetPlayerById(i);
		if (!IsValidPtr(pPlayer)) continue;

		if (Cfg::ESP::Radar::enable)
			RenderRadar(pLocal, pPlayer, i);

		if (pPlayer == pLocal) continue;

		bool isInTeam = pPlayer->m_TeamId == pLocal->m_TeamId;
		if (!Cfg::ESP::team && isInTeam) continue;

		//if (!isInTeam)
		//	PlayerList::list;

		//TESTING SPECTATOR LIST!
		{
			if (Cfg::DBG::spectators && pPlayer->m_IsSpectator)
			{
				Renderer::DrawString({ 20, 600 + count }, 0, ImColor::Purple(), xorstr_("%s is spectating"),
					pPlayer->m_Name);
				count += 15.f;
			}
		}

		auto* pSoldier = pPlayer->GetSoldierEntity();
		if (!IsValidPtr(pSoldier) || !pSoldier->IsAlive()) continue;

		//Dont aim at passengers (velocity is always 0 here idk why)
		if (pPlayer->m_EntryId == ClientPlayer::EntrySeatType::Passenger) continue;

		ImColor color = isInTeam ? Cfg::ESP::teamColor : Cfg::ESP::enemyColor;
		Vector vehicleCenter3D;
		Vector playerHead3D;

		if (!pPlayer->InVehicle())
		{
			BoundingBox3D playerBB3D;
			const auto& playerBB = GetEntityAABB(pSoldier, &playerBB3D);

			if (playerBB != BoundingBox::Zero())
			{
				if (Cfg::ESP::use3DplayerBox)
				{
					std::array<ImVec2, 8> playerPoints2D;
					bool valid = true;
					for (int i = 0; i < 8; i++)
					{
						WorldToScreen(playerBB3D.points[i], playerPoints2D[i]);
						if (playerPoints2D[i].x == 0.f || playerPoints2D[i].y == 0.f)
						{
							valid = false;
							break;
						}
					}
					if (valid) Renderer::DrawBox(playerPoints2D, color);
				}
				else RenderPlayerCorneredRect(playerBB, color);

				if (Cfg::ESP::lines)
					Renderer::DrawLine(
						{ G::screenSize.x * 0.5f, G::screenSize.y },
						{ playerBB.left + (playerBB.GetSize().x * 0.5f), playerBB.bot },
						Cfg::ESP::linesColor);
			}
		}

		std::array<ImVec2, 8> vehiclePoints2D;
		BoundingBox3D vehicleBB3D;
		if (Cfg::ESP::vehicles && pPlayer->InVehicle())
		{
			auto* pVehicle = pPlayer->GetVehicleEntity();
			if (pVehicle)
			{
				const auto& vehicleBB = GetEntityAABB(pVehicle, &vehicleBB3D);
				ImColor color = Cfg::ESP::vehicleAirColor;

				//There are many hardcoded colors here which you could change to your desire
				switch (pVehicle->m_pData->GetVehicleType())
				{
				case VehicleData::VehicleType::JET:
				case VehicleData::VehicleType::HELIATTACK:
				case VehicleData::VehicleType::JETBOMBER:
					color = ImColor(0, 179, 255, 90); break;
				case VehicleData::VehicleType::HELISCOUT:
				case VehicleData::VehicleType::HELITRANS:
				case VehicleData::VehicleType::UAV:
					color = ImColor(212, 255, 0, 90); break;
				case VehicleData::VehicleType::BOAT:
					color = ImColor(255, 111, 0, 90); break;
				case VehicleData::VehicleType::CAR:
				case VehicleData::VehicleType::EODBOT:
				case VehicleData::VehicleType::JEEP:
				case VehicleData::VehicleType::STATICAA:
				case VehicleData::VehicleType::STATICAT:
				case VehicleData::VehicleType::STATIONARY:
				case VehicleData::VehicleType::STATIONARYWEAPON:
					color = ImColor(77, 255, 0, 90); break;
				case VehicleData::VehicleType::TANK:
				case VehicleData::VehicleType::TANKARTY:
				case VehicleData::VehicleType::TANKAT:
				case VehicleData::VehicleType::TANKIFV:
				case VehicleData::VehicleType::TANKLC:
					color = Cfg::ESP::vehicleGroundColor; break;
				case VehicleData::VehicleType::TANKAA:
					color = ImColor(255, 0, 119, 90); break;
				default:
					color = Cfg::ESP::vehicleAirColor; break;
				}

				if (Cfg::ESP::use3DvehicleBox)
				{
					bool valid = true;
					for (int i = 0; i < 8; i++)
					{
						WorldToScreen(vehicleBB3D.points[i], vehiclePoints2D[i]);
						if (vehiclePoints2D[i].x == 0.f || vehiclePoints2D[i].y == 0.f)
						{
							valid = false;
							break;
						}
					}
					if (valid) Renderer::DrawBox(vehiclePoints2D, color);
				}
				else RenderPlayerCorneredRect(vehicleBB, color);

				if (Cfg::ESP::linesVehicles)
				{
					ImVec2 boxCenter = { vehicleBB.GetMin().x + vehicleBB.GetCenter().x, vehicleBB.GetMax().y };
					if (boxCenter != ZERO_VECTOR2D)
						Renderer::DrawLine(
							{ G::screenSize.x * 0.5f, G::screenSize.y },
							boxCenter,
							color);
				}
				else if (Cfg::ESP::vehicleIndicator && pLocal->InVehicle())
				{
					ImVec2 boxCenter = { vehicleBB.GetMin().x + vehicleBB.GetCenter().x, vehicleBB.GetMax().y };
					if (boxCenter != ZERO_VECTOR2D)
						Renderer::DrawLine(
							{ G::screenSize.x * 0.5f, G::screenSize.y * 0.5f },
							boxCenter,
							targetID == i ? ImColor::White(180) : color);
				}
			}
		}

		Vector tmpAimPoint3D = ZERO_VECTOR;
		auto pRagdoll = pSoldier->m_pRagdollComponent;

		//Check if we can grab players head position 
		if (!IsValidPtr(pRagdoll) || !pRagdoll->GetBone(UpdatePoseResultData::BONES::Head, tmpAimPoint3D))
		{
			//If not, try to get vehicle AABB center at least.
			if (pPlayer->InVehicle())
			{
				tmpAimPoint3D = vehicleBB3D.GetCenter();
				ImVec2 o;
				if (WorldToScreen(tmpAimPoint3D, o))
				{
					std::vector<ImVec2> points =
					{
						ImVec2(o.x, o.y - 5),
						ImVec2(o.x + 5, o.y),
						ImVec2(o.x, o.y + 5),
						ImVec2(o.x - 5, o.y),
						ImVec2(o.x, o.y - 5),
					};

					Renderer::DrawLine(points, Cfg::ESP::predictionCrossColor);
				}
			}
		}

		if (tmpAimPoint3D == ZERO_VECTOR) continue;

		//if (!isInTeam) RenderPlayerNames(pPlayer); //TODO;

		Vector2D aimPoint2D;
		WorldToScreen(tmpAimPoint3D, aimPoint2D);
		const auto delta = Misc::GetAbsDeltaAtGivenPoints(G::screenCenter, aimPoint2D);

		//Search for closest player to center of the screen
		if (!targetLock)
		{
			if (delta < longestDelta)
			{
				longestDelta = delta;
				pTargetPlayer = pPlayer;
				aimPoint3D = tmpAimPoint3D;
				targetID = i;
			}
		}
		else if (IsValidPtr(pPlayer) && (i == targetID))
			aimPoint3D = tmpAimPoint3D;
	}

	RenderBombImpact(aimPoint3D, &PreUpdate::weaponData);

	if (!IsValidPtr(pTargetPlayer)
		|| !IsValidPtr(pLocal)
		|| !IsValidPtr(pTargetPlayer->GetSoldierEntity())
		|| !pTargetPlayer->GetSoldierEntity()->IsAlive())
	{
		targetLock = false;
		if (!targetLock)
		{
			pTargetPlayer = nullptr;
			aimPoint3D = ZERO_VECTOR;
			longestDelta = FLT_MAX;
			targetID = -1;

		}
		return;
	}

	auto& preUpd = PreUpdate::preUpdatePlayersData;
	preUpd.pBestTarget = pTargetPlayer;
	preUpd.pMyMissile = pMyMissile;
	
	if (PreUpdate::predictionData.hitPos == ZERO_VECTOR || !PreUpdate::isPredicted) return;

	RenderAimPoint(PreUpdate::predictionData, pTargetPlayer);

	//Draws target's predicted AABB when flying in jet
	if (!PreUpdate::isValid) return;

	std::array<ImVec2, 8> pts;
	bool isValid = true;
	for (int i = 0; i < pts.size(); i++)
	{
		if (!WorldToScreen(PreUpdate::points[i], pts[i]))
		{
			isValid = false;
			break;
		}
	}

	if (isValid) Renderer::DrawBox(pts, ImColor::Green(90));
}

void Timer::ResetCounter()
{
	hasStartedCounting = false;
	elapsedTime = 0.0;
}

void Timer::StartCounting()
{
	if (hasStartedCounting) return;

	hasStartedCounting = true;
	start = std::chrono::high_resolution_clock::now();
}

void Timer::StopCounting()
{
	if (!hasStartedCounting) return;

	hasStartedCounting = false;
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	elapsedTime = elapsed.count();
}

double Timer::GetElapsedTime()
{
	return elapsedTime;
}

bool Timer::IsReadyThisTick()
{
	if (GetTime() - m_PrevTime <= m_Delay)
	{
		m_PrevTime = GetTime();
		return true;
	}
	return false;
}

double Timer::GetTime()
{
	return ImGui::GetTime();
}
