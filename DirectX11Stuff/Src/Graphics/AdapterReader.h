#pragma once
#include <D3D11.h>
#include <wrl/client.h>

struct AdapterData
{
	AdapterData(IDXGIAdapter* pAdapter);
	Microsoft::WRL::ComPtr<IDXGIAdapter> Adapter = nullptr;
	DXGI_ADAPTER_DESC Description = { 0 };
};

class AdapterReader
{
public:
	static std::vector<AdapterData> GetAdapters();

private:
	inline static std::vector<AdapterData> Adapters;
};