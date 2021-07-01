
#ifndef HMDINTERFACE_H_INCLUDED
#define HMDINTERFACE_H_INCLUDED

#include "Direct3DDevice9ExProxyImpl.h"

#include "stCommon.h"

//Generic HMD interface in case we do want to add other APIs other than SteamVR
class HMDInterface
{
public:
	static HMDInterface* Get(IDirect3DDevice9Ex *pDevice);

	virtual ~HMDInterface() {}

	virtual bool Init(IDirect3DDevice9Ex* pDevice) = 0;

	//Rendering Stuff
	virtual void Submit() = 0;
	virtual void GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight) = 0;
	virtual float GetEyeDistance() = 0;
	virtual void GetEyeView(int eye, float matrix[4][4], bool invert) = 0;
	virtual bool IsConnected() = 0;
	virtual void StartFrame() = 0;
	virtual void StoreSharedTexture(int index, IDirect3DTexture9* pIDirect3DTexture9, HANDLE* pShared) = 0;
	virtual void GetProjection(int eye, float matrix[4][4], bool invert) = 0;
	virtual int GetCurrentRenderTexture() = 0;
	virtual int GetTotalStoredTextures() = 0;

	//Tracjing Stuff
	virtual void GetTrackingDataHMD(float hMatrix[4][4]) = 0;
	virtual void GetTrackingDataLeftController(float lcMatrix[4][4]) = 0;
	virtual void GetTrackingDataRightController(float rcMatrix[4][4]) = 0;

	//Button Stuff
	virtual bool  GetButtonHasChanged(ButtonList buttonID, ControllerType controllerType) = 0;
	virtual bool  GetButtonIsTouched(ButtonList buttonID, ControllerType controllerType) = 0;
	virtual bool  GetButtonIsPressed(ButtonList buttonID, ControllerType controllerType) = 0;
	virtual bool  GetButtonIsDownFrame(ButtonList buttonID, ControllerType controllerType) = 0;
	virtual bool  GetButtonIsUpFrame(ButtonList buttonID, ControllerType controllerType) = 0;
	virtual float GetButtonValue(ButtonList buttonID, ControllerType controllerType) = 0;

};

#endif