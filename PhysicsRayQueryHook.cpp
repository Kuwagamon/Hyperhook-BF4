#include "VMTHooking.h"
#include "Engine.h"

bool __fastcall HooksManager::PhysicsRayQuery(void* pThis, void* EDX, const char* identifier, D3DXVECTOR4* from, D3DXVECTOR4* to, RayCastHit* hit, int flag, void* PhysicsEntityList)
{
	static auto oPhysicsRayQuery = HooksManager::Get()->pRayCasterHook->GetOriginal<HooksManager::PhysicsRayQuery_t>(Index::PHYSICS_RAY_QUERY);

	//Secret conedz here:

	return oPhysicsRayQuery(pThis, EDX, identifier, from, to, hit, flag, PhysicsEntityList);
}