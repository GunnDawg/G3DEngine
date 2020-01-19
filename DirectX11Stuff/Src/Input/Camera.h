#pragma once
#include <DirectXMath.h>

namespace G3D
{

	class Camera
	{
	public:
		Camera();
		void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

		inline const DirectX::XMMATRIX& GetViewMatrix() const
		{
			return mViewMatrix;
		}

		inline const DirectX::XMMATRIX& GetProjectionMatrix() const
		{
			return mProjectionMatrix;
		}

		inline const DirectX::XMVECTOR& GetPositionVector() const
		{
			return mPosVector;
		}

		inline const DirectX::XMFLOAT3& GetPositionFloat3() const
		{
			return mPos;
		}

		inline const DirectX::XMVECTOR& GetRotationVector() const
		{
			return mRotVector;
		}

		inline const DirectX::XMFLOAT3& GetRotationFloat3() const
		{
			return mRot;
		}

		void SetPosition(const DirectX::XMVECTOR& pos);
		void SetPosition(float x, float y, float z);
		void AdjustPosition(const DirectX::XMVECTOR& pos);
		void AdjustPosition(float x, float y, float z);
		void SetRotation(const DirectX::XMVECTOR& rot);
		void SetRotation(float x, float y, float z);
		void AdjustRotation(const DirectX::XMVECTOR& rot);
		void AdjustRotation(float x, float y, float z);

	private:
		void UpdateViewMatrix();
		DirectX::XMVECTOR mPosVector;
		DirectX::XMVECTOR mRotVector;
		DirectX::XMFLOAT3 mPos;
		DirectX::XMFLOAT3 mRot;
		DirectX::XMMATRIX mViewMatrix;
		DirectX::XMMATRIX mProjectionMatrix;

		const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	};
}