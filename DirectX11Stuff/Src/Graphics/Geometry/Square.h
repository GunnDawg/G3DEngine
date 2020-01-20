#pragma once


struct ConstantBuffer

{
	DirectX::XMMATRIX transform;
};

struct CameraConstantBuffer

{
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projMatrix;
};

struct Square

{
	Square();
	~Square() = default;
	Square(const Square&) = delete;
	Square& operator=(const Square&) = delete;

	void Update();
	void Render();
	void CleanUp();

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Buffer* constantBuffer = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11PixelShader* PixelShader = nullptr;
	ID3D10Blob* vShaderBuffer = nullptr;
	ID3D10Blob* pShaderBuffer = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
};