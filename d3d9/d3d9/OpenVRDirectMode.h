#ifndef OPENVRDIRECTMODE_H_INCLUDED
#define OPENVRDIRECTMODE_H_INCLUDED

#pragma warning (disable : 4005)

#include <d3d11.h>

#include "HMDInterface.h"
#include "OpenVRHelpers\openvr.h"

#include "stCommon.h"


struct ID3D11Device;
struct IDirect3DDevice9Ex;

struct SharedTextureHolder {
	SharedTextureHolder() :
		m_d3d11Texture(NULL) {}

	void Release() {
		if (m_d3d11Texture != NULL)
		{
			m_d3d11Texture->Release();
			m_d3d11Texture = NULL;
		}
	}

	vr::VRVulkanTextureData_t m_VulkanData;
	ID3D11Texture2D*        m_d3d11Texture;
	vr::Texture_t			m_VRTexture;
};

struct ButtonState {
	bool m_touched;
	float m_value;
};

/**
* OpenVR Direct Mode render class.
*/
class OpenVRDirectMode : public HMDInterface
{
public:
	OpenVRDirectMode();
	virtual ~OpenVRDirectMode();

	virtual bool Init(IDirect3DDevice9Ex* pDevice);	

	virtual std::string  GetAPI();

	//Rendering Stuff
	virtual void Submit();
	virtual void GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight);
	virtual float GetEyeDistance();
	virtual void GetEyeView(int eye, float matrix[4][4], bool invert);
	virtual bool IsConnected();
	virtual void StartFrame();
	virtual void StoreSharedTexture(int index, IDirect3DTexture9* pIDirect3DTexture9, HANDLE* pShared);
	virtual void GetProjection(int eye, float matrix[4][4], bool invert);
	virtual int GetCurrentRenderTexture();
	virtual int GetTotalStoredTextures();

	//Tracjing Stuff
	virtual void GetTrackingDataHMD(float hMatrix[4][4]);
	virtual void GetTrackingDataLeftController(float lcMatrix[4][4]);
	virtual void GetTrackingDataRightController(float rcMatrix[4][4]);

	//Button Stuff
	virtual bool  GetButtonHasChanged(ButtonList buttonID, ControllerType controllerType);
	virtual bool  GetButtonIsTouched(ButtonList buttonID, ControllerType controllerType);
	virtual bool  GetButtonIsPressed(ButtonList buttonID, ControllerType controllerType);
	virtual bool  GetButtonIsDownFrame(ButtonList buttonID, ControllerType controllerType);
	virtual bool  GetButtonIsUpFrame(ButtonList buttonID, ControllerType controllerType);
	virtual float GetButtonValue(ButtonList buttonID, ControllerType controllerType);

private:
	void SetClickButtonState(vr::VRControllerState_t &state, ButtonList button, vr::EVRButtonId vrButtonId);
	void SetXAxisState(vr::VRControllerState_t &state, ButtonList button, vr::EVRButtonId vrButtonId);
	void SetYAxisState(vr::VRControllerState_t &state, ButtonList button, vr::EVRButtonId vrButtonId);

private:
	IDirect3DDevice9Ex*		m_pActualDevice;
	ID3D11Device*			m_pID3D11Device;

	SharedTextureHolder			m_SharedTextureHolder[5];

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	vr::IVRSystem *m_pHMD;
	vr::IVRRenderModels *m_pRenderModels;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	
	char m_rDevClassChar[vr::k_unMaxTrackedDeviceCount];

private:
	bool m_initialised;
	int m_nextStoredexture;
	int m_currentRenderTexture;
	bool m_hasHMDAttached;
	bool m_useControllerState;
	bool m_submitFrameBuffersToCompositor;
	std::string m_api;

	ButtonState m_buttonStates[ButtonsList::right_GestureFist + 1];
	ButtonState m_previousButtonStates[ButtonsList::right_GestureFist + 1];
};

#endif //OPENVRDIRECTMODE_H_INCLUDED