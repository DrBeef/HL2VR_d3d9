#ifndef OPENVRDIRECTMODE_H_INCLUDED
#define OPENVRDIRECTMODE_H_INCLUDED

#pragma warning (disable : 4005)

#include <d3d11.h>

#include "HMDInterface.h"
#include "OpenVRHelpers\openvr.h"
#include "glad/glad.h"
#include "glad/glad_wgl.h"

#include "stCommon.h"


struct ID3D11Device;
struct IDirect3DDevice9Ex;

struct SharedTextureHolder {
	SharedTextureHolder() :
		m_d3d11Texture(NULL),
		m_d3d9Texture(NULL),
		m_glSharedHandle(NULL) {}

	void Release() {
		if (m_d3d11Texture != NULL)
		{
			m_d3d11Texture->Release();
			m_d3d11Texture = NULL;
			m_d3d9Texture->Release();
			m_d3d9Texture = NULL;
		}
		if (m_glSharedHandle != nullptr)
		{
			wglDXUnregisterObjectNV(m_glDXDevice, m_glSharedHandle);
			glDeleteTextures(2, m_glTexture);
			glDeleteFramebuffers(2, m_glFBO);
			m_glSharedHandle = nullptr;
		}
	}

	vr::VRVulkanTextureData_t m_VulkanData;
	ID3D11Texture2D*        m_d3d11Texture;
	IDirect3DTexture9*      m_d3d9Texture;
	vr::Texture_t			m_VRTexture;

	GLuint					m_glTexture[2];
	GLuint					m_glFBO[2];
	HANDLE					m_glSharedHandle;
	HANDLE					m_glDXDevice;
	GLuint					m_Width, m_Height;
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

	//Rendering Stuff
	virtual void PrePresent();
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
	HDC						m_glDC;
	HGLRC					m_glContext;
	HANDLE					m_glDXDevice;

	SharedTextureHolder			m_SharedTextureHolder[5];

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	vr::IVRSystem *m_pHMD;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	
private:
	bool m_initialised;
	int m_nextStoredTexture;
	int m_currentRenderTexture;
	int m_lastSubmittedTexture;
	bool m_hasHMDAttached;

	ButtonState m_buttonStates[ButtonsList::right_GestureFist + 1];
	ButtonState m_previousButtonStates[ButtonsList::right_GestureFist + 1];
};

#endif //OPENVRDIRECTMODE_H_INCLUDED