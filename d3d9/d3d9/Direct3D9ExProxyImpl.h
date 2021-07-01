#ifndef DIRECT3D9EXPROXYIMPL_H_INCLUDED
#define DIRECT3D9EXPROXYIMPL_H_INCLUDED

#include "Direct3D9ExWrapper.h"

class __declspec(dllexport) Direct3D9ExProxyImpl : public Direct3D9ExWrapper
{
public:
	Direct3D9ExProxyImpl(IDirect3D9Ex* pD3DEx);
	virtual ~Direct3D9ExProxyImpl();

	virtual HRESULT	 WINAPI CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow,	DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface);
	virtual HRESULT  WINAPI CreateDeviceEx(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface);
};

#endif