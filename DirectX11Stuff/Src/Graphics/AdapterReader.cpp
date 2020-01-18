#include "PCH.h"
#include "AdapterReader.h"

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	if (adapters.size() > 0)
		return adapters;

	IDXGIFactory* pFactory = nullptr;

	//Create DXGIFactory Object
	HRESULT Result = 0;
	Result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(Result))
	{
		G3D::LOG_FATAL("Error creating DXGIFactory for enumerating adapters.");
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
		G3D::LOG_FATAL("Error getting video adapter description");
	}
}