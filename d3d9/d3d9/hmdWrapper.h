#pragma once

#include "stCommon.h"
#include "d3d9.h"
#include <string>

#define DllExport __declspec(dllexport)
#define DllImport __declspec(dllimport)

// Function to extend the dx9 buffer by the given width or height
// If negative number is used, that value is set rather than added
void DllExport hmdExtendDX9Buffer(int width, int height);

// Changes the next draw call information to modify viewport and projection matrix
void DllExport SetDrawState(int renderStatus, int sOffProj, int sOffView);

// Called to set the next image as part of the headset swapchain
void DllExport hmdSetNextTextureType(hmdTextureType textureType, hmdTextureType index);

IDirect3DSurface9 DllExport *hmdGetSharedSurface();

// Called at the start of the frame to setup head / controller tracking values for the frame
void  DllExport hmdSetFrame();

// Called at the end of the frame to tell the headset to render the frame
void  DllExport hmdEndFrame();

// Sets the directx9 device (doing this within the dll causes issues when the dll is loaded multiple times)
void  DllExport hmdSetDevice(IDirect3DDevice9* D3D9Device);

// Sets the sdk type : openvr, oculus etc
void  DllExport hmdSetSDK(sdkType sdkID);
void  DllExport hmdSetSDK(int sdkID);

// Lets the sdk know if the user is standing or sitting
void  DllExport hmdSetIsSitting(bool isSitting);

// Opens the headset connection. useThreaded runs hmdBegin/EndFrame in a seporate thread so the main game is uncapped fps
bool  DllExport hmdOpen();

// Returns true if a headset connection is open
bool  DllExport hmdIsConnected();

// Closes the open headset connection
void  DllExport hmdClose();

// Gets the hmd projection matrix for a paticular eye : 0 = left, 1 = right
void  DllExport hmdGetProjection(int eye, float matrix[4][4], bool invert = false);
float DllExport *hmdGetProjection(int eye, bool invert = false);

// Gets the hmd eye to hmd matrix for a paticular eye : 0 = left, 1 = right
void  DllExport hmdGetEyeView(int eye, float matrix[4][4], bool invert = false);
float DllExport *hmdGetEyeView(int eye, bool invert = false);

// Gets the hmd resolution / prefered buffer size / IPD
POINT DllExport hmdGetResolution();
POINT DllExport hmdGetBufferSize();
float DllExport hmdGetIPD();

// Returns the tracking data for the headset and controllers
void  DllExport hmdGetTrackingData(float hMatrix[4][4], float lcMatrix[4][4], float rcMatrix[4][4]);
float DllExport *hmdGetTrackingHMD();
float DllExport *hmdGetTrackingLeftController();
float DllExport *hmdGetTrackingRightController();

// Resets the saved controller button information (is down frame, is up frame)
void  DllExport hmdResetTracking();

// Gets the button information
bool  DllExport hmdGetButtonHasChanged(ButtonList buttonID, ControllerType controllerType);
bool  DllExport hmdGetButtonIsTouched(ButtonList buttonID, ControllerType controllerType);
bool  DllExport hmdGetButtonIsPressed(ButtonList buttonID, ControllerType controllerType);
bool  DllExport hmdGetButtonIsDownFrame(ButtonList buttonID, ControllerType controllerType);
bool  DllExport hmdGetButtonIsUpFrame(ButtonList buttonID, ControllerType controllerType);
float DllExport hmdGetButtonValue(ButtonList buttonID, ControllerType controllerType);

// Recenters the headset
void  DllExport hmdRecenter();

// Sets a prediction value for the headset
void  DllExport hmdSetPrediction(float prediction);

// Gets the number of textures used in the swap chain
int   DllExport hmdGetFrameCount();

// Gets the current swap chain index
int   DllExport hmdGetCurrentTextureIndex();

// Starts / stops the controller vibration : controllerID 0 = left, 1 = right, vibratePercent = 0 -> 100
void  DllExport hmdControllerVibrateStart(int controllerID, int vibratePercent);
void  DllExport hmdControllerVibrateStop(int controllerID);

// Sets the texture or surface that is being render too either for both eyes at once, or seporate
void DllExport hmdSetTexture(IDirect3DTexture9 *bothEyes, bool manualSet = false);
void DllExport hmdSetTexture(HANDLE textureID, IDirect3DTexture9 *bothEyes, bool manualSet = false);
void DllExport hmdSetSurface(IDirect3DSurface9 *bothEyes, bool manualSet = false);
void DllExport hmdSetTexture(IDirect3DTexture9 *leftEye, IDirect3DTexture9 *rightEye, bool manualSet = false);
void DllExport hmdSetSurface(IDirect3DSurface9 *leftEye, IDirect3DSurface9 *rightEye, bool manualSet = false);

// Saves the render surface to a texture, if rect is null or not included then it captures the whole surface
void DllExport hmdCaptureScreen(char *fileName);
void DllExport hmdCaptureScreen(char *fileName, RECT *rect);
void DllExport hmdCaptureScreen(char *fileName, int left, int top, int right, int bottom);

void DllExport hmdCaptureScreen(const char fileName[], int left, int top, int right, int bottom);

//----
// Usage
//----
//---- start program
// hmdSetSDK(sdkID);
// hmdSetDevice(dxDevice);
// hmdOpen(); // hmdSetSDK & hmdSetDevice need to be called before hmdOpen
//
//----
//
// hmdSetIsSitting(isSitting);
// projMatL = hmdGetProjection(0);
// projMatR = hmdGetProjection(1);
//
// To use: add hmdTextureTypes::tBothEyes for type and the iIndex0 to frameCount
// hmdSetNextTextureType(hmdTextureTypes::tBothEyes, hmdTextureTypes::iIndex0)
// CreateTexture(Width, Height, .. , ..)
// 
//---- perFrame
//
// index = hmdGetCurrentTextureIndex();
// setRenderTarget(createdView[index]);
//
// hmdSetFrame();
// 
// - render and present here
// - backbuffer is copied to headset during present function
//
//
//----
// hmdClose();
//----
