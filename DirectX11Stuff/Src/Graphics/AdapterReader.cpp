#include "PCH.h"
#include "AdapterReader.h"

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	if (Adapters.size() > 0)
		return Adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

	//Create DXGIFactory Object
	HRESULT Result = 0;
	Result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
	if (FAILED(Result))
	{
		G3D::LOG_FATAL("Error creating DXGIFactory for enumerating adapters.");
	}

	Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		Adapters.emplace_back(AdapterData(pAdapter.Get()));
		index += 1;
	}

	return Adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	Adapter = pAdapter;
	HRESULT Result = 0;
	Result = pAdapter->GetDesc(&Description);
	if (FAILED(Result))
	{
		G3D::LOG_FATAL("Error getting video adapter description");
	}
}