#ifndef DIRECT3D9EXWRAPPER_H_INCLUDED
#define DIRECT3D9EXWRAPPER_H_INCLUDED

#include "Main.h"

class __declspec(dllexport) Direct3D9ExWrapper : public IDirect3D9Ex
{
public:
	Direct3D9ExWrapper(IDirect3D9Ex* pD3DEx);
	virtual ~Direct3D9ExWrapper();

	// IUnknown methods 
	virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG   WINAPI AddRef();
	virtual ULONG   WINAPI Release();

	// IDirect3D9Ex methods
	virtual HRESULT	 WINAPI RegisterSoftwareDevice(void* pInitializeFunction);
	virtual UINT     WINAPI GetAdapterCount();
	virtual HRESULT	 WINAPI GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier);
	virtual UINT     WINAPI GetAdapterModeCount(UINT Adapter, D3DFORMAT Format);    
	virtual HRESULT	 WINAPI GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode);
	virtual HRESULT	 WINAPI CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
	virtual HRESULT	 WINAPI CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);    
	virtual HRESULT	 WINAPI CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels);
	virtual HRESULT	 WINAPI CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
	virtual HRESULT	 WINAPI CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType,	D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
	virtual HRESULT	 WINAPI GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps);
	virtual HMONITOR WINAPI GetAdapterMonitor(UINT Adapter);
	virtual HRESULT	 WINAPI CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow,	DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface);
	virtual UINT     WINAPI GetAdapterModeCountEx(UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter );
	virtual HRESULT	 WINAPI EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode);
	virtual HRESULT  WINAPI EnumAdapterModesEx(UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter,UINT Mode,D3DDISPLAYMODEEX* pMode);
	virtual HRESULT  WINAPI GetAdapterDisplayModeEx(UINT Adapter,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation);
	virtual HRESULT  WINAPI CreateDeviceEx(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface);
	virtual HRESULT  WINAPI GetAdapterLUID(UINT Adapter,LUID * pLUID);

private:
	IDirect3D9Ex* m_pD3DEx;
	ULONG m_refCount;
};

#endif