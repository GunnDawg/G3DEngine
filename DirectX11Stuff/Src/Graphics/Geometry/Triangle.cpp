#include "PCH.h"
#include "Triangle.h"
#include "Graphics/Renderer.h"
#include "Graphics/Vertex.h"

Triangle::Triangle()
{
	HRESULT Result = 0u;

	const VERTEX vertices[] =
	{
		{ 0.0f,  0.5f, 1.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{ 0.5f, -0.5f, 1.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)},
		{-0.5f, -0.5f, 1.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)}
	};

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u},
		{"COLOR", 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0u},
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(VERTEX);

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = vertices;

	Result = G3D::Renderer::Device->CreateBuffer(&bd, &sd, &buffer);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error initialzing triangle!");
	}

	const UINT stride = sizeof(VERTEX);
	const UINT offset = 0u;

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

	Result = G3D::Renderer::Device->CreateInputLayout(layout, (UINT)std::size(layout), vShaderBuffer->GetBufferPointer(), vShaderBuffer->GetBufferSize(), &inputLayout);
	if (FAILED(Result))
	{
		G3D::LOG_ERROR("Error setting input layout!");
	}

	//Renderer::Device->CreateVertexShader(vShaderBuffer->GetBufferPointer(), vShaderBuffer->GetBufferSize(), nullptr, &VertexShader);
	//Renderer::Context->VSSetShader(VertexShader, nullptr, 0);
	//Renderer::Device->CreatePixelShader(pShaderBuffer->GetBufferPointer(), pShaderBuffer->GetBufferSize(), nullptr, &PixelShader);
	//Renderer::Context->PSSetShader(PixelShader, nullptr, 0);
	//Renderer::Context->IASetVertexBuffers(0u, 1u, &buffer, &stride, &offset);
	//Renderer::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//Renderer::Context->IASetInputLayout(inputLayout);
}

void Triangle::Render()
{
	const UINT stride = sizeof(VERTEX);
	const UINT offset = 0u;

	G3D::Renderer::Device->CreateVertexShader(vShaderBuffer->GetBufferPointer(), vShaderBuffer->GetBufferSize(), nullptr, &VertexShader);
	G3D::Renderer::Context->VSSetShader(VertexShader, nullptr, 0u);
	G3D::Renderer::Device->CreatePixelShader(pShaderBuffer->GetBufferPointer(), pShaderBuffer->GetBufferSize(), nullptr, &PixelShader);
	G3D::Renderer::Context->PSSetShader(PixelShader, nullptr, 0u);
	G3D::Renderer::Context->IASetVertexBuffers(0u, 1u, &buffer, &stride, &offset);
	G3D::Renderer::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	G3D::Renderer::Context->IASetInputLayout(inputLayout);

	G3D::Renderer::Context->Draw(3u, 0u);
}

void Triangle::CleanUp()
{
	SAFE_RELEASE(vShaderBuffer);
	SAFE_RELEASE(pShaderBuffer);
	SAFE_RELEASE(PixelShader);
	SAFE_RELEASE(VertexShader);
	SAFE_RELEASE(buffer);
	SAFE_RELEASE(inputLayout);
}