#include "PCH.h"
#include "AdapterReader.h"

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	if (adapters.size() > 0)
		return adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	//Create DXGIFactory Object
	HRESULT Result = 0;
	Result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
	if (FAILED(Result))
	{
		LOG_FATAL("Error creating DXGIFactory for enumerating adapters.");
	}

	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		adapters.emplace_back(AdapterData(pAdapter));
		index += 1;
	}

	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdapter = pAdapter;
	HRESULT Result = 0;
	Result = pAdapter->GetDesc(&description);
	if (FAILED(Result))
	{
		LOG_FATAL("Error getting video adapter description");
	}
}