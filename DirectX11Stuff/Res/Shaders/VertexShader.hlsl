struct VSOut
{
	float4 color: COLOR;
	float4 pos : SV_POSITION;
};



cbuffer CameraBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projMatrix;
};

VSOut main( float4 pos : POSITION, float4 color : COLOR )
{
    matrix camera = transpose(mul(projMatrix, mul(viewMatrix, worldMatrix)));

	VSOut vso;
    vso.pos = mul(pos, camera);
	vso.color = color;

	return vso;
}