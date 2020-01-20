#include "PCH.h"
#include "Graphics/Renderer.h"

#ifdef _DEBUG

UINT debugFlags = D3D11_CREATE_DEVICE_DEBUG;
#else

UINT debugFlags = 0u;
#endif


bool G3D::Renderer::Init()
{
	HRESULT Result = 0u;

	//@Incomplete Enumerating adapters here is not very fleshed out. We currenly only check for ANY available adapters.
	//In the future we should check for DirectX version compatibility, and ONLY initialize that DX version. Currently
	//DX11 is initialized by default.
	std::vector<AdapterData> adapters = AdapterReader::GetAdapters();
	if (adapters.size() < 1)
	{
		LOG_FATAL("No video adapters were found.");
		return(false);
	}

	//Create our swap chain buffer description
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = GameSettings::Display::Width;
	bufferDesc.Height = GameSettings::Display::Height;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Create swap chain description
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferDesc = bufferDesc;
	scd.BufferCount = 1u;
	scd.OutputWindow = GetActiveWindow();
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.SampleDesc.Count = 4u;
	scd.SampleDesc.Quality = 0u;
	scd.Windowed = GameSettings::Display::Windowed;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//Create our swap chain and device
	Result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		debugFlags,
		nullptr,
		0u,
		D3D11_SDK_VERSION,
		&scd,
		&SwapChain,
		&Device,
		nullptr,
		&Context);

	if (FAILED(Result))
	{
		LOG_FATAL("Failed to create swap chain");
		return(false);
	}

	//Name our swapchain for debug purposes later
	//const char* swap_chain_name = "SwapChain";
	//SwapChain->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(swap_chain_name), swap_chain_name);
	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	Result = SwapChain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)& BackBuffer);
	if (FAILED(Result))
	{
		LOG_FATAL("Failed to create back buffer");
		return(false);
	}

	//Create our Render Target
	Result = Device->CreateRenderTargetView(BackBuffer, NULL, &RenderTargetView);
	if (FAILED(Result))
	{
		LOG_FATAL("Failed to create render target");
		return(false);
	}

	BackBuffer->Release();

	//Create our depth stencil state
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.Width = GameSettings::Display::Width;
	depthStencilDesc.Height = GameSettings::Display::Height;
	depthStencilDesc.MipLevels = 1u;
	depthStencilDesc.ArraySize = 1u;
	depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilDesc.SampleDesc.Count = 4u;
	depthStencilDesc.SampleDesc.Quality = 0u;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilStateDesc.DepthEnable = TRUE;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	depthStencilStateDesc.StencilEnable = TRUE;
	depthStencilStateDesc.StencilReadMask = 0xFF;
	depthStencilStateDesc.StencilWriteMask = 0xFF;

	depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	Result = Device->CreateTexture2D(&depthStencilDesc, 0u, &DepthStencilBuffer);
	if (FAILED(Result))
	{
		LOG_FATAL("Failed to create depth stencil buffer");
		return(false);
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0u;

	Result = Device->CreateDepthStencilState(&depthStencilStateDesc, &DepthStencilState);
	if (FAILED(Result))
	{
		LOG_FATAL("Failed to create depth stencil state");
		return(false);
	}

	Result = Device->CreateDepthStencilView(DepthStencilBuffer, &descDSV, &DepthStencilView);
	if (FAILED(Result))
	{
		LOG_FATAL("Failed to create depth stencil view");
		return(false);
	}

	Context->OMSetRenderTargets(1u, &RenderTargetView, DepthStencilView);
	Context->OMSetDepthStencilState(DepthStencilState, 1u);

	//Set Default Rasterizer State
	D3D11_RASTERIZER_DESC RastDesc;
	ZeroMemory(&RastDesc, sizeof(D3D11_RASTERIZER_DESC));
	RastDesc.FillMode = D3D11_FILL_SOLID;
	RastDesc.CullMode = D3D11_CULL_NONE;
	RastDesc.MultisampleEnable = true;
	RastDesc.AntialiasedLineEnable = true;

	Result = Device->CreateRasterizerState(&RastDesc, &RasterizerState);
	if (FAILED(Result))
	{
		LOG_FATAL("Failed to create default rasterizer state");
		return(false);
	}

	Context->RSSetState(RasterizerState);

	//Create our viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Width = GameSettings::Display::Width;
	viewport.Height = GameSettings::Display::Height;
	viewport.TopLeftX = 0u;
	viewport.TopLeftY = 0u;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	Context->RSSetViewports(1, &viewport);

	return(true);
}

//@Speed Test this against the inline method to see which is faster
//void Renderer::Clear(DirectX::XMFLOAT4 color)
//{
//	const float clearColor[4] = {color.x, color.y, color.z, color.w};
//	Context->ClearRenderTargetView(RenderTargetView, clearColor);
//	Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
//}
//
//void Renderer::Present(bool vSync)
//{
//	HRESULT Result = 0u;
//	Result = SwapChain->Present(vSync, 0u);
//	if (FAILED(Result))
//	{
//		//This should never happen btw, and the few times that it has, it was kind of hard to track down.
//		LOG_FATAL("Failed to present back buffer");
//	}
//}

void G3D::Renderer::Shutdown()
{
	HRESULT Result = 0u;
	Result = SwapChain->SetFullscreenState(0u, 0u);
	if (FAILED(Result))
	{
		LOG_ERROR("Error shutting down fullscreen state!");
	}

	SAFE_RELEASE(RasterizerState);
	SAFE_RELEASE(DepthStencilBuffer);
	SAFE_RELEASE(DepthStencilView);
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(DepthStencilState);
	SAFE_RELEASE(Context);
	SAFE_RELEASE(Device);
}