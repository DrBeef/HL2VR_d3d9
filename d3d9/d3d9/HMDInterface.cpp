#include "HMDInterface.h"

#include "OpenVRDirectMode.h"

#include "hmdWrapper.h"

HMDInterface *g_pHMDInterface = NULL;
IDirect3DDevice9Ex *g_pDevice = NULL;


HMDInterface* HMDInterface::Get(IDirect3DDevice9Ex *pDevice)
{
	g_pHMDInterface = new OpenVRDirectMode();
	g_pDevice = pDevice;

	return g_pHMDInterface;
}

void notimplemented(char *function)
{
	char buffer[256];
	sprintf_s(buffer, "Function: %s   is currently not implemented!!\n", function);
	OutputDebugString(buffer);
}

void DllExport hmdExtendDX9Buffer(int width, int height)
{
	notimplemented(__FUNCTION__);
}

// Changes the next draw call information to modify viewport and projection matrix
void DllExport SetDrawState(int renderStatus, int sOffProj, int sOffView)
{
	notimplemented(__FUNCTION__);
}

// Called to set the next image as part of the headset swapchain
void DllExport hmdSetNextTextureType(hmdTextureType textureType, hmdTextureType index)
{
	notimplemented(__FUNCTION__);
}

IDirect3DSurface9 DllExport *hmdGetSharedSurface()
{
	return NULL;
}

// Called at the start of the frame to setup head / controller tracking values for the frame
void  DllExport hmdSetFrame()
{
	g_pHMDInterface->StartFrame();
}

// Called at the end of the frame to tell the headset to render the frame
void  DllExport hmdEndFrame()
{
	notimplemented(__FUNCTION__);
}

// Sets the directx9 device (doing this within the dll causes issues when the dll is loaded multiple times)
void  DllExport hmdSetDevice(IDirect3DDevice9* D3D9Device)
{
	notimplemented(__FUNCTION__);
}

// Sets the sdk type : openvr, oculus etc
void  DllExport hmdSetSDK(sdkType sdkID)
{
	notimplemented(__FUNCTION__);
}

void  DllExport hmdSetSDK(int sdkID)
{
	notimplemented(__FUNCTION__);
}


// Lets the sdk know if the user is standing or sitting
void  DllExport hmdSetIsSitting(bool isSitting)
{
	notimplemented(__FUNCTION__);
}

// Opens the headset connection. 
bool  DllExport hmdOpen()
{
	return g_pHMDInterface->Init(g_pDevice);
}

// Returns true if a headset connection is open
bool  DllExport hmdIsConnected()
{
	return g_pHMDInterface->IsConnected();
}

// Closes the open headset connection
void  DllExport hmdClose()
{
	notimplemented(__FUNCTION__);
}

// Gets the hmd projection matrix for a paticular eye : 0 = left, 1 = right
void  DllExport hmdGetProjection(int eye, float matrix[4][4], bool invert)
{
	g_pHMDInterface->GetProjection(eye, matrix, invert);
}

float DllExport *hmdGetProjection(int eye, bool invert)
{
	static float matrix[4][4];

	g_pHMDInterface->GetProjection(eye, matrix, invert);

	return (float*)matrix;
}

// Gets the hmd eye to hmd matrix for a paticular eye : 0 = left, 1 = right
void  DllExport hmdGetEyeView(int eye, float matrix[4][4], bool invert)
{
	g_pHMDInterface->GetEyeView(eye, matrix, invert);
}

float DllExport *hmdGetEyeView(int eye, bool invert)
{
	static float matrix[4][4];

	g_pHMDInterface->GetEyeView(eye, matrix, invert);

	return (float*)matrix;
}

// Gets the hmd resolution / prefered buffer size / IPD
POINT DllExport hmdGetResolution()
{
	POINT p;
	
	uint32_t x, y;
	g_pHMDInterface->GetRecommendedRenderTargetSize(&x, &y);
	p.x = x;
	p.y = y;
	return p;
}

POINT DllExport hmdGetBufferSize()
{
	POINT p;

	uint32_t x, y;
	g_pHMDInterface->GetRecommendedRenderTargetSize(&x, &y);
	p.x = x * 2;
	p.y = y;
	return p;
}

float DllExport hmdGetIPD()
{
	return g_pHMDInterface->GetEyeDistance();
}

// Returns the tracking data for the headset and controllers
void  DllExport hmdGetTrackingData(float hMatrix[4][4], float lcMatrix[4][4], float rcMatrix[4][4])
{
	g_pHMDInterface->GetTrackingDataHMD(hMatrix);
	g_pHMDInterface->GetTrackingDataLeftController(lcMatrix);
	g_pHMDInterface->GetTrackingDataRightController(rcMatrix);
}

float DllExport *hmdGetTrackingHMD()
{
	static float matrix[4][4];
	g_pHMDInterface->GetTrackingDataHMD(matrix);
	return (float*)matrix;
}

float DllExport *hmdGetTrackingLeftController()
{
	static float matrix[4][4];
	g_pHMDInterface->GetTrackingDataLeftController(matrix);
	return (float*)matrix;
}

float DllExport *hmdGetTrackingRightController()
{
	static float matrix[4][4];
	g_pHMDInterface->GetTrackingDataRightController(matrix);
	return (float*)matrix;
}

// Resets the saved controller button information (is down frame, is up frame)
void  DllExport hmdResetTracking()
{
	notimplemented(__FUNCTION__);
}

// Gets the button information
bool  DllExport hmdGetButtonHasChanged(ButtonList buttonID, ControllerType controllerType)
{
	return g_pHMDInterface->GetButtonHasChanged(buttonID, controllerType);
}

bool  DllExport hmdGetButtonIsTouched(ButtonList buttonID, ControllerType controllerType)
{
	return g_pHMDInterface->GetButtonIsTouched(buttonID, controllerType);
}

bool  DllExport hmdGetButtonIsPressed(ButtonList buttonID, ControllerType controllerType)
{
	return g_pHMDInterface->GetButtonIsPressed(buttonID, controllerType);
}

bool  DllExport hmdGetButtonIsDownFrame(ButtonList buttonID, ControllerType controllerType)
{
	return g_pHMDInterface->GetButtonIsDownFrame(buttonID, controllerType);
}

bool  DllExport hmdGetButtonIsUpFrame(ButtonList buttonID, ControllerType controllerType)
{
	return g_pHMDInterface->GetButtonIsUpFrame(buttonID, controllerType);
}


float DllExport hmdGetButtonValue(ButtonList buttonID, ControllerType controllerType)
{
	return g_pHMDInterface->GetButtonValue(buttonID, controllerType);
}


// Recenters the headset
void  DllExport hmdRecenter()
{
	notimplemented(__FUNCTION__);
}



// Sets a prediction value for the headset
void  DllExport hmdSetPrediction(float prediction)
{
	notimplemented(__FUNCTION__);
}

// Gets the number of textures used in the swap chain
int   DllExport hmdGetFrameCount()
{
	return g_pHMDInterface->GetTotalStoredTextures();
}



// Gets the current swap chain index
int   DllExport hmdGetCurrentTextureIndex()
{
	return g_pHMDInterface->GetCurrentRenderTexture();
}


// Starts / stops the controller vibration : controllerID 0 = left, 1 = right, vibratePercent = 0 -> 100
void  DllExport hmdControllerVibrateStart(int controllerID, int vibratePercent)
{
	notimplemented(__FUNCTION__);
}


void  DllExport hmdControllerVibrateStop(int controllerID)
{
	notimplemented(__FUNCTION__);
}



// Sets the texture or surface that is being render too either for both eyes at once, or seporate
void DllExport hmdSetTexture(IDirect3DTexture9 *bothEyes, bool manualSet)
{
	notimplemented(__FUNCTION__);
}


void DllExport hmdSetTexture(HANDLE textureID, IDirect3DTexture9 *bothEyes, bool manualSet)
{
	notimplemented(__FUNCTION__);
}


void DllExport hmdSetSurface(IDirect3DSurface9 *bothEyes, bool manualSet)
{
	notimplemented(__FUNCTION__);
}


void DllExport hmdSetTexture(IDirect3DTexture9 *leftEye, IDirect3DTexture9 *rightEye, bool manualSet)
{
	notimplemented(__FUNCTION__);
}


// Saves the render surface to a texture, if rect is null or not included then it captures the whole surface
void DllExport hmdCaptureScreen(char *fileName)
{
	notimplemented(__FUNCTION__);
}


void DllExport hmdCaptureScreen(char *fileName, RECT *rect)
{
	notimplemented(__FUNCTION__);
}


void DllExport hmdCaptureScreen(char *fileName, int left, int top, int right, int bottom)
{
	notimplemented(__FUNCTION__);
}


void DllExport hmdCaptureScreen(const char fileName[], int left, int top, int right, int bottom)
{
	notimplemented(__FUNCTION__);
}



