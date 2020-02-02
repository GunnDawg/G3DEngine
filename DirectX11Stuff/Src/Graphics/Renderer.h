#pragma once
#include "AdapterReader.h"
#include <D3D11.h>
#include <D3DX10.h>
#include <D3DX11.h>
#include <DirectXMath.h>

#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DX10.lib")
#pragma comment(lib, "D3DX11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "DXGI.lib")

template<typename T>
inline static void SAFE_RELEASE(T& ptr)
{
	HRESULT Result = 0u;
	if (ptr != nullptr)
	{
		Result = ptr->Release();
		if (FAILED(Result))
		{
			G3D::LOG_ERROR("Failed to release COM object");
		}

		ptr = nullptr;
	}
}

namespace G3D
{
	class Renderer
	{
	public:
		bool Init();

		//I feel like these are small enough to be inlined.
		inline void Clear(DirectX::XMFLOAT4 color) const
		{
			const float clearColor[4] = { color.x, color.y, color.z, color.w };
			Context->ClearRenderTargetView(RenderTargetView, clearColor);
			Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
		}

		inline void Present(bool vSync) const
		{
			HRESULT Result = 0u;
			Result = SwapChain->Present(vSync, 0u);
			if (FAILED(Result))
			{
				//This should never happen btw, and the few times that it has, it was kind of hard to track down.
				G3D::LOG_FATAL("Failed to present back buffer");
			}
		}

		void Shutdown();

		//Basic DirectX
		inline static ID3D11Device* Device = nullptr;
		inline static ID3D11DeviceContext* Context = nullptr;
		inline static ID3D11RasterizerState* RasterizerState = nullptr;

	private:
		//Basic DirectX
		IDXGISwapChain* SwapChain = nullptr;
		ID3D11RenderTargetView* RenderTargetView = nullptr;

		//Depth Stencil
		ID3D11DepthStencilState* DepthStencilState = nullptr;
		ID3D11Texture2D* DepthStencilBuffer = nullptr;
		ID3D11DepthStencilView* DepthStencilView = nullptr;
	};
}