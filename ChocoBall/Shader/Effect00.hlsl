
float4x4 World;	// ワールド変換行列宣言
float4x4 View;	// ビュー変換行列宣言
float4x4 Proj;	// 射影変換行列宣言

texture g_Texture;			// テクスチャ
sampler g_TextureSampler = 
sampler_state{
	Texture = g_Texture;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

// 頂点情報入力用構造体
struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2  uv		: TEXCOORD0;	// 頂点に貼るべきテクスチャのアドレス？
};

// 頂点情報出力用構造体
struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2  uv		: TEXCOORD0;
};

// 頂点シェーダ
VS_OUTPUT BasicTransform(VS_INPUT In /*頂点情報(ローカル座標*/)
{

	//ここでいろいろ自由に触ったり、座標変換を行ったりする。

	VS_OUTPUT Screen;
	float4 pos;
	pos = mul(In.pos, World);	// ワールド座標に変換
	pos = mul(pos, View);			// ビュー座標に変換
	pos = mul(pos, Proj);			// プロジェクション座標に変換
	Screen.pos = pos;
	Screen.color = In.color;
	Screen.uv = In.uv;
	return Screen;	// 頂点情報(スクリーン座標)←スクリーン座標を返さなければエラーとなってしまう。
};

// ピクセルシェーダ
float4 TextureShader(VS_OUTPUT In) : COLOR{
	return tex2D(g_TextureSampler,In.uv);	// テクスチャを貼り付ける
};

float4 NoWorkingPixelShader(VS_OUTPUT In) :COLOR{
	return In.color;
};

technique TextureTec{
	pass p0{
		VertexShader = compile vs_2_0 BasicTransform();	// 頂点シェーダ
		PixelShader = compile ps_2_0 TextureShader();		// ピクセルシェーダ
	}
};

technique BasicTec{
	pass p0{
		VertexShader = compile vs_2_0 BasicTransform();
		PixelShader = compile ps_2_0 NoWorkingPixelShader();
	}
};