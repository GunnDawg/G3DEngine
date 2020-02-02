#pragma once
#include <DirectXMath.h>

struct VERTEX
{
	VERTEX() = default;
	VERTEX(const VERTEX&) = delete;
	VERTEX& operator= (const VERTEX&) = delete;

	VERTEX(float x, float y, float z) :
		Position(x, y, z), Color(1.0f, 0.0f, 1.0f, 1.0f)
	{}

	VERTEX(float x, float y, float z, DirectX::XMFLOAT4 color) :
		Position(x, y, z), Color(color)
	{}

	DirectX::XMFLOAT3 Position = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT4 Color = { 0.0f, 0.0f, 0.0f, 1.0 };
};