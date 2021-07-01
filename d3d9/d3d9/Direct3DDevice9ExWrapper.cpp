#include "Direct3DDevice9ExWrapper.h"

#include "Main.h"


Direct3DDevice9ExWrapper::Direct3DDevice9ExWrapper(IDirect3DDevice9Ex* pDevice, Direct3D9ExWrapper* pCreatedBy) :
	m_pDeviceEx(pDevice),
	m_pCreatedBy(pCreatedBy),
	m_refCount(1)
{


}


Direct3DDevice9ExWrapper::~Direct3DDevice9ExWrapper()
{
	if(m_pDeviceEx)
		m_pDeviceEx->Release();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::QueryInterface(REFIID riid, LPVOID* ppv)
{	return m_pDeviceEx->QueryInterface(riid, ppv);
}


ULONG WINAPI Direct3DDevice9ExWrapper::AddRef()
{	 	return ++m_refCount;
}


ULONG WINAPI Direct3DDevice9ExWrapper::Release()
{	if(--m_refCount == 0)
	{
		delete this;
		return 0;
	}	

	return m_refCount;
}


HRESULT WINAPI Direct3DDevice9ExWrapper::TestCooperativeLevel()
{	 	return m_pDeviceEx->TestCooperativeLevel();
}

UINT WINAPI Direct3DDevice9ExWrapper::GetAvailableTextureMem()
{	return m_pDeviceEx->GetAvailableTextureMem();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::EvictManagedResources()
{	return m_pDeviceEx->EvictManagedResources();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetDirect3D(IDirect3D9** ppD3D9)
{
	if (!m_pCreatedBy)
		return D3DERR_INVALIDCALL;
	else {
		*ppD3D9 = m_pCreatedBy;
		m_pCreatedBy->AddRef();
		return D3D_OK;
	}
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetDeviceCaps(D3DCAPS9* pCaps)
{	return m_pDeviceEx->GetDeviceCaps(pCaps);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode)
{	return m_pDeviceEx->GetDisplayMode(iSwapChain, pMode);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{	return m_pDeviceEx->GetCreationParameters(pParameters);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap)
{	return m_pDeviceEx->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}


void WINAPI Direct3DDevice9ExWrapper::SetCursorPosition(int X,int Y,DWORD Flags)
{	return m_pDeviceEx->SetCursorPosition(X, Y, Flags);
}


BOOL WINAPI Direct3DDevice9ExWrapper::ShowCursor(BOOL bShow)
{	return m_pDeviceEx->ShowCursor(bShow);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain)
{	return m_pDeviceEx->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
{	return m_pDeviceEx->GetSwapChain(iSwapChain, pSwapChain);
}


UINT WINAPI Direct3DDevice9ExWrapper::GetNumberOfSwapChains()
{	return m_pDeviceEx->GetNumberOfSwapChains();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{	return m_pDeviceEx->Reset(pPresentationParameters);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{	return m_pDeviceEx->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{	return m_pDeviceEx->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus)
{	return m_pDeviceEx->GetRasterStatus(iSwapChain, pRasterStatus);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetDialogBoxMode(BOOL bEnableDialogs)
{	return m_pDeviceEx->SetDialogBoxMode(bEnableDialogs);
}


void WINAPI Direct3DDevice9ExWrapper::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp)
{		return m_pDeviceEx->SetGammaRamp(iSwapChain, Flags, pRamp);
}


void WINAPI Direct3DDevice9ExWrapper::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp)
{	return m_pDeviceEx->GetGammaRamp(iSwapChain, pRamp);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
{	return m_pDeviceEx->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
{	return m_pDeviceEx->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle)
{		return m_pDeviceEx->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
{		return m_pDeviceEx->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
{		return m_pDeviceEx->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{	return m_pDeviceEx->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{	return m_pDeviceEx->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint)
{	return m_pDeviceEx->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture)
{	return m_pDeviceEx->UpdateTexture(pSourceTexture, pDestinationTexture);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
{	return m_pDeviceEx->GetRenderTargetData(pRenderTarget, pDestSurface);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface)
{	return m_pDeviceEx->GetFrontBufferData(iSwapChain, pDestSurface);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
{	return m_pDeviceEx->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
{	return m_pDeviceEx->ColorFill(pSurface, pRect, color);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{	return m_pDeviceEx->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
{	return m_pDeviceEx->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
{	return m_pDeviceEx->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{	return m_pDeviceEx->SetDepthStencilSurface(pNewZStencil);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{	return m_pDeviceEx->GetDepthStencilSurface(ppZStencilSurface);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::BeginScene()
{	return m_pDeviceEx->BeginScene();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::EndScene()
{	return m_pDeviceEx->EndScene();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{	return m_pDeviceEx->Clear(Count, pRects, Flags, Color, Z, Stencil);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{	return m_pDeviceEx->SetTransform(State, pMatrix);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix)
{	return m_pDeviceEx->GetTransform(State, pMatrix);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::MultiplyTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{	return m_pDeviceEx->MultiplyTransform(State, pMatrix);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetViewport(CONST D3DVIEWPORT9* pViewport)
{	return m_pDeviceEx->SetViewport(pViewport);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetViewport(D3DVIEWPORT9* pViewport)
{	return m_pDeviceEx->GetViewport(pViewport);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{	return m_pDeviceEx->SetMaterial(pMaterial);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetMaterial(D3DMATERIAL9* pMaterial)
{	return m_pDeviceEx->GetMaterial(pMaterial);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetLight(DWORD Index,CONST D3DLIGHT9* pLight)
{	return m_pDeviceEx->SetLight(Index, pLight);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetLight(DWORD Index,D3DLIGHT9* pLight)
{	return m_pDeviceEx->GetLight(Index, pLight);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::LightEnable(DWORD Index,BOOL Enable)
{	return m_pDeviceEx->LightEnable(Index, Enable);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetLightEnable(DWORD Index,BOOL* pEnable)
{	return m_pDeviceEx->GetLightEnable(Index, pEnable);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetClipPlane(DWORD Index,CONST float* pPlane)
{	return m_pDeviceEx->SetClipPlane(Index, pPlane);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetClipPlane(DWORD Index,float* pPlane)
{	return m_pDeviceEx->GetClipPlane(Index, pPlane);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetRenderState(D3DRENDERSTATETYPE State,DWORD Value)
{	return m_pDeviceEx->SetRenderState(State, Value);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue)
{	return m_pDeviceEx->GetRenderState(State, pValue);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB)
{	return m_pDeviceEx->CreateStateBlock(Type, ppSB);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::BeginStateBlock()
{	return m_pDeviceEx->BeginStateBlock();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::EndStateBlock(IDirect3DStateBlock9** ppSB)
{	return m_pDeviceEx->EndStateBlock(ppSB);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{	return m_pDeviceEx->SetClipStatus(pClipStatus);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{	return m_pDeviceEx->GetClipStatus(pClipStatus);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture)
{	return m_pDeviceEx->GetTexture(Stage, ppTexture);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{	return m_pDeviceEx->SetTexture(Stage, pTexture);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue)
{	return m_pDeviceEx->GetTextureStageState(Stage, Type, pValue);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
{	return m_pDeviceEx->SetTextureStageState(Stage, Type, Value);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue)
{	return m_pDeviceEx->GetSamplerState(Sampler, Type, pValue);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value)
{	return m_pDeviceEx->SetSamplerState(Sampler, Type, Value);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::ValidateDevice(DWORD* pNumPasses)
{	return m_pDeviceEx->ValidateDevice(pNumPasses);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries)
{	return m_pDeviceEx->SetPaletteEntries(PaletteNumber, pEntries);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries)
{	return m_pDeviceEx->GetPaletteEntries(PaletteNumber, pEntries);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetCurrentTexturePalette(UINT PaletteNumber)
{	return m_pDeviceEx->SetCurrentTexturePalette(PaletteNumber);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetCurrentTexturePalette(UINT *PaletteNumber)
{	return m_pDeviceEx->GetCurrentTexturePalette(PaletteNumber);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetScissorRect(CONST RECT* pRect)
{	return m_pDeviceEx->SetScissorRect(pRect);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetScissorRect(RECT* pRect)
{	return m_pDeviceEx->GetScissorRect(pRect);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetSoftwareVertexProcessing(BOOL bSoftware)
{	return m_pDeviceEx->SetSoftwareVertexProcessing(bSoftware);
}


BOOL WINAPI Direct3DDevice9ExWrapper::GetSoftwareVertexProcessing()
{	return m_pDeviceEx->GetSoftwareVertexProcessing();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetNPatchMode(float nSegments)
{	return m_pDeviceEx->SetNPatchMode(nSegments);
}


float WINAPI Direct3DDevice9ExWrapper::GetNPatchMode()
{	return m_pDeviceEx->GetNPatchMode();
}


HRESULT WINAPI Direct3DDevice9ExWrapper::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount)
{	return m_pDeviceEx->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{	return m_pDeviceEx->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{	return m_pDeviceEx->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{	return m_pDeviceEx->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags)
{	return m_pDeviceEx->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
{	return m_pDeviceEx->CreateVertexDeclaration(pVertexElements, ppDecl);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{	return m_pDeviceEx->SetVertexDeclaration(pDecl);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{	return m_pDeviceEx->GetVertexDeclaration(ppDecl);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetFVF(DWORD FVF)
{	return m_pDeviceEx->SetFVF(FVF);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetFVF(DWORD* pFVF)
{	return m_pDeviceEx->GetFVF(pFVF);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader)
{	return m_pDeviceEx->CreateVertexShader(pFunction, ppShader);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetVertexShader(IDirect3DVertexShader9* pShader)
{	return m_pDeviceEx->SetVertexShader(pShader);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetVertexShader(IDirect3DVertexShader9** ppShader)
{	return m_pDeviceEx->GetVertexShader(ppShader);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{	return m_pDeviceEx->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{	return m_pDeviceEx->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{	return m_pDeviceEx->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{	return m_pDeviceEx->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{	return m_pDeviceEx->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{	return m_pDeviceEx->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride)
{	return m_pDeviceEx->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride)
{	return m_pDeviceEx->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetStreamSourceFreq(UINT StreamNumber,UINT Setting)
{	return m_pDeviceEx->SetStreamSourceFreq(StreamNumber, Setting);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetStreamSourceFreq(UINT StreamNumber,UINT* pSetting)
{	return m_pDeviceEx->GetStreamSourceFreq(StreamNumber, pSetting);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{	return m_pDeviceEx->SetIndices(pIndexData);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{	return m_pDeviceEx->GetIndices(ppIndexData);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader)
{	return m_pDeviceEx->CreatePixelShader(pFunction, ppShader);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetPixelShader(IDirect3DPixelShader9* pShader)
{	return m_pDeviceEx->SetPixelShader(pShader);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetPixelShader(IDirect3DPixelShader9** ppShader)
{	return m_pDeviceEx->GetPixelShader(ppShader);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{	return m_pDeviceEx->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{	return m_pDeviceEx->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{	return m_pDeviceEx->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{	return m_pDeviceEx->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{	return m_pDeviceEx->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{	return m_pDeviceEx->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{	return m_pDeviceEx->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{	return m_pDeviceEx->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::DeletePatch(UINT Handle)
{	return m_pDeviceEx->DeletePatch(Handle);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery)
{	return m_pDeviceEx->CreateQuery(Type, ppQuery);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetConvolutionMonoKernel(UINT width,UINT height,float* rows,float* columns)
{	return m_pDeviceEx->SetConvolutionMonoKernel(width, height, rows, columns);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::ComposeRects(IDirect3DSurface9* pSrc,IDirect3DSurface9* pDst,IDirect3DVertexBuffer9* pSrcRectDescs,UINT NumRects,IDirect3DVertexBuffer9* pDstRectDescs,D3DCOMPOSERECTSOP Operation,int Xoffset,int Yoffset)
{	return m_pDeviceEx->ComposeRects(pSrc, pDst, pSrcRectDescs, NumRects, pDstRectDescs, Operation, Xoffset, Yoffset);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::PresentEx(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags)
{	return m_pDeviceEx->PresentEx(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetGPUThreadPriority(INT* pPriority)
{	return m_pDeviceEx->GetGPUThreadPriority(pPriority);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetGPUThreadPriority(INT Priority)
{	return m_pDeviceEx->SetGPUThreadPriority(Priority);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::WaitForVBlank(UINT iSwapChain)
{	return m_pDeviceEx->WaitForVBlank(iSwapChain);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CheckResourceResidency(IDirect3DResource9** pResourceArray,UINT32 NumResources)
{	return m_pDeviceEx->CheckResourceResidency(pResourceArray, NumResources);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::SetMaximumFrameLatency(UINT MaxLatency)
{	return m_pDeviceEx->SetMaximumFrameLatency(MaxLatency);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetMaximumFrameLatency(UINT* pMaxLatency)
{	return m_pDeviceEx->GetMaximumFrameLatency(pMaxLatency);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CheckDeviceState(HWND hDestinationWindow)
{	return m_pDeviceEx->CheckDeviceState(hDestinationWindow);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateRenderTargetEx(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage)
{	return m_pDeviceEx->CreateRenderTargetEx(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle, Usage);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateOffscreenPlainSurfaceEx(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage)
{	return m_pDeviceEx->CreateOffscreenPlainSurfaceEx(Width, Height, Format, Pool, ppSurface, pSharedHandle, Usage);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::CreateDepthStencilSurfaceEx(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle,DWORD Usage)
{	return m_pDeviceEx->CreateDepthStencilSurfaceEx(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle, Usage);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::ResetEx(D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX *pFullscreenDisplayMode)
{	return m_pDeviceEx->ResetEx(pPresentationParameters, pFullscreenDisplayMode);
}


HRESULT WINAPI Direct3DDevice9ExWrapper::GetDisplayModeEx(UINT iSwapChain,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation)
{	return m_pDeviceEx->GetDisplayModeEx(iSwapChain, pMode, pRotation);
}


IDirect3DDevice9Ex* Direct3DDevice9ExWrapper::getRealDevice()
{
	return m_pDeviceEx;
}