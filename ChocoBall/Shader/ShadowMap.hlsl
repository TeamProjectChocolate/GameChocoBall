float4x4 World;
float4x4 View;
float4x4 Proj;

//texture g_ShadowMap;	// シャドウマップ
//sampler g_ShadowMapSampler =
//sampler_state{
//	Texture = <g_ShadowMap>;
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//	AddressU = Clamp;
//	AddressV = Clamp;
//};

struct VS_INPUT{
	float4	pos		: POSITION;
};

// 頂点情報出力用構造体
struct VS_OUTPUT{
	float4	pos		: POSITION;
	//float4  WorldPos	: TEXCOORD2;	// ワールド空間での頂点座標
	//float4  OffScreen	: TEXCOORD3;	// オフスクリーンに描画する際のスクリーン座標
};

VS_OUTPUT VS_ShadowMain(VS_INPUT In){
	float4x4 LightViewProj;	// ライトから見たときのビュープロジェクション行列
	LightViewProj = mul(View, Proj);
	VS_OUTPUT Out;
	float4 pos = mul(In.pos, World);
	Out.pos = mul(pos, LightViewProj);
	return Out;
}

float4 PS_ShadowMain(VS_OUTPUT In)	: COLOR{
	return float4(0.0f,0.0f,0.0f,1.0f);
}

technique ShadowMapping{
	pass p0{
		VertexShader = compile vs_2_0 VS_ShadowMain();
		PixelShader = compile ps_2_0 PS_ShadowMain();
	}
};