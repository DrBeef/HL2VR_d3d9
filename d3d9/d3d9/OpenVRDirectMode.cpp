

#include "OpenVRDirectMode.h"
#include "HMDInterface.h"
#include "Direct3DDevice9ExProxyImpl.h"
#include <DirectXMath.h>


#include "GlShaders.h"
#include "glad/glad.h"
#include "glad/glad_wgl.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment (lib, "OpenVRHelpers\\openvr_api.lib")
#pragma warning (disable : 4305)

#define BUTTON_DEADZONE  0.05f;

void Matrix_SetIdentity(float matrix[4][4])
{
	memset(matrix, 0, 16 * sizeof(float));
	matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1.0f;
}

inline void Swap(float& a, float& b)
{
	float tmp = a;
	a = b;
	b = tmp;
}

void MatrixTranspose(float src[4][4], float dst[4][4])
{
	if (src == dst)
	{
		Swap(dst[0][1], dst[1][0]);
		Swap(dst[0][2], dst[2][0]);
		Swap(dst[0][3], dst[3][0]);
		Swap(dst[1][2], dst[2][1]);
		Swap(dst[1][3], dst[3][1]);
		Swap(dst[2][3], dst[3][2]);
	}
	else
	{
		dst[0][0] = src[0][0]; dst[0][1] = src[1][0]; dst[0][2] = src[2][0]; dst[0][3] = src[3][0];
		dst[1][0] = src[0][1]; dst[1][1] = src[1][1]; dst[1][2] = src[2][1]; dst[1][3] = src[3][1];
		dst[2][0] = src[0][2]; dst[2][1] = src[1][2]; dst[2][2] = src[2][2]; dst[2][3] = src[3][2];
		dst[3][0] = src[0][3]; dst[3][1] = src[1][3]; dst[3][2] = src[2][3]; dst[3][3] = src[3][3];
	}
}

/**
* Constructor.
***/ 
OpenVRDirectMode::OpenVRDirectMode() : 
	m_glDC(nullptr),
	m_glContext(nullptr),
	m_glDXDevice(nullptr),
	m_pHMD(NULL),
	m_initialised(false),
	m_nextStoredTexture(0),
	m_currentRenderTexture(0),
	m_lastSubmittedTexture(-1),
	m_hasHMDAttached(false)
{
	DEBUG_LOG("OpenVRDirectMode::OpenVRDirectMode()");

	memset(m_SharedTextureHolder, 0, sizeof(m_SharedTextureHolder));
	memset(m_buttonStates, 0, sizeof(m_buttonStates));
	memset(m_previousButtonStates, 0, sizeof(m_previousButtonStates));
}

OpenVRDirectMode::~OpenVRDirectMode()
{
	DEBUG_LOG("OpenVRDirectMode::~OpenVRDirectMode()");
	if (m_initialised && m_glContext) {
		wglDXCloseDeviceNV(m_glDXDevice);
		wglDeleteContext(m_glContext);
	}
}


bool OpenVRDirectMode::Init(IDirect3DDevice9Ex* pActualDevice)
{
	DEBUG_LOG("OpenVRDirectMode::Init");

	m_pActualDevice = pActualDevice;

	// Loading the SteamVR Runtime
	vr::EVRInitError eError = vr::VRInitError_None;
	vr::IVRSystem *pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None)
	{
		if (eError == vr::VRInitError_Init_HmdNotFound)
		{
			
			m_initialised = true;
			m_nRenderWidth = m_nRenderHeight = 2016;
			return true;
		}

		OutputDebugString("[FAIL] Could not initialise OpenVR\n");
		return false;
	}

	m_pHMD = vr::OpenVRInternal_ModuleContext().VRSystem();

	if (eError != vr::VRInitError_None)
	{
		return false;
	}

	m_hasHMDAttached = true;

	m_pHMD->GetRecommendedRenderTargetSize(&m_nRenderWidth, &m_nRenderHeight);

	if (!vr::VRCompositor())
	{
		OutputDebugString("ERROR: No VRCompositor\n");
		return false;
	}

	{
		D3DDEVICE_CREATION_PARAMETERS params;
		m_pActualDevice->GetCreationParameters(&params);
		m_glDC = GetDC(params.hFocusWindow);
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_SUPPORT_OPENGL|PFD_DRAW_TO_WINDOW|PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0, 0,
			0, 0, 0, 0, 0,
			24, 8, 0,
			PFD_MAIN_PLANE,
			0, 0, 0, 0
		};
		int pixelFormat = ChoosePixelFormat(m_glDC, &pfd);
		SetPixelFormat(m_glDC, pixelFormat, &pfd);
		HGLRC m_glContext = wglCreateContext(m_glDC);
		if (!m_glContext) {
			OutputDebugString("ERROR: Could not create GL context\n");
			return false;
		}

		wglMakeCurrent(m_glDC, m_glContext);
		if (!gladLoadWGL(m_glDC)) {
			OutputDebugString("ERROR: Could not initialize GLAD\n");
			return false;
		}
		wglDeleteContext(m_glContext);
		int attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		m_glContext = wglCreateContextAttribsARB(m_glDC, NULL, attribs);
		if (!m_glContext) {
			OutputDebugString("ERROR: Could not create GL context\n");
			return false;
		}
		wglMakeCurrent(m_glDC, m_glContext);
		if (!gladLoadWGL(m_glDC) || !gladLoadGL()) {
			OutputDebugString("ERROR: Could not initialize GLAD\n");
			return false;
		}

		m_glDXDevice = wglDXOpenDeviceNV(m_pActualDevice);
		if (!m_glDXDevice) {
			OutputDebugString("ERROR: Could not open DX device for GL sharing\n");
			return false;
		}

		// prepare the shaders
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &g_VertexSource, nullptr);
		glCompileShader(vertex);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &g_FragmentSource, nullptr);
		glCompileShader(fragment);
		int success;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			OutputDebugString("ERROR: Could not compile GL fragment shader\n");
			return false;
		}
		m_glProgram = glCreateProgram();
		glAttachShader(m_glProgram, vertex);
		glAttachShader(m_glProgram, fragment);
		glLinkProgram(m_glProgram);
		glGetProgramiv(m_glProgram, GL_LINK_STATUS, &success);
		if (!success) {
			OutputDebugString("ERROR: Could not link GL shader\n");
			return false;
		}
		int uniform = glGetUniformLocation(m_glProgram, "sourceTex");
		glUniform1i(uniform, 0);
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		// bind a dummy VAO, otherwise rendering commands will fail
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// common setup
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glActiveTexture(GL_TEXTURE0);
		glUseProgram(m_glProgram);
	}

	m_initialised = true;

	return true;
}

void OpenVRDirectMode::PrePresent()
{
	if (!m_initialised)
	{
		return;
	}
}


void OpenVRDirectMode::Submit()
{
	if (!m_initialised)
	{
		return;
	}

	static vr::VRTextureBounds_t leftBounds = { 0.0f, 0.0f, 0.5f, 1.0f };
	static vr::VRTextureBounds_t rightBounds = { 0.5f, 0.0f, 1.0f, 1.0f };

	{
		if (m_SharedTextureHolder[m_currentRenderTexture].m_glSharedHandle)
		{
			wglDXLockObjectsNV(m_glDXDevice, 1, &m_SharedTextureHolder[m_currentRenderTexture].m_glSharedHandle);

			glBindFramebuffer(GL_FRAMEBUFFER, m_SharedTextureHolder[m_currentRenderTexture].m_glFBO);
			GLuint width = m_SharedTextureHolder[m_currentRenderTexture].m_Width;
			GLuint height = m_SharedTextureHolder[m_currentRenderTexture].m_Height;
			glViewport(0, 0, width, height);
			glBindTexture(GL_TEXTURE_2D, m_SharedTextureHolder[m_currentRenderTexture].m_glTexture[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			
			wglDXUnlockObjectsNV(m_glDXDevice, 1, &m_SharedTextureHolder[m_currentRenderTexture].m_glSharedHandle);
		}
	}


	if (m_hasHMDAttached && 
		GetBoolProperty("submitFrameBuffersToCompositor", true) &&
		(
			m_lastSubmittedTexture != m_currentRenderTexture ||
			GetTotalStoredTextures() == 1
			))
	{
		if (vr::VRCompositor())
		{
			vr::EVRCompositorError error = vr::VRCompositor()->Submit(vr::Eye_Left, &(m_SharedTextureHolder[m_currentRenderTexture].m_VRTexture), &leftBounds);
			if (error != vr::VRCompositorError_None)
			{
				OutputDebugString("Error - Could not submit compositor left eye texture\n");
			}

			error = vr::VRCompositor()->Submit(vr::Eye_Right, &(m_SharedTextureHolder[m_currentRenderTexture].m_VRTexture), &rightBounds);
			if (error != vr::VRCompositorError_None)
			{
				OutputDebugString("Error - Could not submit compositor right eye texture\n");
			}

			vr::VRCompositor()->PostPresentHandoff();
		}

		m_lastSubmittedTexture = m_currentRenderTexture;
	}

	//Move to the next texture
	if (++m_currentRenderTexture > m_nextStoredTexture)
	{
		m_currentRenderTexture = 0;
	}
}

float OpenVRDirectMode::GetEyeDistance()
{
	if (!m_initialised || !m_hasHMDAttached)
	{
		return 0.0f;
	}

	vr::HmdMatrix34_t rightEye = m_pHMD->GetEyeToHeadTransform(vr::Eye_Right);
	return rightEye.m[0][3];
}

void OpenVRDirectMode::GetEyeView(int eye, float matrix[4][4], bool invert)
{
	if (!m_initialised || !m_hasHMDAttached)
	{
		Matrix_SetIdentity(matrix);
		return;
	}

	vr::HmdMatrix34_t eyeView = m_pHMD->GetEyeToHeadTransform((vr::EVREye)eye);
	memcpy(matrix, eyeView.m, 16 * sizeof(float));
}

void OpenVRDirectMode::GetProjection(int eye, float matrix[4][4], bool invert)
{
	if (!m_initialised || !m_hasHMDAttached)
	{
		static float projection[16] = {
		0.64759356,			0.0,			-0.12823947,	0.0,
		0.0,				0.78749996,		0.0,			0.0,
		0.0,				0.0,			-1.0001,		-0.10001001,
		0.0,				0.0,			-1.0,			0.0 };
		memcpy(matrix, projection, 16 * sizeof(float));

		return;
	}

	vr::HmdMatrix44_t mat = m_pHMD->GetProjectionMatrix((vr::EVREye)eye, 0.1f, 300.0f);
	memcpy(matrix, mat.m, 16 * sizeof(float));
}

void OpenVRDirectMode::GetTrackingDataHMD(float hMatrix[4][4])
{
	if (m_hasHMDAttached && m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		Matrix_SetIdentity(hMatrix);
		memcpy(hMatrix, m_rTrackedDevicePose[0].mDeviceToAbsoluteTracking.m, 12 * sizeof(float));
		MatrixTranspose(hMatrix, hMatrix);
	}
}

void OpenVRDirectMode::GetTrackingDataLeftController(float lcMatrix[4][4])
{
	if (!m_hasHMDAttached)
	{
		return;
	}

	vr::TrackedDeviceIndex_t leftIndex = m_pHMD->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_LeftHand);

	if (m_rTrackedDevicePose[leftIndex].bPoseIsValid)
	{
		Matrix_SetIdentity(lcMatrix);
		memcpy(lcMatrix, m_rTrackedDevicePose[leftIndex].mDeviceToAbsoluteTracking.m, 12 * sizeof(float));
		MatrixTranspose(lcMatrix, lcMatrix);
	}
}

void OpenVRDirectMode::GetTrackingDataRightController(float rcMatrix[4][4])
{
	if (!m_hasHMDAttached)
	{
		return;
	}
	vr::TrackedDeviceIndex_t rightIndex = m_pHMD->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_RightHand);

	if (m_rTrackedDevicePose[rightIndex].bPoseIsValid)
	{
		Matrix_SetIdentity(rcMatrix);
		memcpy(rcMatrix, m_rTrackedDevicePose[rightIndex].mDeviceToAbsoluteTracking.m, 12 * sizeof(float));
		MatrixTranspose(rcMatrix, rcMatrix);
	}
}

void OpenVRDirectMode::GetRecommendedRenderTargetSize(uint32_t *pnWidth, uint32_t *pnHeight)
{
	*pnWidth = m_nRenderWidth;
	*pnHeight = m_nRenderHeight;
}

bool OpenVRDirectMode::IsConnected()
{
	if (!m_hasHMDAttached)
	{
		return m_initialised;
	}

	return m_pHMD != NULL && m_pHMD->IsTrackedDeviceConnected(vr::k_unTrackedDeviceIndex_Hmd);
}

void OpenVRDirectMode::SetClickButtonState(vr::VRControllerState_t &state, ButtonList button, vr::EVRButtonId vrButtonId)
{
	m_buttonStates[button].m_touched = (state.ulButtonTouched & vr::ButtonMaskFromId(vrButtonId)) == vr::ButtonMaskFromId(vrButtonId);
	m_buttonStates[button].m_value = (state.ulButtonPressed & vr::ButtonMaskFromId(vrButtonId)) ? 1.0f : 0.0f;
}

void OpenVRDirectMode::SetXAxisState(vr::VRControllerState_t &state, ButtonList button, vr::EVRButtonId vrButtonId)
{
	m_buttonStates[button].m_touched = (state.ulButtonTouched & vr::ButtonMaskFromId(vrButtonId)) == vr::ButtonMaskFromId(vrButtonId);
	m_buttonStates[button].m_value = state.rAxis[vrButtonId -vr::k_EButton_Axis0].x;
}

void OpenVRDirectMode::SetYAxisState(vr::VRControllerState_t &state, ButtonList button, vr::EVRButtonId vrButtonId)
{
	m_buttonStates[button].m_value = state.rAxis[vrButtonId - vr::k_EButton_Axis0].y;
}

bool  OpenVRDirectMode::GetButtonHasChanged(ButtonList buttonID, ControllerType controllerType)
{
	return m_buttonStates[buttonID].m_value != m_previousButtonStates[buttonID].m_value;
}

bool  OpenVRDirectMode::GetButtonIsTouched(ButtonList buttonID, ControllerType controllerType)
{
	return m_buttonStates[buttonID].m_touched;
}

bool  OpenVRDirectMode::GetButtonIsPressed(ButtonList buttonID, ControllerType controllerType)
{
	return fabs(m_buttonStates[buttonID].m_value) > BUTTON_DEADZONE;
}

bool  OpenVRDirectMode::GetButtonIsDownFrame(ButtonList buttonID, ControllerType controllerType)
{
	//What does this mean?!
	return false;
}

bool  OpenVRDirectMode::GetButtonIsUpFrame(ButtonList buttonID, ControllerType controllerType)
{
	//What does this mean?!
	return false;
}

float OpenVRDirectMode::GetButtonValue(ButtonList buttonID, ControllerType controllerType)
{
	return m_buttonStates[buttonID].m_value;
}


void OpenVRDirectMode::StartFrame()
{
	if (!m_initialised || !m_hasHMDAttached || !vr::VRCompositor())
	{
		return;
	}

	vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	//Store previous frame's controller state
	memcpy(m_previousButtonStates, m_buttonStates, sizeof(m_buttonStates));

	{
		vr::TrackedDeviceIndex_t leftIndex = m_pHMD->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_LeftHand);
		vr::VRControllerState_t state;
		if (m_pHMD->GetControllerState(leftIndex, &state, sizeof(state)))
		{
			SetClickButtonState(state, ButtonList::left_Menu, vr::k_EButton_System);
			SetClickButtonState(state, ButtonList::left_ButtonA, vr::k_EButton_A);
			SetClickButtonState(state, ButtonList::left_ButtonB, vr::k_EButton_ApplicationMenu); //B Button
			SetClickButtonState(state, ButtonList::left_Pad, vr::k_EButton_SteamVR_Touchpad);

			SetXAxisState(state, ButtonList::left_Bumper, vr::k_EButton_Axis2);
			SetXAxisState(state, ButtonList::left_Trigger, vr::k_EButton_SteamVR_Trigger);

			SetXAxisState(state, ButtonList::left_PadXAxis, vr::k_EButton_SteamVR_Touchpad);
			SetYAxisState(state, ButtonList::left_PadYAxis, vr::k_EButton_SteamVR_Touchpad); 
		}
	}

	{
		vr::TrackedDeviceIndex_t rightIndex = m_pHMD->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_RightHand);
		vr::VRControllerState_t state;
		if (m_pHMD->GetControllerState(rightIndex, &state, sizeof(state)))
		{
			SetClickButtonState(state, ButtonList::right_Menu, vr::k_EButton_System);
			SetClickButtonState(state, ButtonList::right_ButtonA, vr::k_EButton_A);
			SetClickButtonState(state, ButtonList::right_ButtonB, vr::k_EButton_ApplicationMenu); //B Button
			SetClickButtonState(state, ButtonList::right_Pad, vr::k_EButton_SteamVR_Touchpad);

			SetXAxisState(state, ButtonList::right_Bumper, vr::k_EButton_Axis2);
			SetXAxisState(state, ButtonList::right_Trigger, vr::k_EButton_SteamVR_Trigger);

			SetXAxisState(state, ButtonList::right_PadXAxis, vr::k_EButton_SteamVR_Touchpad);
			SetYAxisState(state, ButtonList::right_PadYAxis, vr::k_EButton_SteamVR_Touchpad);
		}
	}
}

void OpenVRDirectMode::StoreSharedTexture(int index, IDirect3DTexture9* pIDirect3DTexture9, HANDLE* pShared)
{
	if (*pShared == NULL)
	{
		return;
	}

	m_nextStoredTexture = index;

	//Ensure this is empty before proceeding
	m_SharedTextureHolder[m_nextStoredTexture].Release();

	if (m_hasHMDAttached)
	{
		SharedTextureHolder &th = m_SharedTextureHolder[m_nextStoredTexture];
		glGenTextures(2, th.m_glTexture);
		glGenFramebuffers(1, &th.m_glFBO);

		// get shared texture handle from DX texture
		wglDXSetResourceShareHandleNV(pIDirect3DTexture9, *pShared);
		th.m_glSharedHandle = wglDXRegisterObjectNV(m_glDXDevice, pIDirect3DTexture9, th.m_glTexture[0], GL_TEXTURE_2D, WGL_ACCESS_READ_WRITE_NV);

		// OpenVR can't directly use the format of the shared texture, so we need to make a copy to an additonal texture
		D3DSURFACE_DESC sd;
		pIDirect3DTexture9->GetLevelDesc(0, &sd);
		glBindTexture(GL_TEXTURE_2D, th.m_glTexture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, sd.Width, sd.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, th.m_glFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, th.m_glTexture[1], 0);
		GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, drawBuffers);
		int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			OutputDebugString("Target Framebuffer is not complete\n");
		}

		th.m_Width = sd.Width;
		th.m_Height = sd.Height;
		th.m_glDXDevice = m_glDXDevice;
		th.m_VRTexture.handle = (void*)th.m_glTexture[1];
		th.m_VRTexture.eColorSpace = vr::ColorSpace_Auto;
		th.m_VRTexture.eType = vr::TextureType_OpenGL;
		//DX9 Texture
		th.m_d3d9Texture = pIDirect3DTexture9;
		pIDirect3DTexture9->AddRef();
	}
}


int OpenVRDirectMode::GetCurrentRenderTexture()
{
	return m_currentRenderTexture;
}

int OpenVRDirectMode::GetTotalStoredTextures()
{
	return m_nextStoredTexture+1;
}


