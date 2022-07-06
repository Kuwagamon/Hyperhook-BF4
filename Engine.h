#pragma once
#include <Windows.h>
#include <atlstr.h>
#include <string.h>
#ifdef GetClassName
#undef GetClassName
#endif

//Creds: https://github.com/stevemk14ebr/BF4-AtomBot/tree/master/BF4%20AtomBot/Engine

#ifdef ERROR
#undef ERROR
#define ERROR(str) MessageBoxA(NULL, str, xorstr_("Error"), MB_OK)
#endif

#define OFFSET_SSMODULE					0x14273D6E8 //checked 1.07.2021
#define OFFSET_BORDERINPUTNODE			0x142671fb0	//checked 1.07.2021
#define OFFSET_FIRSTTYPEINFO			0x1423E41B8	//checked 1.07.2021
#define OFFSET_ANTVTABLE				0x141BE4E00
#define OFFSET_GETENTITYLIST			0x1407CD5D0	//checked 1.07.2021
#define OFFSET_PPCURRENTWEAPONFIRING	0x1423B2EC8 //checked 1.07.2021
#define OFFSET_ANGLES					0x1423B2EC0	//checked 1.07.2021

#define OFFSET_MAIN						0x142364b78	//checked 1.07.2021
#define OFFSET_DXRENDERER				0x142738080	//checked 1.07.2021
#define OFFSET_CLIENTGAMECONTEXT		0x142670d80 //Checked 1.07.2021
#define OFFSET_GAMERENDERER				0x142672378	//checked 1.07.2021


#define OFFSET_WEAPONSHOOTSPACE OFFSET_PPCURRENTWEAPONFIRING + 0x28 //Weapon shootspace

#include <d3dx9.h>
typedef D3DXVECTOR3 Vector;
typedef D3DXVECTOR2 Vector2D;
typedef D3DXVECTOR4 Vector4;
typedef D3DXMATRIX Matrix;
typedef D3DXQUATERNION Quaternion;

#define ZERO_VECTOR Vector( 0.f, 0.f, 0.f )
#define ZERO_VECTOR2D Vector2D( 0.f, 0.f )

#include "TypeInfo.h"

//Thanks to: https://github.com/stevemk14ebr/PolyHook_2_0
#ifdef _WIN64
#define _PTR_MAX_VALUE ((PVOID)0x000F000000000000)
#else
#define _PTR_MAX_VALUE ((PVOID)0xFFF00000)
#endif
__forceinline bool IsValidPtr(PVOID p) { return (p >= (PVOID)0x10000) && (p < _PTR_MAX_VALUE) && p != nullptr; }


#pragma region FORWARD_DECLARATIONS
// Generated using ReClass 2014
struct AABB;
class DxRenderer;
class Screen;
class DxDisplaySettings;
class GameRenderer;
class GameRenderSettings;
class RenderView;
class BorderInputNode;
class UnneededClass;
class Keyboard;
class Mouse;
class Main;
class Server;
class GameSettings;
class ServerSettings;
class Client;
class ClientSettings;
class FileSystem;
class GameTimer;
class GameTimeSettings;
class ServerJobData;
class ClientGameContext;
class GameView;
class Online;
class InterpolationManager;
class PlayerManager;
class GameTime;
class Level;
class HavokPhysicsManager;
class TerrainPhysicsEntity;
class Physics;
class PhysicsSettings;
class PhysicsRenderSettings;
class IPhysicsRayCaster;
class HavokManager;
class LevelData;
class Connection;
class ClientPlayer;
class VeniceSoldierCustimizationAsset;
class CustomizationTable;
class Customization;
class ClientSoldierEntity;
class AntAnimatableComponent;
class GameAnimatable;
class SoldierWeaponComponent;
class AnimatedSoldierWeaponHandler;
class SoldierWeapon;
class SoldierAimingSimulation;
class AimAssist;
class TypeInfo;
class ClientWeapon;
class PrimaryFire;
class FiringFunctionData;
class ShotConfigData;
class BulletEntityData;
class ProjectileEntityData;
class WeaponSuppressionData;
class MessProjectileEntityData;
class SoundAsset;
class SoundScopeData;
class SoundScopeStrategyData;
class OverheatData;
class WeaponModifier;
class WeaponFiring;
class ClientSoldierBodyComponent;
class RagdollComponent;
class UpdatePoseResultData;
class QuatTransform;
class ParachuteComponent;
class SpottingComponent;
class SpottingTargetComponent;
class VaultComponent;
class SoldierSuppressionComponent;
class ClientControllableEntity;
class HealthComponent;
class WeaponShotModifier;
class SoundModifier;
class FiringEffectsModifier;
class FiringDataModifier;
class ProjectileModifier;
class AimingSimulationModifier;
class ZeroingModifier;
class WeaponSway;
class GunSwayData;
class VeniceClientMissileEntity;
class MissileEntityData;
class EntryComponent;
class ClientWeaponComponent;
class WeaponComponentData;
class ClientGameWorld;
class ClientExplosionEntity;
class ClientVehicleEntity;
class PhysicsEntityBase;
class ClientIndirectFireWeapon;
class StaticCamera;
struct WeaponData_s;
class ViewAnglesClass;
class AxisAlignedBox;
class ID3D11Device;
class ID3D11DeviceContext;
#pragma endregion

template< class T > class WeakPtr
{
private:
	T** m_ptr;

public:
	T* GetData()
	{
		if (!m_ptr)
			return NULL;

		if (!*m_ptr)
			return NULL;

		T* ptr = *m_ptr;

		return (T*)((DWORD64)ptr - 0x8);
	}
};

class DxRenderer
{
public:
	BYTE pad00[0x38];                    // 0x00
	Screen* m_pScreen;                    // 0x38
	BYTE pad78[0xC0];                    // 0x40
	//ID3D11Device* m_pDevice;            // 0x100
	//ID3D11DeviceContext* m_pContext;    // 0x108
	//char _0x0110[192];
	//void* m_settings; //0x01D0 

	static DxRenderer* GetInstance()
	{
		return *(DxRenderer**)OFFSET_DXRENDERER;
	}
};//Size=0x0110

class Screen
{
public:
	BYTE pad00[0x58];				//0x00
	unsigned int m_Width;			//0x58
	unsigned int m_Height;			//0x5C
	unsigned int m_WindowWidth;			//0x60
	unsigned int m_WindowHeight;		//0x64
	//BYTE pad01[0x88];				//0x68
	//IDXGISwapChain* m_pSwapChain;		//0xF0
};

class DxDisplaySettings
{
public:
	char _0x0000[40];
	__int32 m_FullscreenHeight; //0x0028 
	__int32 m_FullscreenWidth; //0x002C 
	float m_RefreshRate; //0x0030 
	__int32 m_FullscreenOutputIndex; //0x0034 
	__int32 m_PresentInterval; //0x0038 
	__int32 m_PresentImmediateThreshold; //0x003C 
	__int32 m_RenderAheadLimit; //0x0040 
	float m_StereoDepth; //0x0044 
	float m_StereoConvergeanceScale; //0x0048 
	float m_StereoSeparationScale; //0x004C 
	float m_StereoSoldierZoomConvergeanceScale; //0x0050 
	__int32 m_NVIDIAMinDriverVersion; //0x0054 
	char* m_AMDMinDriverVersion; //0x0058 
	float m_LowResDisplayPlaneScale; //0x0060 
	char _0x0064[52];

};//Size=0x0098

class GameRenderer
{
public:
	char _0x0000[72];
	GameRenderSettings* m_RenderSettings; //0x0048 
	char _0x0050[16];
	RenderView* m_pRenderView; //0x0060 

	static GameRenderer* GetInstance()
	{
		return *(GameRenderer**)OFFSET_GAMERENDERER;
	}

	bool IsInFirstPersonView()
	{
		return *(bool*)((uintptr_t)this + 0x128);
	}
};//Size=0x0068

class GameRenderSettings
{
public:
	char pad[16];
	unsigned __int32 m_InactiveSkipFrameCount; //0x0010
	float m_ResolutionScale; //0x0014
	__int32 m_MantleEnable; //0x0018
	unsigned __int32 m_XenonRingBufferSize; //0x001C
	unsigned __int32 m_XenonLinearFrameBufferSize; //0x0020
	unsigned __int32 m_XenonPresentImmediateThreshold; //0x0024
	unsigned __int32 m_XenonGammaRampType; //0x0028
	float m_Ps3VideoGamma; //0x002C
	unsigned __int32 m_Ps3FrameMainBufferSize; //0x0030
	unsigned __int32 m_Ps3FrameLocalBufferSize; //0x0034
	unsigned __int32 m_Ps3VSyncMethod; //0x0038
	float m_CameraCutMaxFrameTranslation; //0x003C
	float m_NearPlane; //0x0040
	float m_ViewDistance; //0x0044
	float m_ForceFov; //0x0048
	float m_FovMultiplier; //0x004C
	float m_ForceOrthoViewSize; //0x0050
	float m_EdgeModelScreenAreaScale; //0x0054
	float m_EdgeModelViewDistance; //0x0058
	__int32 m_EdgeModelForceLod; //0x005C
	float m_EdgeModelLodScale; //0x0060
	unsigned __int32 m_EdgeModelMaxVisibleInstanceCount; //0x0064
	float m_StaticModelPartOcclusionMaxScreenArea; //0x0068
	unsigned __int32 m_StaticModelCullJobCount; //0x006C
	unsigned __int32 m_SplitScreenTestViewCount; //0x0070
	unsigned __int32 m_SplitScreenTestCase; //0x0074
	float m_ForceBlurAmount; //0x0078
	float m_ForceWorldFadeAmount; //0x007C
	float m_StereoCrosshairMaxHitDepth; //0x0080
	float m_StereoCrosshairRadius; //0x0084
	float m_StereoCrosshairDampingFactor; //0x0088
	bool m_Enable; //0x008C
	bool m_NullRendererEnable; //0x008D
	bool m_JobEnable; //0x008E
	bool m_BuildJobSyncEnable; //0x008F
	bool m_EarlyGpuSyncEnable; //0x0090
	bool m_DrawDebugInfo; //0x0091
	bool m_DrawScreenInfo; //0x0092
	bool m_Fullscreen; //0x0093
	bool m_ForceVSyncEnable; //0x0094
	bool m_MovieVSyncEnable; //0x0095
	bool m_VSyncFlashTestEnable; //0x0096
	bool m_OutputBrightnessTestEnable; //0x0097
	bool m_XenonBufferTwoFramesEnable; //0x0098
	bool m_XenonRes1280x704Enable; //0x0099
	bool m_Ps3LinearFrameCmdBufEnable; //0x009A
	bool m_Ps3CellMemoryTexturesEnable; //0x009B
	bool m_GcmHudEnable; //0x009C
	bool m_Ps3Res1280x704Enable; //0x009D
	bool m_Gen4bColorRemap; //0x009E
	bool m_GpuTextureCompressorEnable; //0x009F
	bool m_EmittersEnable; //0x00A0
	bool m_EntityRenderEnable; //0x00A1
	bool m_DebugRendererEnable; //0x00A2
	bool m_DebugRenderServiceEnable; //0x00A3
	bool m_InitialClearEnable; //0x00A4
	bool m_GpuProfilerEnable; //0x00A5
	bool m_ForceOrthoViewEnable; //0x00A6
	bool m_ForceSquareOrthoView; //0x00A7
	bool m_DestructionVolumeDrawEnable; //0x00A8
	bool m_EdgeModelsEnable; //0x00A9
	bool m_EdgeModelCastShadowsEnable; //0x00AA
	bool m_EdgeModelDepthBiasEnable; //0x00AB
	bool m_EdgeModelShadowDepthBiasEnable; //0x00AC
	bool m_EdgeModelSpuInstancingEnable; //0x00AD
	bool m_EdgeModelUseMainLodEnable; //0x00AE
	bool m_EdgeModelUseLodBox; //0x00AF
	bool m_EdgeModelCullEnable; //0x00B0
	bool m_EdgeModelFrustumCullEnable; //0x00B1
	bool m_EdgeModelOcclusionCullEnable; //0x00B2
	bool m_EdgeModelDrawBoxes; //0x00B3
	bool m_EdgeModelDrawStats; //0x00B4
	bool m_StaticModelEnable; //0x00B5
	bool m_StaticModelMeshesEnable; //0x00B6
	bool m_StaticModelZPassEnable; //0x00B7
	bool m_StaticModelPartCullEnable; //0x00B8
	bool m_StaticModelPartFrustumCullEnable; //0x00B9
	bool m_StaticModelPartOcclusionCullEnable; //0x00BA
	bool m_StaticModelPartShadowCullEnable; //0x00BB
	bool m_StaticModelDrawBoxes; //0x00BC
	bool m_StaticModelDrawStats; //0x00BD
	bool m_StaticModelCullSpuJobEnable; //0x00BE
	bool m_StaticModelSurfaceShaderTerrainAccessEnable; //0x00BF
	bool m_LockView; //0x00C0
	bool m_ResetLockedView; //0x00C1
	bool m_SecondaryStreamingViewEnable; //0x00C2
	bool m_FadeEnable; //0x00C3
	bool m_FadeWaitingEnable; //0x00C4
	bool m_BlurEnable; //0x00C5
	char _0x00C6[2];
};//Size=0x0040

class RenderView
{
public:
	char _0x0000[64];

	D3DXMATRIX m_Transform; //0x0040 
	char _0x0080[52];
	float m_FovY; //0x00B4 
	float m_DefaultFovY; //0x00B8 
	float m_NearPlane; //0x00BC 
	float m_FarPlane; //0x00C0 
	float m_AspectRatio; //0x00C4 
	float m_OrthoWidth; //0x00C8 
	float m_OrthoHeight; //0x00CC 
	char _0x00D0[384];
	float m_FovX; //0x0250 
	float m_DepthHeightRatio; //0x0254 
	float m_FovScale; //0x0258 
	float m_FovScaleSquared; //0x025C 
	D3DXMATRIX  m_View; //0x0260 
	D3DXMATRIX  m_ViewTranspose; //0x02A0 
	D3DXMATRIX  m_ViewInverse; //0x02E0 
	D3DXMATRIX  m_Projection; //0x0320 
	D3DXMATRIX  m_ViewAtOrigin; //0x0360 
	D3DXMATRIX  m_ProjectionTranspose; //0x03A0 
	D3DXMATRIX  m_ProjectionInverse; //0x03E0 
	D3DXMATRIX  m_ViewProjection; //0x0420 
	D3DXMATRIX  m_ViewProjectionTranspose; //0x0460 
	D3DXMATRIX  m_ViewProjectionInverse; //0x04A0 

};//Size=0x04E0

enum InputConceptIdentifiers
{
	ConceptMoveFB = 0x0,
	ConceptMoveLR = 0x1,
	ConceptMoveForward = 0x2,
	ConceptMoveBackward = 0x3,
	ConceptMoveLeft = 0x4,
	ConceptMoveRight = 0x5,
	ConceptYaw = 0x6,
	ConceptPitch = 0x7,
	ConceptRoll = 0x8,
	ConceptRecenterCamera = 0x9,
	ConceptFire = 0xa,
	ConceptAltFire = 0xb,
	ConceptFireCountermeasure = 0xc,
	ConceptReload = 0xd,
	ConceptZoom = 0xe,
	ConceptToggleCamera = 0xf,
	ConceptSprint = 0x10,
	ConceptCrawl = 0x11,
	ConceptToggleWeaponLight = 0x12,
	ConceptSelectPartyMember0 = 0x13,
	ConceptSelectPartyMember1 = 0x14,
	ConceptSelectPartyMember2 = 0x15,
	ConceptSelectPartyMember3 = 0x16,
	ConceptLockTarget = 0x17,
	ConceptCrosshairMoveX = 0x18,
	ConceptCrosshairMoveY = 0x19,
	ConceptTacticalMenu = 0x1a,
	ConceptConversationSelect = 0x1b,
	ConceptConversationSkip = 0x1c,
	ConceptConversationChangeSelection = 0x1d,
	ConceptJump = 0x1e,
	ConceptCrouch = 0x1f,
	ConceptCrouchOnHold = 0x20,
	ConceptProne = 0x21,
	ConceptInteract = 0x22,
	ConceptPickUp = 0x23,
	ConceptDrop = 0x24,
	ConceptBreathControl = 0x25,
	ConceptParachute = 0x26,
	ConceptSwitchInventoryItem = 0x27,
	ConceptSelectInventoryItem1 = 0x28,
	ConceptSelectInventoryItem2 = 0x29,
	ConceptSelectInventoryItem3 = 0x2a,
	ConceptSelectInventoryItem4 = 0x2b,
	ConceptSelectInventoryItem5 = 0x2c,
	ConceptSelectInventoryItem6 = 0x2d,
	ConceptSelectInventoryItem7 = 0x2e,
	ConceptSelectInventoryItem8 = 0x2f,
	ConceptSelectInventoryItem9 = 0x30,
	ConceptSwitchToPrimaryWeapon = 0x31,
	ConceptSwitchToGrenadeLauncher = 0x32,
	ConceptSwitchToStaticGadget = 0x33,
	ConceptSwitchToDynamicGadget1 = 0x34,
	ConceptSwitchToDynamicGadget2 = 0x35,
	ConceptMeleeAttack = 0x36,
	ConceptThrowGrenade = 0x37,
	ConceptCycleFireMode = 0x38,
	ConceptChangeVehicle = 0x39,
	ConceptBrake = 0x3a,
	ConceptHandBrake = 0x3b,
	ConceptClutch = 0x3c,
	ConceptGearUp = 0x3d,
	ConceptGearDown = 0x3e,
	ConceptGearSwitch = 0x3f,
	ConceptNextPosition = 0x40,
	ConceptSelectPosition1 = 0x41,
	ConceptSelectPosition2 = 0x42,
	ConceptSelectPosition3 = 0x43,
	ConceptSelectPosition4 = 0x44,
	ConceptSelectPosition5 = 0x45,
	ConceptSelectPosition6 = 0x46,
	ConceptSelectPosition7 = 0x47,
	ConceptSelectPosition8 = 0x48,
	ConceptCameraPitch = 0x49,
	ConceptCameraYaw = 0x4a,
	ConceptMapZoom = 0x4b,
	ConceptMapInnerZoom = 0x4c,
	ConceptMapSize = 0x4d,
	ConceptMapThreeDimensional = 0x4e,
	ConceptScoreboard = 0x4f,
	ConceptScoreboardAndMenuCombo = 0x50,
	ConceptMenu = 0x51,
	ConceptSpawnMenu = 0x52,
	ConceptCancel = 0x53,
	ConceptCommMenu1 = 0x54,
	ConceptCommMenu2 = 0x55,
	ConceptCommMenu3 = 0x56,
	ConceptAccept = 0x57,
	ConceptDecline = 0x58,
	ConceptSelect = 0x59,
	ConceptBack = 0x5a,
	ConceptActivate = 0x5b,
	ConceptDeactivate = 0x5c,
	ConceptEdit = 0x5d,
	ConceptView = 0x5e,
	ConceptParentNavigateLeft = 0x5f,
	ConceptParentNavigateRight = 0x60,
	ConceptMenuZoomIn = 0x61,
	ConceptMenuZoomOut = 0x62,
	ConceptPanX = 0x63,
	ConceptPanY = 0x64,
	ConceptBattledashToggle = 0x65,
	ConceptVoiceFunction1 = 0x66,
	ConceptSquadVoice = 0x67,
	ConceptSayAllChat = 0x68,
	ConceptTeamChat = 0x69,
	ConceptSquadChat = 0x6a,
	ConceptSquadLeaderChat = 0x6b,
	ConceptToggleChat = 0x6c,
	ConceptQuicktimeInteractDrag = 0x6d,
	ConceptQuicktimeFire = 0x6e,
	ConceptQuicktimeBlock = 0x6f,
	ConceptQuicktimeFastMelee = 0x70,
	ConceptQuicktimeJumpClimb = 0x71,
	ConceptQuicktimeCrouchDuck = 0x72,
	ConceptFreeCameraMoveUp = 0x73,
	ConceptFreeCameraMoveDown = 0x74,
	ConceptFreeCameraMoveLR = 0x75,
	ConceptFreeCameraMoveFB = 0x76,
	ConceptFreeCameraMoveUD = 0x77,
	ConceptFreeCameraRotateX = 0x78,
	ConceptFreeCameraRotateY = 0x79,
	ConceptFreeCameraRotateZ = 0x7a,
	ConceptFreeCameraIncreaseSpeed = 0x7b,
	ConceptFreeCameraDecreaseSpeed = 0x7c,
	ConceptFreeCameraFOVModifier = 0x7d,
	ConceptFreeCameraChangeFOV = 0x7e,
	ConceptFreeCameraSwitchSpeed = 0x7f,
	ConceptFreeCameraTurboSpeed = 0x80,
	ConceptFreeCameraActivator1 = 0x81,
	ConceptFreeCameraActivator2 = 0x82,
	ConceptFreeCameraActivator3 = 0x83,
	ConceptFreeCameraMayaInputActivator = 0x84,
	ConceptTargetedCameraDistance = 0x85,
	ConceptTargetedCameraRotateX = 0x86,
	ConceptTargetedCameraRotateY = 0x87,
	ConceptTargetedCameraChangeSpeed = 0x88,
	ConceptLThumb = 0x89,
	ConceptRThumb = 0x8a,
	ConceptLeftStickX = 0x8b,
	ConceptLeftStickY = 0x8c,
	ConceptRightStickX = 0x8d,
	ConceptRightStickY = 0x8e,
	ConceptButtonDPadLeft = 0x8f,
	ConceptButtonDPadRight = 0x90,
	ConceptButtonDPadUp = 0x91,
	ConceptButtonDPadDown = 0x92,
	ConceptButtonA = 0x93,
	ConceptButtonB = 0x94,
	ConceptButtonX = 0x95,
	ConceptButtonY = 0x96,
	ConceptButtonSelect = 0x97,
	ConceptButtonStart = 0x98,
	ConceptButtonL1 = 0x99,
	ConceptButtonL2 = 0x9a,
	ConceptButtonR1 = 0x9b,
	ConceptButtonR2 = 0x9c,
	ConceptButtonLeftThumb = 0x9d,
	ConceptButtonRightThumb = 0x9e,
	ConceptToggleMinimapType = 0x9f,
	ConceptDeployZoom = 0xa0,
	ConceptMenuDigitalUp = 0xa1,
	ConceptMenuDigitalDown = 0xa2,
	ConceptMenuDigitalLeft = 0xa3,
	ConceptMenuDigitalRight = 0xa4,
	ConceptRightStickUp = 0xa5,
	ConceptRightStickDown = 0xa6,
	ConceptRightStickLeft = 0xa7,
	ConceptRightStickRight = 0xa8,
	ConceptMultipleSelect = 0xa9,
	ConceptSelectAll = 0xaa,
	ConceptMinimize = 0xab,
	ConceptMoveCameraUp = 0xac,
	ConceptMoveCameraDown = 0xad,
	ConceptMoveCameraLeft = 0xae,
	ConceptMoveCameraRight = 0xaf,
	ConceptSelectSquad1 = 0xb0,
	ConceptSelectSquad2 = 0xb1,
	ConceptSelectSquad3 = 0xb2,
	ConceptSelectSquad4 = 0xb3,
	ConceptSelectSquad5 = 0xb4,
	ConceptSelectSquad6 = 0xb5,
	ConceptSelectSquad7 = 0xb6,
	ConceptSelectSquad8 = 0xb7,
	ConceptSelectSquad9 = 0xb8,
	ConceptSpectatorViewPrev = 0xb9,
	ConceptSpectatorViewNext = 0xba,
	ConceptSpectatorTargetPrev = 0xbb,
	ConceptSpectatorTargetNext = 0xbc,
	ConceptSpectatorViewTableTop = 0xbd,
	ConceptSpectatorViewFirstPerson = 0xbe,
	ConceptSpectatorViewThirdPerson = 0xbf,
	ConceptSpectatorViewFreeCam = 0xc0,
	ConceptSpectatorViewPlayer1 = 0xc1,
	ConceptSpectatorViewPlayer2 = 0xc2,
	ConceptSpectatorViewPlayer3 = 0xc3,
	ConceptSpectatorViewPlayer4 = 0xc4,
	ConceptSpectatorViewPlayer5 = 0xc5,
	ConceptSpectatorViewPlayer6 = 0xc6,
	ConceptSpectatorViewPlayer7 = 0xc7,
	ConceptSpectatorViewPlayer8 = 0xc8,
	ConceptSpectatorViewPlayer9 = 0xc9,
	ConceptSpectatorViewPlayer10 = 0xca,
	ConceptSpectatorViewPlayer11 = 0xcb,
	ConceptSpectatorViewPlayer12 = 0xcc,
	ConceptSpectatorViewPlayer13 = 0xcd,
	ConceptSpectatorViewPlayer14 = 0xce,
	ConceptSpectatorViewPlayer15 = 0xcf,
	ConceptSpectatorViewPlayer16 = 0xd0,
	ConceptSpectatorViewOptions = 0xd1,
	ConceptSpectatorHudVisibility = 0xd2,
	ConceptAnalogZoom = 0xd3,
	ConceptSpectatorTargetPrevInSquad = 0xd4,
	ConceptSpectatorTargetNextInSquad = 0xd5,
	ConceptSpectatorTargetPrevOnTeam = 0xd6,
	ConceptSpectatorTargetNextOnTeam = 0xd7,
	ConceptSpectatorFreeCameraIncreaseSpeed = 0xd8,
	ConceptSpectatorFreeCameraDecreaseSpeed = 0xd9,
	ConceptSpectatorFreeCameraSwitchSpeed = 0xda,
	ConceptSpectatorFreeCameraMoveLR = 0xdb,
	ConceptSpectatorFreeCameraMoveUD = 0xdc,
	ConceptSpectatorFreeCameraMoveFB = 0xdd,
	ConceptSpectatorFreeCameraRotateX = 0xde,
	ConceptSpectatorFreeCameraRotateY = 0xdf,
	ConceptSpectatorFreeCameraRotateZ = 0xe0,
	ConceptSpectatorFreeCameraTurboSpeed = 0xe1,
	ConceptSpectatorFreeCameraFOVModifier = 0xe2,
	ConceptSpectatorFreeCameraChangeFOV = 0xe3,
	ConceptSpectatorSquadLeft = 0xe4,
	ConceptSpectatorSquadRight = 0xe5,
	ConceptSpectatorSquadUp = 0xe6,
	ConceptSpectatorSquadDown = 0xe7,
	ConceptSpectatorSquadActivate = 0xe8,
	ConceptTwinkleReload = 0xe9,
	ConceptTwinkleAccept = 0xea,
	ConceptTwinkleDecline = 0xeb,
	ConceptTwinkleOption1 = 0xec,
	ConceptTwinkleOption2 = 0xed,
	ConceptTwinkleOption3 = 0xee,
	ConceptTwinkleOption4 = 0xef,
	ConceptTwinklePrevious = 0xf0,
	ConceptTwinkleNext = 0xf1,
	ConceptTwinkleHome = 0xf2,
	ConceptTwinkleEnd = 0xf3,
	ConceptTwinkleUp = 0xf4,
	ConceptTwinkleDown = 0xf5,
	ConceptTwinkleLeft = 0xf6,
	ConceptTwinkleRight = 0xf7,
	ConceptTwinkleSelect = 0xf8,
	ConceptTwinkleStart = 0xf9,
	ConceptTwinkleScrollUp = 0xfa,
	ConceptTwinkleScrollDown = 0xfb,
	ConceptUndefined = 0xfc,
	ConceptSize = 0xfd,
};

class BorderInputNode
{
public:
	class InputCache
	{
	public:
		char pad_0x0000[4];
		float flInputBuffer[/*223*/253];
	};

	virtual void Init();
	virtual void Exit();

	InputCache* m_inputCache; //0x0008 
	char _0x0010[48];
	/*InputNode**/ void* m_pInputNode; //0x0040 
	char _0x0048[8];
	Keyboard* m_pKeyboard; //0x0050 
	Mouse* m_pMouse; //0x0058

	static BorderInputNode* GetInstance()
	{
		return *(BorderInputNode**)OFFSET_BORDERINPUTNODE;
	}
};//Size=0x0088

class Keyboard
{
public:
	/*virtual void Function0();
	virtual void Function1();
	virtual void Update(); // this
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void SetMode(bool); // to set typing mode
	virtual void Function8();*/

	enum class InputKeys
	{
		IDK_None = 0,
		IDK_Escape = 1,
		IDK_1 = 2,
		IDK_2 = 3,
		IDK_3 = 4,
		IDK_4 = 5,
		IDK_5 = 6,
		IDK_6 = 7,
		IDK_7 = 8,
		IDK_8 = 9,
		IDK_9 = 10,
		IDK_0 = 11,
		IDK_Minus = 12,
		IDK_Equals = 13,
		IDK_Backspace = 14,
		IDK_Tab = 15,
		IDK_Q = 16,
		IDK_W = 17,
		IDK_E = 18,
		IDK_R = 19,
		IDK_T = 20,
		IDK_Y = 21,
		IDK_U = 22,
		IDK_I = 23,
		IDK_O = 24,
		IDK_P = 25,
		IDK_LeftBracket = 26,
		IDK_RightBracket = 27,
		IDK_Enter = 28,
		IDK_LeftCtrl = 29,
		IDK_A = 30,
		IDK_S = 31,
		IDK_D = 32,
		IDK_F = 33,
		IDK_G = 34,
		IDK_H = 35,
		IDK_J = 36,
		IDK_K = 37,
		IDK_L = 38,
		IDK_Semicolon = 39,
		IDK_Apostrophe = 40,
		IDK_Grave = 41,
		IDK_LeftShift = 42,
		IDK_Backslash = 43,
		IDK_Z = 44,
		IDK_X = 45,
		IDK_C = 46,
		IDK_V = 47,
		IDK_B = 48,
		IDK_N = 49,
		IDK_M = 50,
		IDK_Comma = 51,
		IDK_Period = 52,
		IDK_Slash = 53,
		IDK_RightShift = 54,
		IDK_Multiply = 55,
		IDK_LeftAlt = 56,
		IDK_Space = 57,
		IDK_Capital = 58,
		IDK_F1 = 59,
		IDK_F2 = 60,
		IDK_F3 = 61,
		IDK_F4 = 62,
		IDK_F5 = 63,
		IDK_F6 = 64,
		IDK_F7 = 65,
		IDK_F8 = 66,
		IDK_F9 = 67,
		IDK_F10 = 68,
		IDK_Numlock = 69,
		IDK_ScrollLock = 70,
		IDK_Numpad7 = 71,
		IDK_Numpad8 = 72,
		IDK_Numpad9 = 73,
		IDK_Subtract = 74,
		IDK_Numpad4 = 75,
		IDK_Numpad5 = 76,
		IDK_Numpad6 = 77,
		IDK_Add = 78,
		IDK_Numpad1 = 79,
		IDK_Numpad2 = 80,
		IDK_Numpad3 = 81,
		IDK_Numpad0 = 82,
		IDK_Decimal = 83,
		IDK_OEM_102 = 86,
		IDK_F11 = 87,
		IDK_F12 = 88,
		IDK_F13 = 100,
		IDK_F14 = 101,
		IDK_F15 = 102,
		IDK_Kana = 112,
		IDK_PTBRSlash = 115,
		IDK_Convert = 121,
		IDK_NoConvert = 123,
		IDK_Yen = 125,
		IDK_PTBRNUMPADPOINT = 126,
		IDK_NumpadEquals = 141,
		IDK_PrevTrack = 144,
		IDK_At = 145,
		IDK_Colon = 146,
		IDK_Underline = 147,
		IDK_Kanji = 148,
		IDK_Stop = 149,
		IDK_Ax = 150,
		IDK_Unlabeled = 151,
		IDK_NextTrack = 153,
		IDK_NumpadEnter = 156,
		IDK_RightCtrl = 157,
		IDK_Mute = 160,
		IDK_Calculator = 161,
		IDK_PlayPause = 162,
		IDK_MediaStop = 164,
		IDK_VolumeDown = 174,
		IDK_VolumeUp = 176,
		IDK_WebHome = 178,
		IDK_NumpadComma = 179,
		IDK_Divide = 181,
		IDK_PrintScreen = 183,
		IDK_RightAlt = 184,
		IDK_Home = 199,
		IDK_ArrowUp = 200,
		IDK_PageUp = 201,
		IDK_ArrowLeft = 203,
		IDK_ArrowRight = 205,
		IDK_End = 207,
		IDK_ArrowDown = 208,
		IDK_PageDown = 209,
		IDK_Insert = 210,
		IDK_Delete = 211,
		IDK_LeftWin = 219,
		IDK_RightWin = 220,
		IDK_AppMenu = 221,
		IDK_Power = 222,
		IDK_Sleep = 223,
		IDK_Wake = 227,
		IDK_WebSearch = 229,
		IDK_WebFavorites = 230,
		IDK_WebRefresh = 231,
		IDK_WebStop = 232,
		IDK_WebForward = 233,
		IDK_WebBack = 234,
		IDK_MyComputer = 235,
		IDK_Mail = 236,
		IDK_MediaSelect = 237,
		IDK_Pause = 197,
		IDK_Undefined = 255
	};

	class KeyboardDevice
	{
	public:
		virtual void Function0(); // 0x0000
		virtual void Read(float SampleTime, bool VisualFrame); //0x0008 
		virtual const char* Name(unsigned int); //0x0010 
		virtual const char* Name(void); // 0x0018 
		virtual unsigned int ControlCount(); // 0x0020 
		virtual bool IsConnected(); // 0x0028
		virtual bool IsAnalogue(unsigned int); // 0x0030
		virtual float GetValue(unsigned int);	// 0x0038

		char _0x0008[144];
		__int64 m_HWND; //0x0098 
		__int64 m_pWindowProcedure; //0x00A0 fb::WindowProcedure( ) 
		unsigned char m_Current[0x100]; //0x00A8
		unsigned char m_Buffer[0x100]; //0x01A8
		BYTE m_TypingMode; //0x02A8 
		BYTE m_HasOverflowed; //0x02A9 
		__int32 m_CodePage; //0x02AA 
		char _0x02AE[2];
	}; //Size = 0x02B0

	class KeyboardActionData
	{
	public:
		char _0x0000[16];
		BYTE m_IsAnalog; //0x0010 
		BYTE m_NegateValue; //0x0011 
		char _0x0012[14];
	}; //Size = 0x0020

	char _0x0000[8];
	KeyboardDevice* m_pDevice; //0x0008 
	char _0x0010[136];
	KeyboardActionData* m_pActionData; //0x0098
	char _0x00A0[24];
};//Size=0x0010

class Mouse
{
public:
	/*virtual void Function0();
	virtual void Function1();
	virtual void Update(); // this
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void SetMode(bool); // to set typing mode
	virtual void Function8();*/

	enum class InputButtons : BYTE
	{
		IDB_Button_0 = 0,
		IDB_Button_1 = 1,
		IDB_Button_2 = 2,
		IDB_Button_3 = 3,
		IDB_Button_4 = 4,
		IDB_Button_5 = 5,
		IDB_Button_6 = 6,
		IDB_Button_7 = 7,
		IDB_Button_Undefined = 8
	};

public:
	class MouseDevice
	{
	public:
		class MouseState
		{
		public:
			long x; //0x0000
			long y; //0x0004
			long z; //0x0008
			unsigned char buttons[0x8]; //0x000C
		};

		virtual void Function0(); // 0x0000
		virtual void Read(float SampleTime, bool VisualFrame); //0x0008 
		virtual const char* Name(void); //0x0010 
		virtual const char* Name(unsigned int); // 0x0018 
		virtual unsigned int ControlCount(); // 0x0020 
		virtual bool IsConnected(); // 0x0028
		virtual bool IsAnalogue(unsigned int); // 0x0030
		virtual float GetValue(unsigned int);	// 0x0038

		char _0x0008[144];
		__int64 m_HWND; //0x0098 
		__int64 m_pWindowProcedure; //0x00A0 
		char _0x00A8[40];
		BYTE m_CursorMode; //0x00D0 
		BYTE m_UIOwnsInput; //0x00D1 
		BYTE m_ShowCursor; //0x00D2 
		BYTE m_CursorConfined; //0x00D3 
		BYTE m_HasOverflowed; //0x00D4 
		BYTE m_UseRawMouseInput; //0x00D5 
		BYTE m_WindowActive; //0x00D6 
		char _0x00D7[25];
		MouseState m_Current; //0x00F0
		MouseState m_Buffer; //0x0104
		char _0x0118[24];

	}; //Size = 0x0130

	char _0x0000[16];
	MouseDevice* m_pDevice; // 0x0010


};//Size=0x0040


class ServerJobData
{
public:
	char _0x0000[136];
	Server* m_pServer; //0x0088 
	ClientGameContext* m_pGameContext; //0x0090 
	__int64 m_pParams; //0x0098 
};//Size=0x00A0

class ClientSettings
{
public:
	char pad[32];
	float m_JuiceDistanceThreshold; //0x0020
	float m_JuiceTimeThreshold; //0x0024
	float m_JuiceVehicleDistanceThreshold; //0x0028
	float m_JuiceVehicleTimeThreshold; //0x002C
	char* m_ScreenshotFilename; //0x0030
	char* m_ScreenshotSuffix; //0x0038
	unsigned __int32 m_Team; //0x0040
	__int32 m_SpawnPointIndex; //0x0044
	char* m_ServerIp; //0x0048
	char* m_SecondaryServerIp; //0x0050
	float m_AimScale; //0x0058
	float m_MouseSensitivityMin; //0x005C
	float m_MouseSensitivitySliderRange; //0x0060
	float m_MouseSensitivityFactor; //0x0064
	float m_MouseSensitivityPower; //0x0068
	float m_XenonGamepadDeadZoneCenter; //0x006C
	float m_XenonGamepadDeadZoneAxis; //0x0070
	float m_XenonGamepadDeadZoneOffsetAxis; //0x0074
	float m_PS3GamepadDeadZoneCenter; //0x0078
	float m_PS3GamepadDeadZoneAxis; //0x007C
	float m_PS3GamepadDeadZoneOffsetAxis; //0x0080
	float m_PCGamepadDeadZoneCenter; //0x0084
	float m_PCGamepadDeadZoneAxis; //0x0088
	float m_PCGamepadDeadZoneOffsetAxis; //0x008C
	float m_Gen4aGamepadDeadZoneCenter; //0x0090
	float m_Gen4aGamepadDeadZoneAxis; //0x0094
	float m_Gen4aGamepadDeadZoneOffsetAxis; //0x0098
	float m_Gen4bGamepadDeadZoneCenter; //0x009C
	float m_Gen4bGamepadDeadZoneAxis; //0x00A0
	float m_Gen4bGamepadDeadZoneOffsetAxis; //0x00A4
	char* m_GamepadGuid; //0x00A8
	float m_IncomingFrequency; //0x00B0
	unsigned __int32 m_IncomingRate; //0x00B4
	unsigned __int32 m_OutgoingRate; //0x00B8
	float m_LoadingTimeout; //0x00BC
	float m_LoadedTimeout; //0x00C0
	float m_IngameTimeout; //0x00C4
	bool m_IsSpectator; //0x00C8
	bool m_VsyncEnable; //0x00C9
	bool m_VisualFrameInterpolation; //0x00CA
	bool m_DebrisClusterEnabled; //0x00CB
	bool m_VegetationEnabled; //0x00CC
	bool m_ForceEnabled; //0x00CD
	bool m_WorldRenderEnabled; //0x00CE
	bool m_TerrainEnabled; //0x00CF
	bool m_WaterPhysicsEnabled; //0x00D0
	bool m_OvergrowthEnabled; //0x00D1
	bool m_EffectsEnabled; //0x00D2
	bool m_EmittersEnabled; //0x00D3
	bool m_PadRumbleEnabled; //0x00D4
	bool m_JuicePlayerReportPositionEnabled; //0x00D5
	bool m_LipSyncEnabled; //0x00D6
	bool m_OnDamageSpottingEnabled; //0x00D7
	bool m_IgnoreClientFireRateMultiplier; //0x00D8
	bool m_PauseGameOnStartUp; //0x00D9
	bool m_SkipFastLevelLoad; //0x00DA
	bool m_InputEnable; //0x00DB
	bool m_ScreenshotToFile; //0x00DC
	bool m_LoadMenu; //0x00DD
	bool m_DebugMenuOnLThumb; //0x00DE
	bool m_InvertFreeCamera; //0x00DF
	bool m_RenderTags; //0x00E0
	bool m_InvertPitch; //0x00E1
	bool m_InvertPadPcRightStick; //0x00E2
	bool m_Scheme0FlipY; //0x00E3
	bool m_Scheme1FlipY; //0x00E4
	bool m_Scheme2FlipY; //0x00E5
	bool m_InvertYaw; //0x00E6
	bool m_ConsoleInputEmulation; //0x00E7
	bool m_SampleInputEveryVisualFrame; //0x00E8
	bool m_HavokVisualDebugger; //0x00E9
	bool m_HavokVDBShowsEffectsWorld; //0x00EA
	bool m_HavokCaptureToFile; //0x00EB
	bool m_UseMouseAndKeyboardSystem; //0x00EC
	bool m_UseGlobalGamePadInput; //0x00ED
	bool m_ShowBuildId; //0x00EE
	bool m_ExtractPersistenceInformation; //0x00EF
	bool m_EnableRestTool; //0x00F0
	bool m_LocalVehicleSimulationEnabled; //0x00F1
	bool m_AsyncClientBulletEntity; //0x00F2
	bool m_AutoUnspawnDynamicObjects; //0x00F3
	bool m_QuitGameOnServerDisconnect; //0x00F4
	bool m_DebugTrackAllPlayersInSpawnScreen; //0x00F5
	bool m_UseOldKillerCamera; //0x00F6
	bool m_LuaOptionSetEnable; //0x00F7
};//Size=0x00F8

class Main
{
public:
	char _0x0000[32];
	unsigned char m_IsDedicatedServer; //0x0020 
	unsigned char m_IsDedicatedServerData; //0x0021 
	unsigned char m_IsPaused; //0x0022 
	char _0x0023[5]; //0x0023 
	char _0x0028[32];
	Server* m_pServer; //0x0048 
	Client* m_pClient; //0x0050 
	FileSystem* m_pFileSystem; //0x0058 
	GameTimer* m_pSimulationGameTimer; //0x0060 
	GameTimer* m_pUIGameTimer; //0x0068 
	char _0x0070[8];
	ServerJobData m_ServerJobData; //0x0078 

	static Main* GetInstance()
	{
		return *(Main**)OFFSET_MAIN;
	}

	IPhysicsRayCaster* GetRayCaster();
};//Size=0x0118

class Server
{
public:
	char _0x0000[8];
	GameSettings* m_pGameSettings; //0x0008 
	char _0x0010[120];
	ServerSettings* m_pServerSettings; //0x0088 
};//Size=0x0090

class GameSettings
{
public:
	char _0x0000[64];

};//Size=0x0040

class ServerSettings
{
public:
	char _0x0000[64];

};//Size=0x0040

class Client
{
public:
	char _0x0000[8];
	GameSettings* m_pGameSettings; //0x0008 
	char _0x0010[24];
	ClientGameContext* m_pGameContext; //0x0028 
	ClientSettings* m_pClientSettings; //0x0030 
	char _0x0038[8];

};//Size=0x0040

class FileSystem
{
public:
	char _0x0000[56];

};//Size=0x0038

class GameTimer
{
public:

	__int64 m_Count; //0x0000 
	__int64 m_Counts; //0x0008 
	double m_DeltaTime; //0x0010 
	double m_Time; //0x0018 
	double m_TargetDelta; //0x0020 
	__int64 m_SleepMode; //0x0028 
	GameTimeSettings* m_pGameTimeSettings; //0x0030 
	__int32 m_TickFrequency; //0x0038 
	__int32 m_Ticks; //0x003C 
	__int32 m_OldTicks; //0x0040 
	__int32 m_Frames; //0x0044 
	__int32 N00000498; //0x0048 
	__int32 N000004A2; //0x004C 
	__int32 N00000499; //0x0050 
	__int32 N000004A5; //0x0054 
	double m_DeltaTime2; //0x0058 
	double m_ActualDelta; //0x0060 
	double m_OldActualDelta; //0x0068 
	double m_ExpectedTotalTime; //0x0070 
	double m_RealTotalTime; //0x0078 
	double m_SleptTime; //0x0080 
	double m_LostTime; //0x0088 
	double m_WorstFrameTime; //0x0090 
	double m_LogTime; //0x0098 
	double m_LatestDeltaTime; //0x00A0 
	double m_TimeInTick; //0x00A8 
	double m_BaseTicks; //0x00B0 
	double m_BaseTime; //0x00B8 
	unsigned char m_HitVSync; //0x00C0 

};//Size=0x00C1

class GameTimeSettings
{
public:
	char _0x0000[56];

};//Size=0x0038

class ClientGameContext
{
public:
	char _0x0000[32];
	GameTime* m_pGameTime; //0x0020 
	Level* m_pLevel; //0x0028 
	char _0x0030[48];
	PlayerManager* m_pPlayerManager; //0x0060 
	Online* m_pOnline; //0x0068 
	GameView* m_pGameView; //0x0070 
	InterpolationManager* m_pInterpolationManager; //0x0078 
	char _0x0080[960];

	static ClientGameContext* GetInstance()
	{
		return *(ClientGameContext**)(OFFSET_CLIENTGAMECONTEXT);
	}

};//Size=0x0440

class GameView
{
public:
	char _0x0000[64];

};//Size=0x0040

class Online
{
public:
	char _0x0000[56];
	Connection* m_pConnection; //0x0038 

};//Size=0x0040

class InterpolationManager
{
public:
	char _0x0000[64];

};//Size=0x0040

namespace eastl
{
	class allocator
	{
	public:
		__forceinline allocator()
		{
		}

		__forceinline allocator(eastl::allocator* __formal)
		{
		}

		__forceinline void set_name(const char* __formal)
		{
		}

		__forceinline const char* get_name()
		{
			return "";
		}

		__forceinline void* allocate(unsigned int n, int flags)
		{
			return malloc(n);
		}

		__forceinline void deallocate(void* p, unsigned int __formal)
		{
			free(p);
		}
	};

	template <class T>
	class vector
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		void* vftable;
	public:
		size_t size()
		{
			return (((intptr_t)m_lastElement - (intptr_t)m_firstElement) / sizeof(void*));
		}

		T at(int nIndex)
		{
			return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
		}
		T operator [](int index)
		{
			return at(index);
		}
	};

	template <class T, INT Count, INT PadSize>
	class fixed_vector
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		//LPVOID m_pad[PadSize];
		T m_data[Count];

	public:
		fixed_vector() {
			m_firstElement = (T*)m_data;
			m_lastElement = (T*)m_data;
			m_arrayBound = (T*)&m_data[Count];
		}

		void push_back(T* const value) {
			if (m_lastElement > m_arrayBound) {

				return;
			}
			*m_lastElement = *value;
			m_lastElement = m_lastElement + 1;
		};

		void clear() {
			m_firstElement = m_data;
			m_lastElement = m_data;
		}

		UINT Size() {
			return m_lastElement - m_firstElement;
		}

		T At(INT nIndex) {
			return m_firstElement[nIndex];
		}

		T operator [](INT index) { return At(index); }
	};
}

class PlayerManager
{
public:
	virtual void function();
	virtual eastl::vector<ClientPlayer*>* GetPlayers();
	virtual eastl::vector<ClientPlayer*>* GetSpectators();

private:
	char _0x0008[1336];
	ClientPlayer* m_pLocalPlayer; //0x0540 
	ClientPlayer** m_ppPlayers; //0x0548 

public:
	ClientPlayer* GetPlayerById(unsigned int id);
	ClientPlayer* GetLocalPlayer();
	static PlayerManager* GetInstance();
};//Size=0x0550

class GameTime
{
public:
	char _0x0000[64];

};//Size=0x0040

class Level
{
public:
	char _0x0000[56];
	LevelData* m_pLevelData; //0x0038 
	//char _0x0040[224];
	char pad_0040[8]; //0x0040
	char* m_LevelName; //0x0048
	char pad_0050[208]; //0x0050
	HavokPhysicsManager* m_pHavokPhysics; //0x0120 
	char _0x0128[8];
	ClientGameWorld* m_pGameWorld; //0x0130 

};//Size=0x0138

class HavokPhysicsManager
{
public:
	char _0x0000[80];
	HavokManager* m_pHavokManager; //0x0050 
	IPhysicsRayCaster* m_pRayCaster; //0x0058 
	char _0x0060[60];
	float m_MaxVehicleHeight; //0x009C 
	char _0x00A0[16];
	TerrainPhysicsEntity* m_pTerrainPhysicsEntity; //0x00B0 
	char _0x00B8[248];
	Physics* m_pPhysics; //0x01B0 
	char _0x01B8[8];
	PhysicsSettings* m_pPhysicsSettings; //0x01C0 
	PhysicsRenderSettings* m_pPhysicsRenderSettings; //0x01C8 

};//Size=0x01D0

class TerrainPhysicsEntity
{
public:
	char _0x0000[64];

};//Size=0x0040

class Physics
{
public:
	char _0x0000[64];

};//Size=0x0040

class PhysicsSettings
{
public:
	char _0x0000[64];

};//Size=0x0040

class PhysicsRenderSettings
{
public:
	char _0x0000[64];

};//Size=0x0040

class Material
{
public:
	enum MaterialFlag
	{
		MFSeeThrough = 0x1,
		MFClientDestructable = 0x40000000,
		MFPenetrable = 0x8
	};
	UINT32 m_flagsAndIndex;
	__forceinline bool isPenetrable()
	{
		return (m_flagsAndIndex & MFPenetrable);
	};
	__forceinline bool isSeeThrough()
	{
		return (m_flagsAndIndex & MFSeeThrough);
	};
};

class RayCastHit
{
public:
	Vector m_position;		// 0x00
	Vector m_normal;		// 0x10
	void* m_rigidBody;		// 0x20
	Material m_material;	// 0x28
	DWORD m_part;			// 0x30
	FLOAT m_lambda;			// 0x34
	char _pad[56];			// 0x38
}; //Size = 0x0070

class IPhysicsRayCaster
{
public:
	enum class RayCastFlags
	{
		NoCheck = 0,
		CheckDetailMesh = 0x0DB,
		IsAsyncRaycast = 0x2,
		DontCheckWater = 0x0FD,
		DontCheckTerrain = 0x07A,
		DontCheckRagdoll = 0x10,
		DontCheckCharacter = 0x20,
		DontCheckGroup = 0x40,
		DontCheckPhantoms = 0x80,
	};

	class Ray
	{
	public:
		Vector origin;
		Vector direction;

		//Ray's start position and normalized direction vector
		Ray(const Vector& _origin, const Vector& _direction);
		Ray() : origin(-1.f, -1.f, -1.f), direction(-1.f, -1.f, -1.f) {}

		//Ray's start position and normalized direction vector
		void Init(const Vector& _origin, const Vector& _direction);
	};

	class AxisAlignedBoundingBox
	{
	public:
		Vector min, max;
		AxisAlignedBoundingBox(const Vector& _min, const Vector& _max);
	};

	virtual bool PhysicsRayQuery(const char* identifier, D3DXVECTOR3* from, D3DXVECTOR3* to, RayCastHit* hit, int flag, eastl::fixed_vector<PhysicsEntityBase*, 8, 0>* PhysicsEntityList);

	bool IsPointVisible(const Vector& src, const Vector& dst, RayCastHit* outHit);
	bool IsIntersectingEntity(const Ray& ray, ClientPlayer* const pEntity);

	static bool IsIntersectingAABB(const Vector& dir, const AABB& aabb, float* rayHitLenght);
	static bool IsIntersectingOBB(const Ray& ray, const AxisAlignedBoundingBox& aabb, Matrix& matrix, float* rayHitLenghtOut);
};//Size=0x0008

class HavokManager
{
public:
	char _0x0000[56];
	__int64 m_pHKPWorld; //0x0038 

};//Size=0x0040

class LevelData
{
public:
	char _0x0000[64];

};//Size=0x0040

class Connection
{
public:
	char _0x0000[64];

};//Size=0x0040

namespace fb
{
	class MemoryArena;

	struct eastl_arena_allocator
	{
	public:
		MemoryArena* arena; // this+0x0

	}; // eastl_arena_allocator

};

class ClientPlayer
{
public:
	virtual ~ClientPlayer();
	virtual void* GetCharacterEntity(); // ClientSoldierEntity + 188 
	virtual void* GetCharacterUserData(); // PlayerCharacterUserData
	virtual EntryComponent* GetEntryComponent();
	virtual bool InVehicleFn();
	virtual unsigned int GetId();
	virtual bool hasUnlockAsset(LPVOID, bool);
	virtual void getUnlockAssets(eastl::vector<LPVOID>*);
	virtual bool isUnlocked(LPVOID);

	bool InVehicle();

	enum class EntrySeatType
	{
		Driver = 0x0,
		Gunner = 0x1,
		Passenger = 0x2,
	};

	int32_t m_Data; //0x0008
	char pad_000C[12]; //0x000C
	char* m_NamePtr; //0x0018
	char pad_0020[32]; //0x0020
	char m_Name[16]; //0x0040
	char pad_0050[2296]; //0x0050
	VeniceSoldierCustimizationAsset* m_pCustomization; //0x0948 
	char pad_0950[2681]; //0x0950
	bool m_IsSpectator; //0x13C9
	char pad_13CA[2]; //0x13CA
	__int32 m_TeamId; //0x13CC 
	char _0x13D0[240];
	ClientSoldierEntity* m_pAttachedControllable; //0x14C0 
	EntrySeatType m_EntryId; //0x14C8 
	ClientSoldierEntity* m_pControlledControllable; //0x14D0 
	char pad_14D8[862]; //0x14D8
	char m_Name2[11]; //0x1836

	ClientSoldierEntity* GetSoldierEntity();
	ClientControllableEntity* GetVehicleEntity();
	ClientVehicleEntity* GetClientVehicleEntity();
	void GetWeaponShootSpace(Matrix* const out);
	bool GetCurrentWeaponData(WeaponData_s* pDataOut);

};//Size=0x14D8

class VeniceSoldierCustimizationAsset
{
public:
	char _0x0000[32];
	char* m_pUIKitIconName; //0x0020 
	char* m_pUIHudIcon; //0x0028 
	CustomizationTable* m_pAppearance; //0x0030 
	char _0x0038[16];
	CustomizationTable* m_pWeaponTable; //0x0048 

};//Size=0x0050

class CustomizationTable
{
public:
	char _0x0000[16];
	Customization* m_ppList; //0x0010 
	char _0x0018[40];

};//Size=0x0040

class Customization
{
public:
	char _0x0000[16];
	char* m_pSID; //0x0010 
	char _0x0018[8];
	__int64 m_ppUnlockParts; //0x0020 
	char _0x0028[16];

};//Size=0x0038

/*struct LinearTransform
{
	D3DXVECTOR3 m_right; // 0x0
	D3DXVECTOR3 m_up; // 0x10
	D3DXVECTOR3 m_forward; // 0x20
	D3DXVECTOR3 m_trans; // 0x30
}; // size = 0x40*/

class LinearTransform
{
public:
	union
	{
		struct
		{
			D3DXVECTOR3 left;
			D3DXVECTOR3 up;
			D3DXVECTOR3 forward;
			D3DXVECTOR3 trans;
		};
		FLOAT data[4][4];
	};
	LinearTransform()
	{}
};

class AxisAlignedBox
{
public:
	D3DXVECTOR4 m_Min; //0x0000 
	D3DXVECTOR4 m_Max; //0x0010 
	bool Intersect(const Vector& point, const Vector& dir) const;

	AxisAlignedBox() {}
};//Size=0x0020

struct TransformAABBStruct {
	LinearTransform Transform;
	AxisAlignedBox AABB;
	D3DXMATRIX  pad;

	TransformAABBStruct()
	{}
};

class HealthComponent
{
public:
	char _0x0000[32];
	float m_Health; //0x0020 
	float m_MaxHealth; //0x0024 
	char _0x0028[16];
	float m_VehicleHealth; //0x0038 

};//Size=0x003C

class VehicleCustomizationAsset
{

};

class VehicleData
{
private: char pad_0000[240]; //0x0000
public:  char* m_ObjectName; //0x00F0 vehicles.heli.scout
private: char pad_00F8[56]; //0x00F8
public:  char* m_ObjectPath; //0x0130 Gameplay/Vehicles/AH6/AH6_Littlebird
private: char pad_0138[16]; //0x0138
public:  
	float m_MaxHealth; //0x0148
	char pad[156];
	float m_TopHitHeight; //0x01E8
	float m_TopHitAngle; //0x01EC
	float m_RegenerationDelay; //0x01F0
	float m_RegenerationRate; //0x01F4
	float m_ArmorMultiplier; //0x01F8
	float m_RegenerationDelayMultiplier; //0x01FC
	float m_RegenerationRateMultiplier; //0x0200
	float m_EmergencyRepairHealth; //0x0204
	float m_DecayDelay; //0x0208
	float m_DecayRate; //0x020C
	void* m_CriticallyDamagedEffect; //0x0210
	float m_CriticalDamageTime; //0x0218
	char _0x021C[4];
	void* m_PreExplosionEffect; //0x0220
	float m_PreExplosionTime; //0x0228
	char _0x022C[4];
	void* m_Explosion; //0x0230
	void* m_Mesh; //0x0238
	void* m_CockpitMesh; //0x0240
	char* m_NameID; //0x0248 ID_P_VNAME_AH6
	__int32 m_MaxPlayersInVehicle; //0x0250
	float m_MinSpeedForMineActivation; //0x0254
	float m_UpsideDownDamage; //0x0258
	float m_UpsideDownDamageDelay; //0x025C
	float m_UpsideDownAngle; //0x0260
	float m_WaterDamage; //0x0264
	float m_BelowWaterDamageDelay; //0x0268
	float m_WaterDamageOffset; //0x026C
	float m_VelocityDamageThreshold; //0x0270
	float m_VelocityDamageMagnifier; //0x0274
	float m_RepairRateModifier; //0x0278
	float m_KillSoldierCollisionSpeedThreshold; //0x027C
	float m_ExitSpeedThreshold; //0x0280
	float m_ExitDirectionSpeedThreshold; //0x0284
	float m_FLIRValue; //0x0288
	__int32 m_MPMode; //0x028C
	float m_ExitCameraSwitchDelay; //0x0290
	char pad_0294[24]; //0x0294
	float m_LockingTimeMultiplier; //0x02AC
	char pad_02B0[16]; //0x02B0
	float m_HighAltitudeLockHeight; //0x02C0
	char _0x02C4[4];
	void* m_Sound; //0x02C8
	void* m_VoiceOverInfo; //0x02D0
	float m_NametagHeightScale; //0x02D8
	float m_SpottingFovScale; //0x02DC
	bool m_AllowVehicleOutsideCombatAreas; //0x02E0
	bool m_UseTopZone; //0x02E1
	bool m_HealthZonesShareDamage; //0x02E2
	bool m_UseProtectedShields; //0x02E3
	bool m_ShowPlayerHealth; //0x02E4
	bool m_ForegroundRenderCockpitMesh; //0x02E5
	bool m_MotionBlurMask; //0x02E6
	bool m_SuppressDamageByPassengers; //0x02E7
	bool m_IsAffectedByEMP; //0x02E8
	bool m_CanTakeDynamicFireDamage; //0x02E9
	bool m_ThrowOutSoldierInsideOnWaterDamage; //0x02EA
	bool m_IgnoreSoldierCollisionNormal; //0x02EB
	bool m_ChoseExitPointByDirection; //0x02EC
	bool m_ExitAllowed; //0x02ED
	bool m_EnableGroundmapLighting; //0x02EE
	bool m_UseAsTeamSpawner; //0x02EF
	bool m_IsLockable; //0x02F0
	bool m_NeverReportVehicleAsEmpty; //0x02F1
	bool m_UseLowAltitudeHeatSignature; //0x02F2
	bool m_UseSpottingTargetComponentForRaycast; //0x02F3
	bool m_EquipmentFakeVehicle; //0x02F4
	bool m_ExplosionPacksAttachable; //0x02F5
	bool m_DamageGiverOverrideOwnerVehicle; //0x02F6
	char _0x02F7[9];
public:

	enum class VehicleType
	{
		UNUSED = 0X0,
		LOCALPLAYER = 0X1,
		LOCALDIRECTION = 0X2,
		FRIENDLYPLAYER = 0X3,
		ENEMYPLAYER = 0X4,
		NEUTRALPLAYER = 0X5,
		SQUADMEMBER = 0X6,
		SQUADLEADER = 0X7,
		SQUADLEADERTARGETED = 0X8,
		VEHICLE = 0X9,
		PRIMARYOBJECTIVE = 0XA,
		PRIMARYOBJECTIVEBLINK = 0XB,
		SECONDARYOBJECTIVE = 0XC,
		AREAMAPMARKER = 0XD,
		OBJECTIVEDESTROY = 0XE,
		OBJECTIVESCOUT = 0XF,
		OBJECTIVEDEFEND = 0X10,
		OBJECTIVEMOVETO = 0X11,
		OBJECTIVEATTACK = 0X12,
		OBJECTIVEFOLLOW = 0X13,
		OBJECTIVEGENERAL = 0X14,
		UAV = 0X15,
		AMMOCRATE = 0X16,
		MEDICBAG = 0X17,
		C4 = 0X18,
		ATMINE = 0X19,
		STATIONARYWEAPON = 0X1A,
		NORTH = 0X1B,
		SOUTH = 0X1C,
		WEST = 0X1D,
		EAST = 0X1E,
		NEUTRALFLAG = 0X1F,
		FRIENDLYFLAG = 0X20,
		ENEMYFLAG = 0X21,
		FRIENDLYBASE = 0X22,
		ENEMYBASE = 0X23,
		TEAM1FLAG = 0X24,
		TEAM2FLAG = 0X25,
		NEUTRALFLAGLIT = 0X26,
		FRIENDLYFLAGLIT = 0X27,
		ENEMYFLAGLIT = 0X28,
		SELECTABLESPAWNPOINT = 0X29,
		SELECTEDSPAWNPOINT = 0X2A,
		NONSELECTABLESPAWNPOINT = 0X2B,
		FRIENDLYFLAGUNDERATTACK = 0X2C,
		ENEMYFLAGUNDERATTACK = 0X2D,
		ORDERATTACK = 0X2E,
		ORDERDEFEND = 0X2F,
		ORDERATTACKOBSERVED = 0X30,
		ORDERDEFENDOBSERVED = 0X31,
		BOAT = 0X32,
		CAR = 0X33,
		JEEP = 0X34,
		HELIATTACK = 0X35,
		HELISCOUT = 0X36,
		TANK = 0X37,
		TANKIFV = 0X38,
		TANKARTY = 0X39,
		TANKAA = 0X3A,
		TANKAT = 0X3B,
		JET = 0X3C,
		JETBOMBER = 0X3D,
		STATIONARY = 0X3E,
		STRATEGIC = 0X3F,
		MOTIONRADARSWEEP = 0X40,
		NEEDBACKUP = 0X41,
		NEEDAMMO = 0X42,
		NEEDMEDIC = 0X43,
		NEEDPICKUP = 0X44,
		NEEDREPAIR = 0X45,
		KITASSAULT = 0X46,
		KITDEMOLITION = 0X47,
		KITRECON = 0X48,
		KITSPECIALIST = 0X49,
		KITSUPPORT = 0X4A,
		KITMEDIC = 0X4B,
		KITENGINEER = 0X4C,
		KITPICKUPASSAULT = 0X4D,
		KITPICKUPDEMOLITION = 0X4E,
		KITPICKUPRECON = 0X4F,
		KITPICKUPSPECIALIST = 0X50,
		KITPICKUPSUPPORT = 0X51,
		KITPICKUPMEDIC = 0X52,
		KITPICKUPENGINEER = 0X53,
		PICKUP = 0X54,
		TAGGEDVEHICLE = 0X55,
		LASERPAINTEDVEHICLE = 0X56,
		HELITARGETENEMY = 0X57,
		HELITARGETFRIENDLY = 0X58,
		ARTILLERYTARGET = 0X59,
		NEUTRALFLAGATTACKER = 0X5A,
		FRIENDLYFLAGATTACKER = 0X5B,
		ENEMYFLAGATTACKER = 0X5C,
		LASERTARGET = 0X5D,
		OBJECTIVEATTACKER = 0X5E,
		OBJECTIVEDEFENDER = 0X5F,
		HEALTHBARBACKGROUND = 0X60,
		HEALTHBAR = 0X61,
		RADARSWEEPCOMPONENT = 0X62,
		BLANK = 0X63,
		LOCALPLAYERBIGICON = 0X64,
		LOCALPLAYEROUTOFMAP = 0X65,
		PRIMARYOBJECTIVELARGE = 0X66,
		TARGETUNLOCKED = 0X67,
		TARGETLOCKED = 0X68,
		TARGETLOCKING = 0X69,
		ARTILLERYSTRIKENAMETAG = 0X6A,
		ARTILLERYSTRIKEMINIMAP = 0X6B,
		CAPTUREPOINTCONTESTED = 0X6C,
		CAPTUREPOINTDEFENDED = 0X6D,
		ROUNDBAR = 0X6E,
		ROUNDBARBG = 0X6F,
		ROUNDBARBGPLATE = 0X70,
		SNAPOVALARROW = 0X71,
		SQUADLEADERBG = 0X72,
		VEHICLEBG = 0X73,
		NONTAKEABLECONTROLPOINT = 0X74,
		SPOTTEDPOSITION = 0X75,
		GRENADE = 0X76,
		REVIVE = 0X77,
		REPAIR = 0X78,
		INTERACT = 0X79,
		VOIP = 0X7A,
		CLAYMORE = 0X7B,
		EODBOT = 0X7C,
		EXPLOSIVE = 0X7D,
		LASERDESIGNATOR = 0X7E,
		MAV = 0X7F,
		MORTAR = 0X80,
		RADIOBEACON = 0X81,
		UGS = 0X82,
		PERCETAGEBARMIDDLE = 0X83,
		PERCETAGEBAREDGE = 0X84,
		PERCENTAGEBARBACKGROUND = 0X85,
		TANKLC = 0X86,
		HELITRANS = 0X87,
		STATICAT = 0X88,
		STATICAA = 0X89,
		SPRINTBOOST = 0X8A,
		AMMOBOOST = 0X8B,
		EXPLOSIVEBOOST = 0X8C,
		EXPLOSIVERESISTBOOST = 0X8D,
		SUPPRESSIONBOOST = 0X8E,
		SUPPRESSIONRESISTBOOST = 0X8F,
		GRENADEBOOST = 0X90,
		HEALSPEEDBOOST = 0X91,
		NEEDAMMOHIGHLIGHT = 0X92,
		NEEDMEDICHIGHLIGHT = 0X93,
		NEEDREPAIRHIGHLIGHT = 0X94,
		NEEDPICKUPHIGHLIGHT = 0X95,
		PLAYERDEAD = 0X96,
		PLAYER = 0X97,
		FLAG = 0X98,
		BASE = 0X99,
		OBJECTIVENEUTRALBOMB = 0X9A,
		OBJECTIVEFRIENDLYBOMB = 0X9B,
		OBJECTIVEENEMYBOMB = 0X9C,
		OBJECTIVEENEMYHVT = 0X9D,
		OBJECTIVEFRIENDLYHVT = 0X9E,
		CANSUPPLYAMMO = 0X9F,
		CANSUPPLYMEDIC = 0XA0,
		CANSUPPLYREPAIR = 0XA1,
		COUNT = 0XA2,
	};
	enum class VehicleCategory
	{
		UNUSED,
		GROUND,
		AIR,
		WATER
	};

	bool IsInJet();
	bool IsInHeli();
	VehicleType GetVehicleType();
	VehicleCategory GetVehicleCategory();
	bool IsAirVehicle();
	bool IsGroundVehicle();
	bool IsWaterVehicle();
};

class ClientControllableEntity
{
public:
#pragma region Virtual
	virtual TypeInfo* GetType();
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void GetAABB(TransformAABBStruct* pAABB);
	virtual void GetTransform(D3DXMATRIX * mTransform); //LinearTransform
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27();
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual PhysicsEntityBase* GetPhysiscsEntity(); //physics
	virtual D3DXVECTOR3* GetVelocity(); //velocity
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //
#pragma endregion Functions

	char _0x0000[10];
	unsigned char m_OcclusionFlags; //0xB
	char _0x0013[13]; 
	char _0x0020[16];
	VehicleData* m_pData;
	char _0x0038[200];
	float m_Velocity;
	char _0x0104[60];
	HealthComponent* m_pHealthComp; //0x140

	//TODO
	std::string GetVehicleName();
	bool IsAlive();
	bool IsTVGuidedMissile();
	
};//Size=0x0148

class ClientSoldierEntity : public ClientControllableEntity
{
public:
	char _0x0148[160];
	AntAnimatableComponent* m_pAnimatable; //0x01E8 
	AntAnimatableComponent* m_pAnimatable2; //0x01F0 
	char _0x01F8[760];
	__int32 m_PoseType; //0x04F0 
	__int32 m_EngineChams; //0x04F4 
	char _0x04F8[120];
	SoldierWeaponComponent* m_pWeaponComponent; //0x0570 
	ClientSoldierBodyComponent* m_pBodyComponent; //0x0578 
	RagdollComponent* m_pRagdollComponent; //0x0580 
	/*char _0x0588[40];
	unsigned char m_Sprinting; //0x05B0 
	unsigned char m_Occluded; //0x05B1 
	char N00001BCE[6]; //0x05B2 
	char _0x05B8[1432];
	ParachuteComponent* m_pParachute; //0x0B50 
	char _0x0B58[152];
	SpottingComponent* m_pSpottingComp; //0x0BF0 
	char _0x0BF8[24];
	SpottingTargetComponent* m_pSpottingTargetComp; //0x0C10 
	char _0x0C18[88];
	SoldierSuppressionComponent* m_pSuppressionComp; //0x0C70 
	char _0x0C78[184];*/

	char padddd[1960];
	VaultComponent* m_pVaultComp; //0x0D30 
	char _0x0D38[1264];

	//Getting view angles in radians
	D3DXVECTOR2* GetAimAngles();
	FiringFunctionData* GetFiringData();

};//Size=0x1228

class PhysicsEntityBase
{
public:
	virtual TypeInfo* getType();
	virtual void deconstructor(); //
	virtual void addToWorld(); //
	virtual void removeFromWorld(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void GetAABB(TransformAABBStruct* transaabb);  //Physics virtual 19
	virtual void GetMass(float&); //
	virtual void GetAnotherMass(float&); //
	virtual void GetTransform(LinearTransform* mTransform); //Physics virtual 22
	virtual void Function23(); // __m128i *__fastcall sub_140B11110(__int64 a1, __m128i *a2)
	virtual void Function24(); // return a float
	virtual D3DXVECTOR3* LinearVelocity(); // 25 signed __int64 __fastcall sub_140B0F7F0(__int64 a1)
	virtual D3DXVECTOR3* AngularVelocity(); // // Returns the angular velocity around the center of mass, in World space.
	/*virtual void Function27(); // n?
	virtual void Function28(); // ret bool
	virtual void Function29(); //
	virtual unsigned int GetpartCount(); //Physics virtual 30
	virtual void Function31(); //__int64 __fastcall sub_140B274B0(__int64 a1, int a2)
	virtual unsigned int GetPartTransforms(fb::QuatTransform*); //Physics virtual 32 (return nbparts)
	virtual void Function33(); //__int64 __fastcall sub_140B27110(__int64 a1, int a2)
	virtual void Function34(); //__int64 __fastcall sub_140B27370(__int64 a1, __int64 a2, unsigned int a3)
	virtual void Function35(); //__int64 __fastcall sub_140B27370(__int64 a1, __int64 a2, unsigned int a3)
	virtual void Function36(); //__int64 __fastcall sub_140B27460(__int64 a1, unsigned int a2)
	virtual void Function37(); //int __fastcall sub_140B2B310(__int64 a1, __int64 a2, __m128 *a3)*/

	class PhysicsEntityUserData
	{
	public:
		unsigned char* materialIndices;	// this+0x0
		unsigned int* materialFlags;		// this+0x8
		void* partsEnabled;				// this+0x10
		unsigned int flags;					// this+0x18
		float mass;							// this+0x1C
		unsigned short partCount;			// this+0x20
		unsigned char materialCount;		// this+0x22
		unsigned char pad[0x28 - 0x23];		// this+0x23
	}; //size 0x28



	char _0x0008[0x18 - 0x08];
	void*/*Entity**/ m_Parententity; //0x0018 ex ClientVehicleEntity StaticModelEntity
	class PhysicsEntityUserData m_physicsUserData; //0x20
	char _0x0038[0x70 - 0x48];
};//Size=0x0070

class AntAnimatableComponent
{
public:
	char _0x0000[104];
	GameAnimatable* m_Handler; //0x0068 
	char _0x0070[16];

};//Size=0x0080

class GameAnimatable
{
public:
	char _0x0000[212];
	unsigned char m_HadVisualUpdate; //0x00D4 

};//Size=0x00D5

class AnimatedSoldierWeaponHandler
{
public:
	SoldierWeapon* m_pWeaponList[7]; //0x0000 
};//Size=0x0040

class SoldierWeaponComponent
{
public:
	char _0x0000[208];
	D3DXMATRIX  m_WeaponTransform; //0x00D0 
	char _0x0110[1920];
	AnimatedSoldierWeaponHandler* m_Handler; //0x0890 
	char _0x0898[48];
	ClientSoldierEntity* m_pOwner; //0x08C8 
	char _0x08D0[456];
	__int32 m_CurrentWeaponIndex; //0x0A98  0 - primary, 1 - secondary, 2 - gadget (C4), ... 5 - M230, 6 - granade, 7 - knife
	__int32 m_LastWeaponIndex; //0x0A9C 
	__int32 m_LastGunIndex; //0x0AA0 
	char _0x0AA4[28];
	__int32 m_CurrentZoomLevel; //0x0AC0 
	__int32 m_ZoomLevelMax; //0x0AC4 
	__int32 m_ZeroingDistanceLevel; //0x0AC8 

	SoldierWeapon* GetActiveSoldierWeapon();;
	int GetSlot();
};//Size=0x0ACC

class SoldierWeapon
{
public:
	char _0x0000[18824];
	SoldierAimingSimulation* m_pAuthoritativeAiming; //0x4988 
	char _0x4990[24];
	ClientWeapon* m_pWeapon; //0x49A8 
	char _0x49B0[16];
	WeaponFiring* m_pPrimary; //0x49C0 
	char _0x49C8[696];
};//Size=0x4C80

class SoldierAimingSimulation
{
public:
	char _0x0000[16];
	AimAssist* m_pFPSAimer; //0x0010 
	float m_Yaw; //0x0018 
	float m_Pitch; //0x001C 
	float m_AimYawTimer; //0x0020 
	float m_AimPitchTimer; //0x0024 
	D3DXVECTOR2  m_Sway; //0x0028 
	float m_DeltaTime; //0x0030 
	char _0x0034[8];
	D3DXVECTOR2  m_ViewDelta; //0x003C 
	char _0x0044[44];
	D3DXMATRIX  m_Transform; //0x0070 
	D3DXVECTOR4 m_Position; //0x00B0 
	D3DXVECTOR4 m_View; //0x00C0 
	D3DXVECTOR4 m_Velocity; //0x00D0 
	char _0x00E0[88];
	float m_Fov; //0x0138 
	char _0x013C[28];
	TypeInfo* m_RayResult; //0x0158 
	D3DXVECTOR4 m_RayHitPoint; //0x0160 
	__int32 m_RayLength; //0x0170 
};//Size=0x0174

class AimAssist
{
public:
	char _0x0000[20];
	D3DXVECTOR2  m_AimAngles;
};//Size=0x001C

class ClientWeapon
{
public:
	char N000018B4[24]; //0x0000 
	PrimaryFire* m_pWeaponFiring; //0x0018 
	WeaponModifier* m_pWeaponModifier; //0x0020 
	char _0x0028[8];
	D3DXVECTOR4 m_MoveSpeed; //0x0030 
	D3DXMATRIX  m_ShootSpace; //0x0040 
	D3DXMATRIX  m_ShootSpaceIdentity; //0x0080 
	char _0x00C0[464];
	float m_CameraFOV; //0x0290 
	float m_WeaponFOV; //0x0294 
	float m_FOVScaleFactor; //0x0298 
	char _0x029C[20];
	__int32 m_ZoomLevel; //0x02B0 

};//Size=0x02B4

class PrimaryFire
{
public:
	char _0x0000[16];
	FiringFunctionData* m_FiringData; //0x0010 
	char _0x0018[24];
	__int64 m_pGunSwayData; //0x0030 

};//Size=0x0038

class OverheatData
{
public:
	struct FireEffectData
	{
		D3DXVECTOR3 m_Offset; // 0x0
		D3DXVECTOR3 m_Rotation; // 0x10
		D3DXVECTOR3 m_ZoomOffset; // 0x20
		D3DXVECTOR3 m_ZoomRotation; // 0x30
		/*EffectBlueprint**/void* m_Effect; // 0x40
		bool m_UseZoomOffset; // 0x48
		bool m_UseZoomRotation; // 0x49
		bool m_DisableDuringZoom; // 0x4a
		bool m_UpdateTransform; // 0x4b
		bool m_StopLoopingEffects; // 0x4c
		unsigned char _0x4d[0x3];
	}; // size = 0x50

	FireEffectData m_OverHeatEffect; // 0x0
	float m_HeatPerBullet; // 0x50
	float m_HeatDropPerSecond; // 0x54
	float m_OverHeatPenaltyTime; // 0x58
	float m_OverHeatThreshold; // 0x5c
};//Size=0x0060

class ShotConfigData
{
public:
	D3DXVECTOR4 m_PositionOffset; //0x0000 
	D3DXVECTOR4 m_Direction; //0x0010 
	D3DXVECTOR4 m_Speed; //0x0020 
	char _0x0030[32];
	BulletEntityData* m_ProjectileData; //0x0050 
	BulletEntityData* m_SecondaryProjectileData; // 0x58
	void* m_ProjectileBluePrint; // 0x60
	void* m_SecondaryProjectileBluePrint; // 0x68
	float m_SpawnDelay; // 0x70
	float m_SpawnDelayZoomed; // 0x74
	unsigned int m_NumberOfBulletsPerShell; // 0x78
	unsigned int m_NumberOfBulletsPerShot; // 0x7c
	unsigned int m_NumberOfBulletsPerBurst; // 0x80
	bool m_RelativeTargetAiming; // 0x84
	bool m_ForceSpawnToCamera; // 0x85
	bool m_SpawnVisualAtWeaponBone; // 0x86
	bool m_ActiveForceSpawnToCamera; // 0x87
	unsigned char _0x88[0x8];
};//Size=0x0090

class FiringFunctionData
{
public:
	struct AmmoConfigData
	{
		int m_MagazineCapacity; // 0x0
		int m_NumberOfMagazines; // 0x4
		unsigned int m_TraceFrequency; // 0x8
		unsigned int m_AmmoPickupMinAmount; // 0xc
		unsigned int m_AmmoPickupMaxAmount; // 0x10
		float m_AutoReplenishDelay; // 0x14
		float m_AmmoBagPickupDelayMultiplier; // 0x18
		int m_AmmoBagPickupAmount; // 0x1c
		bool m_AutoReplenishMagazine; // 0x20
		bool m_StartUnloaded; // 0x21
		unsigned char _0x22[0x2];
	}; // size = 0x24
	struct FireLogicData
	{
		struct HoldAndReleaseData
		{
			float m_MaxHoldTime; // 0x0
			float m_MinPowerModifier; // 0x4
			float m_MaxPowerModifier; // 0x8
			float m_PowerIncreasePerSecond; // 0xc
			float m_Delay; // 0x10
			float m_KilledHoldingPowerModifier; // 0x14
			bool m_ForceFireWhenKilledHolding; // 0x18
			unsigned char _0x19[0x3];
		}; // size = 0x1c

		struct BoltActionData
		{
			float m_BoltActionDelay; // 0x0
			float m_BoltActionTime; // 0x4
			bool m_HoldBoltActionUntilFireRelease; // 0x8
			bool m_HoldBoltActionUntilZoomRelease; // 0x9
			bool m_ForceBoltActionOnFireTrigger; // 0xa
			bool m_UnZoomOnBoltAction; // 0xb
			bool m_ReturnToZoomAfterBoltAction; // 0xc
			unsigned char _0xd[0x3];
		}; // size = 0x10

		struct RecoilData
		{
			float m_MaxRecoilAngleX; // 0x0
			float m_MinRecoilAngleX; // 0x4
			float m_MaxRecoilAngleY; // 0x8
			float m_MinRecoilAngleY; // 0xc
			float m_MaxRecoilAngleZ; // 0x10
			float m_MinRecoilAngleZ; // 0x14
			float m_MaxRecoilFov; // 0x18
			float m_MinRecoilFov; // 0x1c
			bool m_RecoilFollowsDispersion; // 0x20
			unsigned char _0x21[0x3];
		}; // size = 0x24

		enum ReloadLogic
		{
			rlWeaponSwitchCancelsUnfinishedReload = 0x0,
			rlReloadUnaffectedByWeaponSwitch = 0x1,
		};

		enum ReloadType
		{
			rtSingleBullet = 0x0,
			rtMagazine = 0x1,
			rtMagazineWithPossibleShorterReload = 0x2,
		};

		enum FireLogicType
		{
			fltSingleFire = 0x0,
			fltSingleFireWithBoltAction = 0x1,
			fltAutomaticFire = 0x2,
			fltBurstFire = 0x3,
			fltHoldAndRelease = 0x4,
			fltDetonatedFiring = 0x5,
			fltCount = 0x6,
		};

		HoldAndReleaseData m_HoldAndRelease; // 0x0
		BoltActionData m_BoltAction; // 0x1c
		RecoilData m_Recoil; // 0x2c
		int m_FireInputAction; // 0x50
		int m_ReloadInputAction; // 0x54
		int m_CycleFireModeInputAction; // 0x58
		float m_TriggerPullWeight; // 0x5c
		float m_RateOfFire; // 0x60
		float m_RateOfFireForBurst; // 0x64
		float m_DelayBetweenBursts; // 0x68
		float m_ClientFireRateMultiplier; // 0x6c
		float m_ReloadDelay; // 0x70
		float m_ReloadTime; // 0x74
		/*eastl::Array<float> m_ReloadTimerArray*/BYTE pad[8]; // 0x78
		float m_ReloadTimeBulletsLeft; // 0x80
		float m_ReloadThreshold; // 0x84
		float m_PreFireDelay; // 0x88
		float m_PreFireDelayZoomed; // 0x8c
		float m_PreFireRequireHold; // 0x90
		float m_AutomaticDelay; // 0x94
		ReloadLogic m_ReloadLogic; // 0x98
		ReloadType m_ReloadType; // 0x9c
		FireLogicType m_FireLogicType; // 0xa0
		/*unsigned char _0xa4[0x4];
		Array<FireLogicType> m_FireLogicTypeArray; // 0xa8*/
		BYTE pad_00A4[12]; //0x00A4
		bool m_HoldOffReloadUntilFireRelease; // 0xb0
		bool m_HoldOffReloadUntilZoomRelease; // 0xb1
		bool m_ForceReloadActionOnFireTrigger; // 0xb2
		bool m_AlwaysAutoReload; // 0xb3
		bool m_ZoomTransitionDisableFire; // 0xb4
		unsigned char _0xb5[0x3];
	}; // size = 0xb8

	char _0x0000[96];
	ShotConfigData m_ShotConfigData; //0x0060 
	OverheatData m_OverHeatData; //0x00F0 
	__int64 m_FireEffects1; //0x0150 
	__int64 m_FireEffects2; //0x0158 
	__int64 m_pSound; //0x0160 
	FireLogicData m_FireLogic; // 0x168
	AmmoConfigData m_Ammo; // 0x220
	float m_SelfHealTimeWhenDeployed; // 0x244
	bool m_UsePrimaryAmmo; // 0x248
	bool m_UnlimitedAmmoForAI; // 0x249
	unsigned char _0x24a[0x6];
}; // size = 0x250
class ProjectileEntityData
{
public:
	enum AntHitReactionWeaponType
	{
		AntHitReactionWeaponType_Pistol = 0,
		AntHitReactionWeaponType_SMG = 1,
		AntHitReactionWeaponType_AssaultRifle = 2,
		AntHitReactionWeaponType_LMG = 3,
		AntHitReactionWeaponType_Shotgun = 4,
		AntHitReactionWeaponType_SniperRifle = 5,
		AntHitReactionWeaponType_Explosion = 6,
		AntHitReactionWeaponType_Flashbang = 7,
		AntHitReactionWeaponType_Melee = 8
	};
	char _0x0000[96];
	char* m_Name; //0x0060 
	char _0x0068[40];
	float m_InitialSpeed; //0x0090 
	float m_TimeToLive; //0x0094 
	__int32 m_MaxCount; //0x0098 
	float m_InitMeshHideTime; //0x009C 
	float m_VisualConvergeDistance; //0x00A0 
	float m_VisualConvergeDelay; //0x00A4 
	float m_ProxyVisualConvergeDelay; //0x00A8 
	float m_ProxyVisualConvergeDuration; //0x00AC 
	char _0x00B0[16];
	WeaponSuppressionData* m_pSuppressionData; //0x00C0 
	char* m_AmmunitionType; //0x00C8 
	char _0x00D0[4];
	AntHitReactionWeaponType m_HitReactionWeaponType; //0x00D4 
	unsigned char m_DetonateOnTimeout; //0x00D8 
	unsigned char m_ServerProjectileDisabled; //0x00D9 
	bool m_HideOnDetonation; //0x00DA
	bool m_VehicleLightingEnable; // 0xdb
	unsigned char _0xdc[0x4];

};//Size=0x00E0

class MessProjectileEntityData
{
public:
	D3DXVECTOR4 m_AngularVelocity; //0x0000 
	char _0x0010[16]; //0x0010 
	float m_InstantAttachableTestDistance; //0x0020 
	float m_InstantAttachableVisualConvergenceDelay; //0x0024 
	float m_InstantAttachableVisualConvergenceDuration; //0x0028 
	float m_MaxAttachableInclination; //0x002C 
	float m_UnspawnAfterDetonationDelay; //0x0030 
	unsigned char m_IsAttachable; //0x0034 
	unsigned char m_InstantAttachableTestUnderReticle; //0x0035 
	unsigned char m_ExtraDamping; //0x0036 
	char N000019B5[9]; //0x0037 
};//Size=0x0040

class BulletEntityData : public ProjectileEntityData
{
public:
	MessProjectileEntityData m_MeshProjectileEntityData; //0x00E0 
	SoundAsset* m_FlyBySound; //0x0120 
	__int64 m_DudExplosion; //0x0128 
	float m_Gravity; //0x0130 
	float m_ImpactImpulse; //0x0134 
	float m_DetionationTimeVariation; //0x0138 
	float m_VehicleDetonationRadius; //0x013C 
	float m_VehicleDetonationActivationDelay; //0x0140 
	float m_FlyBySoundRadius; //0x0144 
	float m_FlyBySoundSpeed; //0x0148 
	float m_Stamina; //0x014C 
	float m_DistributeDamageOverTime; //0x0150 
	float m_StartDamage; //0x0154 
	float m_EndDamage; //0x0158 
	float m_DamageFalloffStartDist; //0x015C 
	float m_DamageFalloffEndDist; //0x0160 
	float m_TimeToArmExplosion; //0x0164 
	float m_FirstFrameTravelDistance; //0x0168 
	unsigned char m_HasVehicleDetonation; //0x016C 
	unsigned char m_InstantHit; //0x016D 
	unsigned char m_StopTrailEffectOnUnspawn; //0x016E 
	char _0x016F[1];

};//Size=0x0170

class ClientChassisComponent
{
public:
	char pad_0000[208]; //0x0000
	Vector4 N000007EB; //0x00D0
	char pad_00E0[192]; //0x00E0
	Vector m_PrevLinearVelocity; //0x01A0
	char pad_01AC[4]; //0x01AC
	Vector m_AngularVelocity; //0x01B0
	char pad_01BC[4]; //0x01BC
	Vector m_LinearVelocity; //0x01C0
	char _0x01D0[48];
};//Size=0x0200

class ClientVehicleEntity : public ClientControllableEntity
{
public:
	char _0x0188[320 + 8];
	/*float m_waterLevel; //0x0240 
	float m_terrainLevel; //0x0244 
	float m_waterLevelUpdateTimer; //0x0248 
	float m_terrainLevelUpdateTime; //0x024C 
	AxisAlignedBox m_childrenAABB; //0x0250 
	char _0x0268[24];*/
	D3DXVECTOR3 m_VelocityVec; //0x0280 
	char _0x028C[4];
	D3DXVECTOR3 m_prevVelocity; //0x0290 
	float zero2; //0x029C
	char pad_02A0[316]; //0x02A0
	float N000003C6; //0x03DC
	ClientChassisComponent* m_Chassis; //0x03E0
	char pad_03E8[186]; //0x03E8

	ClientChassisComponent* GetChassisComponent()
	{
		return *(ClientChassisComponent**)((uintptr_t)this + 0x03E0);
	}


};//Size=0x0480

class LockingControllerData
{
public:
	struct LockingAndHomingData
	{
		int m_WarnLock; //0x0000
		bool m_IsHoming; //0x0004
		bool m_IsGuided; //0x0005
		bool m_IsGuidedWhenZoomed; //0x0006
		bool m_IsGuidedHoming; //0x0007
		bool m_FireOnlyWhenLockedOn; //0x0008
		char _0x0009[3];
	};//Size=0x000C
	
	char pad[24];
	float m_LockTime; //0x0018
	float m_UnLockTime; //0x001C
	float m_ReleaseTime; //0x0020
	float m_ReleaseOnNewTargetTime; //0x0024
	float m_SampleRate; //0x0028
	float m_HoldStillThreshold; //0x002C
	float m_CheckVisibilityLength; //0x0030
	float m_RayLength; //0x0034
	float m_AcceptanceAngle; //0x0038
	float m_AngleConstant; //0x003C
	float m_DistanceConstant; //0x0040
	float m_Sensitivity; //0x0044
	float m_MinimumLockTime; //0x0048
	LockingAndHomingData m_LockingWeaponData; //0x004C
	bool m_LockOnVisibleTargetsOnly; //0x0058
	bool m_RequireAmmoToLock; //0x0059
	bool m_PositionOnly; //0x005A
	bool m_LockOnWorldSpacePos; //0x005B
	bool m_LockOnEmptyVehicles; //0x005C
	bool m_LockOnCharacters; //0x005D
	bool m_IgnoreHeigthLockDistance; //0x005E
	bool m_LockInCombatAreaOnly; //0x005F
};//Size=0x0060

class MeshProjectileEntityData : public ProjectileEntityData
{
public:
	
	D3DXVECTOR3 m_InitialAngularVelocity; //0x00E0
	void* m_Mesh; //0x00F0
	void* m_TrailEffect; //0x00F8
	float m_InstantAttachableTestDistance; //0x0100
	float m_InstantAttachableVisualConvergenceDelay; //0x0104
	float m_InstantAttachableVisualConvergenceDuration; //0x0108
	float m_MaxAttachableInclination; //0x010C
	float m_UnspawnAfterDetonationDelay; //0x0110
	bool m_IsAttachable; //0x0114
	bool m_InstantAttachableTestUnderReticule; //0x0115
	bool m_ExtraDamping; //0x0116
	char _0x0117[9];
};//Size=0x0120

struct MissileUnguidedData
{
	D3DXVECTOR2 m_StaticPosition; //0x0000
	D3DXVECTOR2 m_TargetPositionOffset; //0x0008
	bool m_UseStaticPosition; //0x0010
	bool m_UseTargetPosition; //0x0011
	char _0x0012[2];
};//Size=0x0014

struct MissileLockableInfoData
{
	float m_HeatSignature; //0x0000
	float m_RadarSignature; //0x0004
};//Size=0x0008

struct NearTargetDetonationData
{
	float m_DetonationRadius; //0x0000
	float m_MaxDetonationDelay; //0x0004
	float m_MinDetonationDelay; //0x0008
	bool m_DetonateNearTarget; //0x000C
	char _0x000D[3];
};//Size=0x0010

class ExplosionEntityData// : public SpatialEntityData
{
public:

	char pad[96];
	/*EffectBlueprint**/void* m_DetonationEffect; //0x0060
	/*EffectBlueprint**/void* m_DetonationEffectForFriendlies; //0x0068
	/*MaskVolumeEntityData**/void* m_MaskVolume; //0x0070
	/*DestructionMaskVolumeEntityData**/void* m_DestructionMaskVolume; //0x0078
	char pad1[0x8C - 0x78];
	//MaterialDecl m_MaterialPair; //0x0080
	//MaterialDecl m_SecondaryMaterialPair; //0x0084
	//DamageIndicationType m_DamageIndicationType; //0x0088
	float m_EmpTime; //0x008C
	float m_MaxOcclusionRaycastRadius; //0x0090
	float m_InnerBlastRadius; //0x0094
	float m_BlastDamage; //0x0098
	float m_BlastRadius; //0x009C
	float m_BlastImpulse; //0x00A0
	float m_ShockwaveDamage; //0x00A4
	float m_ShockwaveRadius; //0x00A8
	float m_ShockwaveImpulse; //0x00AC
	float m_ShockwaveTime; //0x00B0
	float m_CameraShockwaveRadius; //0x00B4
	float m_SpawnDelay; //0x00B8
	bool m_NoFriendliesEffectOnEnabledFriendlyFire; //0x00BC
	bool m_UseEntityTransformForDetonationEffect; //0x00BD
	bool m_SecondaryMaterialsActive; //0x00BE
	bool m_HasStunEffect; //0x00BF
	bool m_DisableOcclusion; //0x00C0
	bool m_DisableStaticEntityOcclusion; //0x00C1
	bool m_TriggerImpairedHearing; //0x00C2
	bool m_Enabled; //0x00C3
	char _0x00C4[12];
};//Size=0x00D0

class GhostedProjectileEntityData : public MeshProjectileEntityData
{
public:
	
	float m_ProxyConvergenceDelay; //0x0120
	float m_ProxyConvergenceDuration; //0x0124
	bool m_ProxyConvergenceInstantOnAttach; //0x0128
	bool m_ForceProxyConvergence; //0x0129
	char _0x012A[6];
};//Size=0x0130

class MissileEntityData : public GhostedProjectileEntityData
{
public:
	enum WarnTarget
	{
		wtWarnSoldierAndVehicle = 0x0,
		wtWarnSoldier = 0x1,
		wtWarnVehicle = 0x2,
		wtWarnNone = 0x3,
	};

	void* m_EngineEffect; //0x0130
	ExplosionEntityData* m_DudExplosion; //0x0138
	SoundAsset* m_FlyBySound; //0x0140
	float m_EngineStrength; //0x0148
	float m_MaxSpeed; //0x014C
	float m_EngineTimeToIgnition; //0x0150
	float m_EngineTimeToLive; //0x0154
	float m_TimeToActivateGuidingSystem; //0x0158
	float m_TimeToArm; //0x015C
	float m_MaxTurnAngle; //0x0160
	float m_MinTurnAngle; //0x0164
	float m_TurnAngleMultiplier; //0x0168
	float m_Drag; //0x016C
	float m_Gravity; //0x0170
	float m_FlyBySoundRadius; //0x0174
	float m_FlyBySoundSpeed; //0x0178
	float m_ImpactImpulse; //0x017C
	float m_Damage; //0x0180
	int m_DefaultTeam; //0x0184
	WarnTarget m_WarnTarget; // 0x188
	unsigned char _0x18c[0x4];
	LockingControllerData* m_LockingController; // 0x190
	MissileLockableInfoData m_LockableInfo; //0x0198
	MissileUnguidedData m_UnguidedData; //0x01A0
	NearTargetDetonationData m_NearTargetDetonation; //0x01B4
	float m_MaxBankAngle; //0x01C4
	float m_BankingSpeed; //0x01C8
	char _0x01CC[4];
	CString m_Icon; //0x01D0
	CString m_TargetIcon; //0x01D8
	CString m_TargetIconEnemy; //0x01E0
	float m_MinGhostFrequency; //0x01E8
	bool m_ApplyGravityWhenGuided; //0x01EC
	bool m_WarnOnPointingMissile; //0x01ED
	bool m_EnableBanking; //0x01EE
	char _0x01EF[1];

	bool IsLaserGuided(); //m_MinTurnAngle > 0.0f
	bool IsLockable(); //m_TimeToActivateGuidingSystem > 0.0f
};

class VeniceClientMissileEntity //or : inherit from ClientGameComponentEntity..etc
{
public:
	virtual void unkn0();
	virtual void unkn1();
	virtual void unkn2();
	virtual void unkn3();
	virtual void unkn4();
	virtual void unkn5();
	virtual void unkn6();
	virtual void unkn7();
	virtual void unkn8();
	virtual void unkn9();
	virtual void unkn10();
	virtual void unkn11();
	virtual void unkn12();
	virtual void unkn13();
	virtual void unkn14();
	virtual void unkn15();
	virtual void unkn16();
	virtual void unkn17();
	virtual void unkn18();
	virtual void unkn19();
	virtual void unkn20();
	virtual void GetAABB(TransformAABBStruct* mataabb); //22
	virtual void GetTransform(D3DXMATRIX* mTransform); //23

	char _0x008[0x28];
	MissileEntityData* m_pMissileEntityData;//0x030
	char _0x038[0x238 - 0x038];
	WeakPtr<ClientPlayer> m_pOwner;//0x238
	//SoldierWeaponUnlockAsset* m_pUnlockAsset; //0x0240
	char pad_0240[32]; //0x0240
	D3DXVECTOR3 N000000A4; //0x0260
	D3DXVECTOR3 N000000A5; //0x026C
	D3DXVECTOR3 N000000A6; //0x0278
	D3DXVECTOR3 N000000A7; //0x0284
	D3DXVECTOR3 m_Position; //0x0290
};

class WeaponSuppressionData
{
public:
	char _0x0000[16];
	float m_MinMultiplier; //0x0010 
	float m_MaxMultiplier; //0x0014 
	float m_MinDistance; //0x0018 
	float m_MaxDistance; //0x001C 

};//Size=0x0020

class SoundAsset
{
public:
	char _0x0000[24];
	SoundScopeData* m_Scope; //0x0018 
	SoundScopeData* m_ReferencedData; //0x0020 

};//Size=0x0028

class SoundScopeData
{
public:
	char _0x0000[16];
	char* m_Name; //0x0010 
	SoundScopeStrategyData* m_ScopeStrategyData; //0x0018 

};//Size=0x0020

class SoundScopeStrategyData
{
public:
	char _0x0000[16];
	char* m_Name; //0x0010 
	char* m_Stages; //0x0018 
	char N000019E8[32]; //0x0020 

};//Size=0x0040

class WeaponModifier
{
public:
	char _0x0000[64];
	unsigned char m_BreathControl; //0x0040 
	unsigned char m_SupportedShooting; //0x0041 
	unsigned char m_UnZoomOnBoltAction; //0x0042 
	unsigned char m_HoldBoltActionUntilZoomRelease; //0x0043 
	char _0x0044[12];
	FiringDataModifier* m_FiringDataModifier; //0x0050 
	FiringEffectsModifier* m_FiringEffectsModifier; //0x0058 
	SoundModifier* m_SoundModifier; //0x0060 
	WeaponShotModifier* m_ShotModifier; //0x0068 
	char _0x0070[56];
	AimingSimulationModifier* m_AimingSimulationModifier; //0x00A8 
	char _0x00B0[16];
	ZeroingModifier* m_ZeroingModifier; //0x00C0 
	char _0x00C8[48];
};//Size=0x0044

class VehicleTurret
{
public:
	static VehicleTurret* GetInstance()
	{
		return (VehicleTurret*)OFFSET_ANGLES;
	}

	char pad_0000[8]; //0x0000
	WeaponFiring* m_pWeaponFiring; //0x0008
	char pad_0010[32]; //0x0010
	D3DXMATRIX m_VehicleMatrix; //0x0030
	D3DXMATRIX m_SoldierMatrix; //0x0070
	float m_VehicleYawFixed; //0x00B0
	Vector2D m_Angles; //0x00B4
	float m_ZeroFloat; //0x00BC Always == zero
	bool m_SomeBool; //0x00C0

	Vector GetVehicleCameraOrigin();
	Vector GetVehicleCrosshair();
}; //Size: 0x011C

enum class WeaponClass
{
	_12gauge = 0x0,
	_338Magnum = 0x1,
	_357Magnum = 0x2,
	_44Magnum = 0x3,
	_45cal = 0x4,
	_46x30mm = 0x5,
	_50cal = 0x6,
	_545x45mmWP = 0x7,
	_556x45mmNATO = 0x8,
	_57x28mm = 0x9,
	_58x42mm = 0xa,
	_762x39mmWP = 0xb,
	_762x51mmNATO = 0xc,
	_762x54mmR = 0xd,
	_9x19mm = 0xe,
	_9x39mm = 0xf,
	Assault = 0x10,
	Shotgun = 0x11,
	Smg = 0x12,
	Lmg = 0x13,
	Sniper = 0x14,
	Ugl = 0x15,
	Hgr = 0x16,
	At = 0x17,
	ATMine = 0x18,
	C4 = 0x19,
	BallisticShield = 0x1a,
	AutoInjector = 0x1b,
	Knife = 0x1c,
	LaserDesignator = 0x1d,
	LaserPainter = 0x1e,
	MedKit = 0x1f,
	MortarStrike = 0x20,
	PowerTool = 0x21,
	TracerDart = 0x22,
	RadioBeacon = 0x23,
	EodBot = 0x24,
	ReconMav = 0x25,
	UGS = 0x26,
	Unarmed = 0x27,
	Count = 0x28,
	None = 0x29,
};

class WeaponEntityData
{
public:
	char pad[0x80];
	WeaponClass m_WeaponClass; // 0x80
	//unsigned char _0x84[0x4];
	//Array<WeaponStateData> m_WeaponStates; // 0x88
	//WeaponFiringData* m_WeaponFiring; // 0x90
	//WeaponData* m_CustomWeaponType; // 0x98
	//GameAIWeaponData* m_AIData; // 0xa0
	//unsigned char _0xa8[0x8];
}; // size = 0xb0

class WeaponFiring
{
public:
	static WeaponFiring* GetInstance()
	{
		return *(WeaponFiring**)OFFSET_PPCURRENTWEAPONFIRING;
	}

	enum WeaponFiringEvent
	{
		WeaponFiringEvent_Push = 0x0,
		WeaponFiringEvent_Pop = 0x1,
		WeaponFiringEvent_PrimaryStartedFiringCallback = 0x2,
		WeaponFiringEvent_PrimaryFireCallback = 0x3,
		WeaponFiringEvent_PrimaryFireReleaseCallback = 0x4,
		WeaponFiringEvent_PrimaryFireShotSpawnedCallback = 0x5,
		WeaponFiringEvent_PrimaryFireAutomaticBeginCallback = 0x6,
		WeaponFiringEvent_PrimaryFireAutomaticEndCallback = 0x7,
		WeaponFiringEvent_PrimaryStoppedFiringCallback = 0x8,
		WeaponFiringEvent_ReloadPrimaryCallback = 0x9,
		WeaponFiringEvent_ReloadPrimaryEndCallback = 0xa,
		WeaponFiringEvent_BoltActionCallback = 0xb,
		WeaponFiringEvent_BoltActionEndCallback = 0xc,
		WeaponFiringEvent_DetonationSwitchCallback = 0xd,
		WeaponFiringEvent_HoldAndReleaseReleaseCallback = 0xe,
		WeaponFiringEvent_UpdateRequired = 0xf,
	};

	char _0x0000[120];
	WeaponSway* m_Sway; //0x0078 
	char _0x0080[168];
	PrimaryFire* m_pPrimaryFire; //0x0128 
	char _0x138[8];
	WeaponComponentData* m_weaponComponentData; //0x0138
	char _0x0130[8];
	int32_t m_WeaponState; //0x0148
	int32_t m_LastWeaponState; //0x014C
	int32_t m_NextWeaponState; //0x0150
	float m_Zero; //0x0154
	float m_MagazineReloadTime; //0x0158 ???? 10, 15, 20, 25 and so on
	float m_TimeToWait; //0x015C
	float m_ReloadTimer; //0x0160
	float m_HoldReleaseMinDelay; //0x0164
	float m_RecoilTimer; //0x0168
	float m_RecoilAngleX; //0x016C
	float m_RecoilAngleY; //0x0170
	float m_RecoilAngleZ; //0x0174
	float m_RecoilFOVAngle; //0x0178
	float m_RecoilTimeMultiplier; //0x017C
	float m_OverheatDropMultiplier; //0x0180
	char pad_0184[28]; //0x0184
	int32_t m_FirstSlotBullets; //0x01A0
	int32_t m_SecondSlotBullets; //0x01A4
	char pad_01A8[4]; //0x01A8
	bool m_IsNotFiring; //0x01AC
	bool m_JustShot; //0x01AD
	bool m_IsCoolingDown; //0x01AE
	bool m_IsOverheated; //0x01AF
	float m_Overheat; //0x01B0
	char pad_01B4[4]; //0x01B4
	int32_t m_CurrTimeWhenReadyToFire; //0x01B8
	char pad_01BC[224]; //0x01BC

	WeaponClass GetWeaponClass();
};//Size=0x01AF

class ClientSoldierBodyComponent
{
public:
	char _0x0000[64];

};//Size=0x0040

class SkeletonAsset
{
public:
	char _0x0000[24];
	char** m_ppBoneNames; //0x0018
};//Size=0x0020

class AnimationSkeleton
{
public:
	SkeletonAsset* m_SkeletonAsset; //0x0000 
	__int32 m_BoneCount; //0x0008 
	const char* GetBoneNameAt(int i);
};//Size=0x000C

class QuatTransform
{
public:
	D3DXVECTOR4 m_TransAndScale; //0x0000 
	D3DXVECTOR4 m_Rotation; //0x0010 
};//Size=0x0020

class UpdatePoseResultData
{
public:
	enum BONES
	{
		Reference = 0,
		AITrajectory = 1,
		Trajectory = 2,
		TrajectoryEnd = 3,
		Hips = 4,
		Spine = 5,
		Spine1 = 6,
		Spine2 = 7,
		LeftShoulder = 8,
		LeftArm = 9,
		LeftArmRoll = 10,
		LeftForeArm = 11,
		LeftForeArmRoll = 12,
		LeftForeArmRoll1 = 13,
		LeftHand = 14,
		LeftHandMiddle0 = 15,
		LeftHandMiddle1 = 16,
		LeftHandMiddle2 = 17,
		LeftHandMiddle3 = 18,
		LeftHandMiddle4 = 19,
		LeftHandRing0 = 20,
		LeftHandRing1 = 21,
		LeftHandRing2 = 22,
		LeftHandRing3 = 23,
		LeftHandRing4 = 24,
		LeftHandPinky0 = 25,
		LeftHandPinky1 = 26,
		LeftHandPinky2 = 27,
		LeftHandPinky3 = 28,
		LeftHandPinky4 = 29,
		LeftHandIndex0 = 30,
		LeftHandIndex1 = 31,
		LeftHandIndex2 = 32,
		LeftHandIndex3 = 33,
		LeftHandIndex4 = 34,
		LeftHandThumb1 = 35,
		LeftHandThumb2 = 36,
		LeftHandThumb3 = 37,
		LeftHandThumb4 = 38,
		LeftHandProp1 = 39,
		LeftElbowRoll = 40,
		LeftArmCloth = 41,
		LeftShoulderPhys1 = 42,
		Neck = 43,
		Neck1 = 44,
		Head = 45,
		HeadEnd = 46,
		Face = 47,
		Jaw = 48,
		LeftLowerLip = 49,
		LeftLowerInnerLip = 50,
		LowerLip = 51,
		LowerInnerLip = 52,
		RightLowerLip = 53,
		RightLowerInnerLip = 54,
		Tongue = 55,
		TongueTip = 56,
		Chin = 57,
		LeftLowCheek = 58,
		RightLowCheek = 59,
		LeftEye = 60,
		LeftIris = 61,
		RightEye = 62,
		RightIris = 63,
		LeftUpCheek = 64,
		LeftUpInnerCheek = 65,
		RightUpInnerCheek = 66,
		RightUpCheek = 67,
		LeftCheek = 68,
		RightCheek = 69,
		LeftMouth = 70,
		LeftInnerMouth = 71,
		LeftMiddleCrease = 72,
		LeftUpperLip = 73,
		LeftUpperInnerLip = 74,
		UpperLip = 75,
		UpperInnerLip = 76,
		RightUpperLip = 77,
		RightUpperInnerLip = 78,
		RightMouth = 79,
		RightInnerMouth = 80,
		RightMiddleCrease = 81,
		LeftUpEyelid = 82,
		RightUpEyelid = 83,
		LeftLowEyelid = 84,
		RightLowEyelid = 85,
		LeftInnerEyebrow = 86,
		LeftOuterEyebrow = 87,
		RightInnerEyebrow = 88,
		RightOuterEyebrow = 89,
		LeftNose = 90,
		RightNose = 91,
		LeftCrease = 92,
		RightCrease = 93,
		LeftLowMiddleEyebrow = 94,
		RightMiddleEyebrow = 95,
		LeftLowEyelidCrease = 96,
		LeftLowOuterEyebrow = 97,
		NoseTip = 98,
		RightLowOuterEyebrow = 99,
		LeftMiddleEyebrow = 100,
		RightLowMiddleEyebrow = 101,
		RightLowEyelidCrease = 102,
		LowNose = 103,
		HeadCloth = 104,
		Throat = 105,
		Spine2Phys1 = 106,
		Spine2Prop1 = 107,
		RightShoulder = 108,
		RightArm = 109,
		RightArmRoll = 110,
		RightForeArm = 111,
		RightForeArmRoll = 112,
		RightForeArmRoll1 = 113,
		RightHand = 114,
		RightHandMiddle0 = 115,
		RightHandMiddle1 = 116,
		RightHandMiddle2 = 117,
		RightHandMiddle3 = 118,
		RightHandMiddle4 = 119,
		RightHandRing0 = 120,
		RightHandRing1 = 121,
		RightHandRing2 = 122,
		RightHandRing3 = 123,
		RightHandRing4 = 124,
		RightHandPinky0 = 125,
		RightHandPinky1 = 126,
		RightHandPinky2 = 127,
		RightHandPinky3 = 128,
		RightHandPinky4 = 129,
		RightHandIndex0 = 130,
		RightHandIndex1 = 131,
		RightHandIndex2 = 132,
		RightHandIndex3 = 133,
		RightHandIndex4 = 134,
		RightHandThumb1 = 135,
		RightHandThumb2 = 136,
		RightHandThumb3 = 137,
		RightHandThumb4 = 138,
		RightHandProp1 = 139,
		RightElbowRoll = 140,
		RightArmCloth = 141,
		RightShoulderPhys1 = 142,
		Wep_Root = 143,
		Wep_Trigger = 144,
		Wep_Slide = 145,
		Wep_Grenade1 = 146,
		Wep_Grenade2 = 147,
		Wep_Mag = 148,
		Wep_Mag_Ammo = 149,
		Wep_Mag_Extra1 = 150,
		Wep_Scope1 = 151,
		Wep_Scope2 = 152,
		Wep_Belt1 = 153,
		Wep_Belt2 = 154,
		Wep_Belt3 = 155,
		Wep_Belt4 = 156,
		Wep_Belt5 = 157,
		Wep_Belt6 = 158,
		Wep_Belt7 = 159,
		Wep_Belt8 = 160,
		Wep_Belt9 = 161,
		Wep_Belt10 = 162,
		Wep_Bipod1 = 163,
		Wep_Bipod2 = 164,
		Wep_Bipod3 = 165,
		IK_Joint_LeftHand = 166,
		IK_Joint_RightHand = 167,
		Wep_Physic1 = 168,
		Wep_Physic2 = 169,
		Wep_Physic3 = 170,
		Wep_Physic4 = 171,
		Wep_Physic5 = 172,
		Wep_Extra1 = 173,
		Wep_Extra2 = 174,
		Wep_Extra3 = 175,
		Wep_Extra4 = 176,
		Wep_Extra5 = 177,
		Wep_Aim = 178,
		LeftSpine1Phys1 = 179,
		RightSpine1Phys1 = 180,
		LeftUpLeg = 181,
		LeftUpLegRoll = 182,
		LeftLeg = 183,
		LeftFoot = 184,
		LeftToeBase = 185,
		LeftToe = 186,
		LeftLegCloth = 187,
		LeftKneeRoll = 188,
		LeftHipsRoll = 189,
		LeftUpLegCloth = 190,
		HipsCloth = 191,
		LeftHipsFrontPhys = 192,
		LeftHipsBackPhys = 193,
		LeftHipsSidePhys = 194,
		RightUpLeg = 195,
		RightUpLegRoll = 196,
		RightLeg = 197,
		RightFoot = 198,
		RightToeBase = 199,
		RightToe = 200,
		RightLegCloth = 201,
		RightKneeRoll = 202,
		RightHipsRoll = 203,
		RightUpLegCloth = 204,
		RightHipsFrontPhys = 205,
		RightHipsBackPhys = 206,
		RightHipsSidePhys = 207,
		CameraBase = 208,
		CameraJoint = 209,
		Connect = 210,
		ConnectEnd = 211,
		FacePosesAnimation = 212
	};
	QuatTransform* m_LocalTransform; //0x0000 
	QuatTransform* m_WorldTransform; //0x0008 
	QuatTransform* m_Unk; //0x0010 
	QuatTransform* m_Unk1; //0x0018 
	QuatTransform* m_Unk2; //0x0020 
	QuatTransform* m_ActiveWorldTransforms; //0x0028 
	QuatTransform* m_ActiveLocalTransforms; //0x0030 
	__int32 m_Slot; //0x0038 
	__int32 m_ReaderIndex; //0x003C 
	unsigned char m_ValidTransforms; //0x0040 
	unsigned char m_PoseUpdateEnabled; //0x0041 
	unsigned char m_PoseNeeded; //0x0042 
	char _0x0043[1];
};//Size=0x0044

class RagdollComponent
{
public:

	char _0x0000[16];
	__int64 m_pData; //0x0010 
	char _0x0018[8];
	__int64 m_pEntry; //0x0020 
	char _0x0028[32];
	__int64 m_RagdollCompData; //0x0048 
	char _0x0050[8];
	AnimationSkeleton* m_AnimationSkeleton; //0x0058 
	char _0x0060[40];
	UpdatePoseResultData m_PoseResultData; //0x0088 
	char _0x00CC[56];

	bool GetBone(const UpdatePoseResultData::BONES BoneId, D3DXVECTOR3& BoneOut)
	{
		UpdatePoseResultData PoseResult = this->m_PoseResultData;
		if (PoseResult.m_ValidTransforms)
		{
			QuatTransform* pQuat = PoseResult.m_ActiveWorldTransforms;
			if (!pQuat)
				return false;

			D3DXVECTOR4 Bone = pQuat[BoneId].m_TransAndScale;
			BoneOut = D3DXVECTOR3(Bone.x, Bone.y, Bone.z);
			return true;
		}
		return false;
	}
};//Size=0x0104

class ParachuteComponent
{
public:
	char _0x0000[64];

};//Size=0x0040

class SpottingComponent
{
public:
	char _0x0000[64];

};//Size=0x0040

class SpottingTargetComponent
{
public:
	char _0x0000[64];

};//Size=0x0040

class VaultComponentData// : public GameComponentData
{
public:
	char pad_0000[112]; //0x0000
	float m_StartHeightMax; //0x0070
	float m_StartHeightMin; //0x0074
	char pad_0078[144]; //0x0078 //Size: 0x0108
};//Size=0x0130

class VaultComponent
{
public:
	char pad_0000[16]; //0x0000
	class VaultComponentData* m_pVaultData; //0x0010
	char pad_0018[216]; //0x0018
	int32_t m_VaultState; //0x00F0
	char pad_00F4[140]; //0x00F4
	D3DXVECTOR3 m_OldPosition; //0x0180
	float unkn; //0x018C
	float m_HeightVaulted; //0x0190
	char pad_0194[12]; //0x0194
	D3DXVECTOR3 m_NewPosition; //0x01A0
	char pad_01AC[160]; //0x01AC
	float unkn2; //0x024C
	D3DXVECTOR3 m_TeleportVector; //0x0250
	char pad_025C[48]; //0x025C
};//Size=0x0040

class SoldierSuppressionComponent
{
public:
	char _0x0000[64];

};//Size=0x0040



template <class T> class EntityIterator
{
public:
	class Element
	{
	public:

		Element* m_pFlink;
		Element* m_pBlink;
		__int32  m_Unk1;
		__int32  m_Unk2;

		T* getObject()
		{
			intptr_t pObject = reinterpret_cast<intptr_t>(this);
			pObject -= 0x40;

			return reinterpret_cast<T*>(pObject);
		}
	};

	Element* m_pFirst;
	Element* m_pCurrent;

	EntityIterator(void* pGameWorld, void* pClassInfo)
	{
		typedef Element* (__thiscall* tGetEntityList)(void* pClassInfo, void* pThis);
		tGetEntityList lpGetEntityList = reinterpret_cast<tGetEntityList>(OFFSET_GETENTITYLIST);

		this->m_pFirst = lpGetEntityList(pClassInfo, pGameWorld);
		this->m_pCurrent = this->m_pFirst;
	}

	bool hasNext()
	{
		if (m_pCurrent && m_pCurrent->m_pFlink)
			return true;

		return false;
	}

	Element* first() { return m_pFirst; }
	Element* front() { return m_pCurrent; }
	Element* next()
	{
		if (!m_pFirst) return nullptr;

		m_pCurrent = m_pCurrent->m_pFlink;

		return m_pCurrent;
	}
};

class WeaponShotModifier
{
public:
	char _0x0000[24];
	__int32 m_NumberOfBulletsPerShell; //0x0018 
	char _0x001C[4];
	D3DXVECTOR3 m_InitialSpeed; //0x0020 

};//Size=0x002C

class SoundModifier
{
public:
	char _0x0000[64];

};//Size=0x0040

class FiringEffectsModifier
{
public:
	char _0x0000[64];

};//Size=0x0040

class FiringDataModifier
{
public:
	char _0x0000[64];

};//Size=0x0040

class ProjectileModifier
{
public:
	char _0x0000[64];

};//Size=0x0040

class m_AimingSimulationModifier
{
public:
	char _0x0000[64];

};//Size=0x0040

class AimingSimulationModifier
{
public:
	char _0x0000[64];

};//Size=0x0040

class WeaponZeroingEntry
{
public:
	float m_ZeroDistance; //0x0000 
	float m_Angle; //0x0004 

	WeaponZeroingEntry(float Dist, float Angle)
	{
		m_ZeroDistance = Dist;
		m_Angle = Angle;
	}
};//Size=0x0008

class ZeroingModifier
{
public:
	char _0x0000[24];
	WeaponZeroingEntry* m_ppZeroLevels;
	float m_DefaultZeroingDistance; //0x0020 

	WeaponZeroingEntry GetZeroLevelAt(int index);
};//Size=0x0038

class WeaponSway
{
public:
	char _0x0000[8];
	GunSwayData* m_Data; //0x0008 
};//Size=0x0010

class GunSwayData
{
public:
	char _0x0000[1088];
	float m_ShootingRecoilDecreaseScale; //0x0440 
	float m_FirstShotRecoilMultiplier; //0x0444 
	__int64 m_CamerRecoilData; //0x0448 
};//Size=0x0450

class WeaponComponentData
{
public:
	char _0x0000[0x70];
	D3DXVECTOR4 m_ProjectileSpawnOffset; //0x0070
	D3DXVECTOR4 m_TargetPositionOverride; //0x0080
	void* m_WeaponMesh; //0x0090
	WeaponFiring* m_WeaponFiring; //0x0098
	char* m_pDamageGiverName; //0x00A0
	void* m_AIData; //0x00A8
	void* m_CustomWeaponType; //0x00B0
	float m_ImpulseStrength; //0x00B8
	DWORD m_Classification; //0x00BC
	float m_ReloadTimeMultiplier; //0x00C0
	float m_DamageMultiplier; //0x00C4
	float m_ExplosionDamageMultiplier; //0x00C8
	float m_OverheatDropPerSecondMultiplier; //0x00CC
	float m_LockTimeMultiplier; //0x00D0
	float m_LockingAcceptanceAngleMultiplier; //0x00D4
	DWORD m_WeaponItemHash; //0x00D8
	bool m_SequentialFiring; //0x00DC
	char _0x00DD[0x3];
}; //0x00E0

struct WeaponData_s
{
	D3DXVECTOR3 speed = { -1.f, -1.f, -1.f };
	std::string gunName = "Error";
	float gravity = 1.f;
	bool isValid = false;
	ClientWeapon* pWeapon = nullptr;
	int gunID = -1;

};

class EntryComponent
{
public:

	class WeaponFiringCallbacks
	{
	public:
		virtual void fc0();
	}; // fb::WeaponFiringCallbacks

	class WeaponInfo
	{
	public:
		virtual void WorldTransfrom(D3DXMATRIX&);
		virtual void GetState(int&);
		virtual void AddWeaponFiringCallbcks(void*);
		virtual void RemoveWeaponFiringCallbcks(void*);
		virtual WeaponFiring* GetWeaponFiring();
		virtual ClientWeapon* GetWeapon();
		virtual bool ActiveInStance(int);
		virtual ClientWeaponComponent* GetWeaponComponent();

		ClientWeaponComponent* m_pWeaponComponent; //0x0008
	};
	class Subscriber
	{
	public:
		virtual void onUnSpawn();
	};
	class FiringCallbacks
		:public WeaponFiringCallbacks
	{
	public:
		EntryComponent* m_entry;
		WeaponInfo* m_info;
	};
	class InputModifier
	{
	public:
		unsigned int actionIndex;
		//PropertyReader<bool> enabled;
		//PropertyReader<float> offset;
		//PropertyReader<float> scale;
	};

	class State
	{
	public:
		unsigned int m_currentCameraIndex;
		unsigned int m_previousCameraIndex;
		int m_activeStance;
		int m_previousStance;
		bool m_stanceResetOnExit;
	};


	virtual unsigned int getActiveStance();
	virtual bool isCharacterControlEntry();
	virtual void /*struct AnimTreeDataAsset */animTree();
	virtual void onPrimaryStartedFiring(EntryComponent::WeaponInfo*);
	virtual void onPrimaryFire(EntryComponent::WeaponInfo*);
	virtual void onPrimaryFireRelease(EntryComponent::WeaponInfo*);
	virtual void onPrimaryFireShotSpawned(EntryComponent::WeaponInfo*, float);
	virtual void onPrimaryFireAutomaticBegin(EntryComponent::WeaponInfo*);
	virtual void onPrimaryFireAutomaticEnd(EntryComponent::WeaponInfo*);
	virtual void onPrimaryStoppedFiring(EntryComponent::WeaponInfo*);
	virtual void onReload(EntryComponent::WeaponInfo*);
	virtual /*EntryComponentData**/void* entryData();
	virtual void onSwitchStance();
	virtual bool isStanceAvailable(int);

	eastl::vector<FiringCallbacks*> m_weapons;
	eastl::vector<Subscriber*> m_subscribers;
	void* m_turretComponent;
	boolean m_underExternalControl;
	byte placeholder;
	__int16 m_inputModifierCacheSize;
	//fb::EntryComponent::InputModifier* m_inputModifierCache;

	
};

class ClientExplosionEntity
{
public:
	virtual void unkn0();
	virtual void unkn1();
	virtual void unkn2();
	virtual void unkn3();
	virtual void unkn4();
	virtual void unkn5();
	virtual void unkn6();
	virtual void unkn7();
	virtual void unkn8();
	virtual void unkn9();
	virtual void unkn10();
	virtual void unkn11();
	virtual void unkn12();
	virtual void unkn13();
	virtual void unkn14();
	virtual void unkn15();
	virtual void unkn16();
	virtual void unkn17();
	virtual void unkn18();
	virtual void unkn19();
	virtual void unkn20();
	virtual void GetAABB(TransformAABBStruct* mataabb); //22
	virtual void GetTransform(D3DXMATRIX* mTransform); //23
};

class ClientIndirectFireWeapon
{
public:
	char pad[2928];
	D3DXVECTOR4 offsetstuffs; //0x0B70 
	__int32 integer; //0x0B80 
	float timesincedeployed; //0x0B84 
	float countlastfire; //0x0B88 
	char pad_0x0B8C[0x4]; //0x0B8C
	D3DXVECTOR4 landingpos; //0x0B90 
	D3DXVECTOR4 landingpos2; //0x0BA0 
	bool boole; //0x0BB0
	char pad_0x0BB1[0xA]; //0x0BB0
};//Size=0x0BC0

class ClientWeaponComponent
{
public:
	char _0x0000[0x10];
	WeaponComponentData* m_pComponentData; //0x0010
	char _0x0018[0x8];
	EntryComponent* m_pPlayerEntry; //0x0020
	char _0x0028[0x28];
	/*DynamicPhysicsEntity**/void* m_physicsEntity; //0x0050 Start of WeaponComponent
	char _0x0008[0x30];
	void* m_interpolationObject; //0x0088
	ClientWeapon* m_pWeapon; //0x0090
	void* m_pController; //0x0098 ClientWeaponComponentSimulation
	void* m_pReplicatedWeapon; //0x00A0 ClientWeaponComponentReplication
	void* m_pPredictedWeapon; //0x00A8 ClientWeaponComponentPrediction
	void* m_pLockingController; //0x00B0 ClientLockingController null
	void* m_pSecondaryLockingController; //0x00B8 ClientLockingController null
	ClientPlayer* m_pPlayer; //0x00C0
	EntryComponent::WeaponInfo* m_pWeaponInfo; //0x00C8
	EntryComponent::FiringCallbacks* m_pWeaponFiringCallback; //0x00D0
	void* m_pWeaponMeshModel; //0x00D8 MeshModel null
	void* m_pFiringEntry; //0x00E0 ClientPlayerEntryComponent
	char _0x0098[0x18];
}; //0x00B0

class StaticCamera
{
public:
	struct HudData
	{
		class DataContainer
		{
		public:
			unsigned char _0x0[0x10];
		}; // size = 0x10
		class CrosshairTypeAsset
		{
		public:
			char aAsset[24]; //+0x00 Inherited
		};
		class LockingTypeAsset
		{
		public:
			char aAsset[24]; //+0x00 Inherited
		};
		class UIPartPropertyList : public DataContainer
		{
		public:
			DataContainer* m_HudPropertyList; //+0x10
		};
		float m_CrosshairScaleMin; // 0x0
		float m_CrosshairScaleMax; // 0x4
		float m_CrosshairOpacityMin; // 0x8
		float m_CrosshairOpacityMax; // 0xc
		float m_CrosshairOpacityModifier; // 0x10
		unsigned char _0x14[0x4];
		const char* m_CrosshairTypeId; // 0x18
		CrosshairTypeAsset* m_CrosshairType; // 0x20
		LockingTypeAsset* m_LockingType; // 0x28
		const char* m_WeaponClass; // 0x30
		float m_LowAmmoWarning; // 0x38
		float m_ReloadPrompt; // 0x3c
		int m_RenderTargetIndex; // 0x40
		unsigned char _0x44[0x4];
		UIPartPropertyList* m_HudPropertyList; // 0x48
		float m_SeaLevelAltFreq; // 0x50
		float m_CameraShakeModifier; // 0x54
		const char* m_HudIcon; // 0x58
		bool m_ShowMinimap; // 0x60
		bool m_HideAmmo; // 0x61
		bool m_InfiniteAmmo; // 0x62
		bool m_HideCrosshairWhenAimOnFriend; // 0x63
		bool m_UseRenderTarget; // 0x64
		bool m_UseRangeMeter; // 0x65
		bool m_UseAimWarning; // 0x66
		bool m_UsePredictedSight; // 0x67
		bool m_UseWeaponOrientations; // 0x68
		bool m_UseVelocityVectorMarker; // 0x69
		bool m_UseLockingController; // 0x6a
		bool m_UseThrust; // 0x6b
		bool m_UseGForce; // 0x6c
		bool m_UseSkidSlip; // 0x6d
		bool m_UseClimbRate; // 0x6e
		unsigned char _0x6f[0x1];
	}; // size = 0x70

	class TargetCameraData
	{
		char pad[96];
	public:
		
		HudData m_Hud; // 0x60
	}; // size = 0xd0

	class StaticCameraData
	{
		char aTargetCameraData[208];
	public:
		TargetCameraData* m_LeftCurve; // 0xd0
		TargetCameraData* m_RightCurve; // 0xd8
		TargetCameraData* m_UpCurve; // 0xe0
		TargetCameraData* m_DownCurve; // 0xe8
		bool m_LoosePartPhysics; // 0xf0
		float m_LeftYawAngle; // 0xf8
		float m_RightYawAngle; // 0xfc
		float m_UpPitchAngle; // 0x100
		float m_DownPitchAngle; // 0x104
		int m_AverageFilterFrames; // 0x108
		int m_YawInputAction; // 0x10c
		int m_PitchInputAction; // 0x110
		float m_WorldSpaceLockEfficiencyYaw; // 0x114
		float m_WorldSpaceLockEfficiencyYawAway; // 0x118
		float m_WorldSpaceLockEfficiencyPitch; // 0x11c
		float m_YawSensitivityNonZoomed; // 0x120
		float m_YawSensitivityZoomed; // 0x124
		float m_PitchSensitivityNonZoomed; // 0x128
		float m_PitchSensitivityZoomed; // 0x12c
		bool m_MergeLeftAndRightCurves; // 0x130
		bool m_MergeUpAndDownCurves; // 0x131
		bool m_MirrorHorizontalCurves; // 0x132
		bool m_MirrorVerticalCurves; // 0x133
		bool m_AccumulateInput; // 0x134
		bool m_ResetAccumulatedInputOnViewChange; // 0x135
		unsigned char _0x136[0xa];
	}; // size = 0x140


	virtual TypeInfo* GetType(); 

	char _0x0008[240];
	StaticCameraData* m_pStaticCameraData; //0x00F8 
	char _0x0100[24];
	void*/*ViewFxData**/ m_pViewFxData; //0x0118 
	char _0x0120[8];
	float m_Xoffset; //0x0128 
	char _0x012C[12];
	float m_Yoffset; //0x0138 

	static StaticCamera* GetInstance()
	{
		return reinterpret_cast<StaticCamera*>(
			*reinterpret_cast<__int64*>(
				(*reinterpret_cast<__int64*>(
					(*reinterpret_cast<__int64*>(OFFSET_ANGLES + 0x30)) + 0x2F8)) + 0x20));
	}

	Vector2D GetOverlayCrosshair()
	{
		return Vector2D();
	}

	/*
	CrossHair.y=m_Yoffset*-(0.0565*(screen.w-screen.h))/fov*1000
	CrossHair.z=m_Xoffset*(0.0565*(screen.w-screen.h))/fov*1000
	VehicleCrossHairAddreess =14212c190
	*/
};//Size=0x013C

class DeployScreenClass
{
	char _0x000[0x260];

public:
	bool m_canSpawn;
	static DeployScreenClass* GetInstance()
	{
		return reinterpret_cast<DeployScreenClass*>(*reinterpret_cast<__int64*>((*reinterpret_cast<__int64*>((*reinterpret_cast<__int64*>(0x142812040)) + 0x030)) + 0x728));
	}
};




class ViewAnglesClass
{
public:
	static ViewAnglesClass* GetInstance()
	{
		return (ViewAnglesClass*)OFFSET_ANGLES;
	}
	
	char pad_0000[48]; //0x0000
	D3DXMATRIX m_VehicleMatrix; //0x0030
	D3DXMATRIX m_SoldierMatrix; //0x0070
	float m_VehicleYawFixed; //0x00B0
	Vector2D m_Angles; //0x00B4
	float m_ZeroFloat; //0x00BC Always == zero
	bool m_SomeBool; //0x00C0 Always == true
}; //Size: 0x00C1

class ClientWarningSystemComponent// : public ClientGameComponent // size = 0x38
{
public:
	static void* GetTypeInfo()
	{
		return (void*)0x0000000142C2A630;
	}
	unsigned char _0x38[0x1f0];
}; // size = 0x228

class PredictionData_s
{
public:
	Vector hitPos;
	Vector origin;
	float travelTime;
	float distance;
	float bulletDrop;
	float bulletVel;
};

struct AABB
{
	Vector min;
	Vector max;
	Vector origin;
};