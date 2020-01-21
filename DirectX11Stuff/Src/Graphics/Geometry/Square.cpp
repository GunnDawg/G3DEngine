#include "PCH.h"
#include "Core/Game/Game.h"
#include "Graphics/Renderer.h"
#include "Square.h"
#include "Graphics/Vertex.h"

Square::Square()
{
	HRESULT Result = 0u;

	const VERTEX vertices[] =
	{
		//Back Face
		{-1.0f, -1.0f, -1.0f, DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)},
		{ 1.0f, -1.0f, -1.0f, DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		{-1.0f,  1.0f, -1.0f, DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{ 1.0f,  1.0f, -1.0f, DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},

		//Front Face
		{-1.0f, -1.0f,  1.0f, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{ 1.0f, -1.0f,  1.0f, DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},
		{-1.0f,  1.0f,  1.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)},
		{ 1.0f,  1.0f,  1.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)}
	};

	const u16 indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"COLOR", 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
	};

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(D3D11_BUFFER_DESC));
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(vertices);
	vbd.StructureByteStride = sizeof(VERTEX);

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = vertices;

	Result = G3D::Renderer::Device->CreateBuffer(&vbd, &sd, &vertexBuffer);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error initialzing triangle!");
	}

	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(D3D11_BUFFER_DESC));
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(u16);

	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&isd, sizeof(D3D11_SUBRESOURCE_DATA));
	isd.pSysMem = indices;

	Result = G3D::Renderer::Device->CreateBuffer(&ibd, &isd, &indexBuffer);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error initialzing triangle!");
	}

	//Load and compile shader files
	Result = D3DX11CompileFromFile("Res/Shaders/VertexShader.hlsl", 0u, 0u, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0u, 0u, &vShaderBuffer, 0u, 0u);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error compiling vertex shader!");
	}

	Result = D3DX11CompileFromFile("Res/Shaders/PixelShader.hlsl", 0u, 0u, "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0u, 0u, &pShaderBuffer, 0u, 0u);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error compiling pixel shader!");
	}

	//Create shaders from compiled source
	Result = G3D::Renderer::Device->CreateVertexShader(vShaderBuffer->GetBufferPointer(), vShaderBuffer->GetBufferSize(), nullptr, &VertexShader);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error creating vertex shader!");
	}

	Result = G3D::Renderer::Device->CreatePixelShader(pShaderBuffer->GetBufferPointer(), pShaderBuffer->GetBufferSize(), nullptr, &PixelShader);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error creating pixel shader!");
	}

	//Create the vertex layout
	Result = G3D::Renderer::Device->CreateInputLayout(layout, (UINT)std::size(layout), vShaderBuffer->GetBufferPointer(), vShaderBuffer->GetBufferSize(), &inputLayout);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error setting input layout!");
	}

	//Set rasterizer state
	D3D11_RASTERIZER_DESC RastDesc;
	ZeroMemory(&RastDesc, sizeof(D3D11_RASTERIZER_DESC));
	RastDesc.FillMode = D3D11_FILL_SOLID;
	RastDesc.CullMode = D3D11_CULL_NONE;
	RastDesc.MultisampleEnable = true;
	RastDesc.AntialiasedLineEnable = true;

	Result = G3D::Renderer::Device->CreateRasterizerState(&RastDesc, &G3D::Renderer::RasterizerState);
	if (FAILED(Result))
	{
		G3D::LOG_FATAL("Failed to create rasterizer state");
	}

	G3D::Renderer::Context->RSSetState(G3D::Renderer::RasterizerState);
}

void Square::Update()
{
	HRESULT Result = 0u;

	//DirectX::XMMATRIX world = DirectX::XMMatrixRotationY(Game::Timer.Peek()) * DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f);
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

	const CameraConstantBuffer cb =
	{
		world,
		Game::Camera.GetViewMatrix(),
		Game::Camera.GetProjectionMatrix()
	};

	static D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;

	static D3D11_SUBRESOURCE_DATA srd;
	ZeroMemory(&srd, sizeof(D3D11_SUBRESOURCE_DATA));
	srd.pSysMem = &cb;

	Result = G3D::Renderer::Device->CreateBuffer(&cbd, &srd, &constantBuffer);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error creating constant buffer!");
	}
}

void Square::Render()
{
	static const UINT stride = sizeof(VERTEX);
	static const UINT offset = 0u;

	G3D::Renderer::Context->VSSetShader(VertexShader, nullptr, 0u);
	G3D::Renderer::Context->PSSetShader(PixelShader, nullptr, 0u);
	G3D::Renderer::Context->VSSetConstantBuffers(0u, 1u, &constantBuffer);
	G3D::Renderer::Context->IASetVertexBuffers(0u, 1u, &vertexBuffer, &stride, &offset);
	G3D::Renderer::Context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0u);
	G3D::Renderer::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	G3D::Renderer::Context->IASetInputLayout(inputLayout);

	G3D::Renderer::Context->DrawIndexed(36u, 0u, 0u);
}

void Square::CleanUp()
{
	SAFE_RELEASE(inputLayout);
	SAFE_RELEASE(vShaderBuffer);
	SAFE_RELEASE(pShaderBuffer);
	SAFE_RELEASE(constantBuffer);
	SAFE_RELEASE(PixelShader);
	SAFE_RELEASE(VertexShader);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}