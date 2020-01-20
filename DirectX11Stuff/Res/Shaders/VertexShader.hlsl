struct VSOut
{
	float4 color: COLOR;
	float4 pos : SV_POSITION;
};

cbuffer CBuffer
{
    matrix transform;
};

cbuffer CameraBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projMatrix;
};	

VSOut main( float4 pos : POSITION, float4 color : COLOR )
{
    matrix camera = worldMatrix * viewMatrix * projMatrix;
	
	VSOut vso;
    vso.pos = mul(pos, transform);
	vso.color = color;

	return vso;
}