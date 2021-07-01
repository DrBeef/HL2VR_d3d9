#include "Direct3D9ExWrapper.h"
#include "Direct3DDevice9ExWrapper.h"


Direct3D9ExWrapper::Direct3D9ExWrapper(IDirect3D9Ex* pD3DEx) :
	m_pD3DEx(pD3DEx),
	m_refCount(1)
{
}


Direct3D9ExWrapper::~Direct3D9ExWrapper()
{
	if(m_pD3DEx)
		m_pD3DEx->Release();
}


HRESULT WINAPI Direct3D9ExWrapper::QueryInterface(REFIID riid, LPVOID* ppv)
{
	return m_pD3DEx->QueryInterface(riid, ppv);
}


ULONG WINAPI Direct3D9ExWrapper::AddRef()
{
	return ++m_refCount;
}


ULONG WINAPI Direct3D9ExWrapper::Release()
{
	if(--m_refCount == 0)
	{
		delete this;
		return 0;
	}
	return m_refCount;
}


UINT Direct3D9ExWrapper::GetAdapterCount()
{
	return m_pD3DEx->GetAdapterCount();
}


HRESULT WINAPI Direct3D9ExWrapper::RegisterSoftwareDevice(void* pInitializeFunction)
{
	return m_pD3DEx->RegisterSoftwareDevice(pInitializeFunction);
}


HRESULT WINAPI Direct3D9ExWrapper::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode,D3DDISPLAYMODE* pMode)
{
	return m_pD3DEx->EnumAdapterModes(Adapter, Format, Mode, pMode);
}


HRESULT WINAPI Direct3D9ExWrapper::GetAdapterIdentifier(UINT Adapter, DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	return m_pD3DEx->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}


UINT WINAPI Direct3D9ExWrapper::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return m_pD3DEx->GetAdapterModeCount(Adapter, Format);
}


HRESULT WINAPI Direct3D9ExWrapper::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return m_pD3DEx->GetAdapterDisplayMode(Adapter, pMode);
}


HRESULT WINAPI Direct3D9ExWrapper::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType,D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return m_pD3DEx->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}


HRESULT WINAPI Direct3D9ExWrapper::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return m_pD3DEx->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}


HRESULT WINAPI Direct3D9ExWrapper::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
	return m_pD3DEx->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT WINAPI Direct3D9ExWrapper::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return m_pD3DEx->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}


HRESULT WINAPI Direct3D9ExWrapper::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return m_pD3DEx->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}


HRESULT WINAPI Direct3D9ExWrapper::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{	
	return m_pD3DEx->GetDeviceCaps(Adapter, DeviceType, pCaps);
}


HMONITOR WINAPI Direct3D9ExWrapper::GetAdapterMonitor(UINT Adapter)
{
	return m_pD3DEx->GetAdapterMonitor(Adapter);
}


HRESULT WINAPI Direct3D9ExWrapper::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow,DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	return m_pD3DEx->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
}


UINT WINAPI Direct3D9ExWrapper::GetAdapterModeCountEx(UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter )
{
	return m_pD3DEx->GetAdapterModeCountEx(Adapter, pFilter);
}


HRESULT WINAPI Direct3D9ExWrapper::EnumAdapterModesEx(UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter,UINT Mode,D3DDISPLAYMODEEX* pMode)
{	
	return m_pD3DEx->EnumAdapterModesEx(Adapter, pFilter, Mode, pMode);
}


HRESULT WINAPI Direct3D9ExWrapper::GetAdapterDisplayModeEx(UINT Adapter,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation)
{	
	return m_pD3DEx->GetAdapterDisplayModeEx(Adapter, pMode, pRotation);
}


HRESULT WINAPI Direct3D9ExWrapper::CreateDeviceEx(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface)
{	
	return m_pD3DEx->CreateDeviceEx(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, pFullscreenDisplayMode, ppReturnedDeviceInterface);
}


HRESULT WINAPI Direct3D9ExWrapper::GetAdapterLUID(UINT Adapter,LUID * pLUID)
{	
	return m_pD3DEx->GetAdapterLUID(Adapter, pLUID);
}