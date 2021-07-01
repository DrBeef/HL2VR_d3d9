#ifndef D3DPROXYDEVICEEX_H_INCLUDED
#define D3DPROXYDEVICEEX_H_INCLUDED

#pragma warning (disable : 4005)

#include "Direct3DDevice9ExWrapper.h"
#include "Main.h"

class HMDInterface;

class Direct3DDevice9ExProxyImpl : public Direct3DDevice9ExWrapper
{
public:
	Direct3DDevice9ExProxyImpl(IDirect3DDevice9Ex* pDevice, Direct3D9ExWrapper* pCreatedBy);
	virtual ~Direct3DDevice9ExProxyImpl();

	virtual HRESULT WINAPI Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);
	virtual HRESULT WINAPI CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle);
	virtual HRESULT WINAPI PresentEx(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD flags);

private:
	HMDInterface* hmdInterface;
};

#endif //D3DPROXYDEVICEEX_H_INCLUDED