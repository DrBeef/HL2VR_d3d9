
#include "Direct3DDevice9ExProxyImpl.h"
#include "HMDInterface.h"

#include "Main.h"

#define  MAGIC_WIDTH		12340

#pragma comment(lib, "d3dx9.lib")

Direct3DDevice9ExProxyImpl::Direct3DDevice9ExProxyImpl(IDirect3DDevice9Ex* pDevice, Direct3D9ExWrapper* pCreatedBy):
	Direct3DDevice9ExWrapper(pDevice, pCreatedBy),
	hmdInterface(HMDInterface::Get(getRealDevice()))
{
}

Direct3DDevice9ExProxyImpl::~Direct3DDevice9ExProxyImpl()
{
}

HRESULT WINAPI Direct3DDevice9ExProxyImpl::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{
	HRESULT hr = S_OK;

	if (hmdInterface)
		hmdInterface->PrePresent();

	hr =  Direct3DDevice9ExWrapper::PresentEx(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion,  0);

	if (hmdInterface)
		hmdInterface->Submit();

	return hr;
}


HRESULT WINAPI Direct3DDevice9ExProxyImpl::PresentEx(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion, DWORD flags)
{
	HRESULT hr = S_OK;

	if (hmdInterface)
		hmdInterface->PrePresent();

	hr = Direct3DDevice9ExWrapper::PresentEx(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, flags);
	
	if (hmdInterface)
		hmdInterface->Submit();

	return hr;
}

HRESULT WINAPI Direct3DDevice9ExProxyImpl::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
{
	HANDLE shared_handle = NULL;

	//Use the special width to tell us whether we need to store this texture
	int index = -1;
	if (Width >= MAGIC_WIDTH)
	{
		uint32_t rtWidth, rtHeight;
		hmdInterface->GetRecommendedRenderTargetSize(&rtWidth, &rtHeight);

		//Double width for both eyes
		rtWidth *= 2;

		index = Width - MAGIC_WIDTH;

		pSharedHandle = &shared_handle;

		//Update to actual render target size 
		Width = rtWidth;
		Height = rtHeight;
	}

	if (index != -1)
		Pool = D3DPOOL_DEFAULT;
	HRESULT creationResult = Direct3DDevice9ExWrapper::CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	if (index != -1)
	{
		hmdInterface->StoreSharedTexture(index, *ppTexture, pSharedHandle);
	}

	return creationResult;
}
