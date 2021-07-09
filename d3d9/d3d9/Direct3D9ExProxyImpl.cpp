#include "Direct3D9ExProxyImpl.h"
#include "Direct3DDevice9ExWrapper.h"
#include "HMDInterface.h"

#include "Main.h"


Direct3D9ExProxyImpl::Direct3D9ExProxyImpl(IDirect3D9Ex* pD3DEx) :
	Direct3D9ExWrapper(pD3DEx)
{
}


Direct3D9ExProxyImpl::~Direct3D9ExProxyImpl()
{
}

HRESULT WINAPI Direct3D9ExProxyImpl::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow,DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	HRESULT hResult = S_OK;
	IDirect3DDevice9 *pDirect3DDevice9 = NULL;
	IDirect3DDevice9Ex *pDirect3DDevice9Ex = NULL;

	hResult = Direct3D9ExWrapper::CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags | D3DCREATE_MULTITHREADED, pPresentationParameters, &pDirect3DDevice9);

	if (pDirect3DDevice9)
	{
		if (SUCCEEDED((pDirect3DDevice9)->QueryInterface(IID_IDirect3DDevice9Ex, reinterpret_cast<void**>(&pDirect3DDevice9Ex))))
		{
			DEBUG_LOG("Direct3DDevice9Ex created\n");
		}
		else
		{
			DEBUG_LOG("Normal D3D device created\n");
		}
	}

	if(FAILED(hResult))
	{
		DEBUG_LOG("No D3DDevice9 Created\n");
		return hResult;
	}

	// Create and return proxy
	IDirect3DDevice9Ex *pDevice = new Direct3DDevice9ExProxyImpl(pDirect3DDevice9Ex, this);
	*ppReturnedDeviceInterface = pDevice;

	pDirect3DDevice9Ex->Release();

	return hResult;
}

HRESULT WINAPI Direct3D9ExProxyImpl::CreateDeviceEx(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface)
{	
	DEBUG_LOG("Direct3D9ExProxyImpl::CreateDeviceEx\n");

	HRESULT hResult = S_OK;
	IDirect3DDevice9Ex *pDirect3DDevice9Ex = NULL;

	hResult = Direct3D9ExWrapper::CreateDeviceEx(Adapter, DeviceType, hFocusWindow, BehaviorFlags | D3DCREATE_MULTITHREADED, pPresentationParameters, pFullscreenDisplayMode, &pDirect3DDevice9Ex);
	if(FAILED(hResult))
	{
		DEBUG_LOG("No Direct3DDevice9 Created\n");
		return hResult;
	}

	// Create and return proxy
	IDirect3DDevice9Ex *pDevice = new Direct3DDevice9ExProxyImpl(pDirect3DDevice9Ex, this);
	*ppReturnedDeviceInterface = pDevice;

	pDirect3DDevice9Ex->Release();

	DEBUG_LOG("dxproxy D3D device created.\n");

	return hResult;
}
