#pragma once
#include <D3D11.h>

struct AdapterData
{
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* pAdapter = nullptr;
	DXGI_ADAPTER_DESC description = { 0 };
};

class AdapterReader
{
public:
	static std::vector<AdapterData> GetAdapters();

private:
	inline static std::vector<AdapterData> adapters;
};