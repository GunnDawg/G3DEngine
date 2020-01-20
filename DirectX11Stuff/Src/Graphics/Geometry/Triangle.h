#pragma once

#include <D3D11.h>

struct Triangle

{
	Triangle();
	~Triangle()=default;
	Triangle(const Triangle&) = delete;
	Triangle& operator=(const Triangle&) = delete;

	void Render();
	void CleanUp();

	ID3D11Buffer* buffer = nullptr;
	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11PixelShader* PixelShader = nullptr;
	ID3D10Blob* vShaderBuffer = nullptr;
	ID3D10Blob* pShaderBuffer = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
};