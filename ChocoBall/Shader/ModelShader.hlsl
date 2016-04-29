
float4x4 World;	// ワールド変換行列宣言
float4x4 View;	// ビュー変換行列宣言
float4x4 Proj;	// 射影変換行列宣言
float4x4 Rota;	// 回転行列。法線をモデルと同じ量だけ回転させるために必要
float3 EyePosition;	// 視点
float4x4 LightViewProj;		// ライトビュープロジェクション行列

#define DIFFUSE_LIGHT_NUM 4		// ディフューズライトの数
float4 diffuseLightDirection[DIFFUSE_LIGHT_NUM];	// ディフューズライトの方向
float4 diffuseLightColor[DIFFUSE_LIGHT_NUM];	// ディフューズライトのカラー
float4 ambientLight;							// 環境光

texture g_Texture;			// テクスチャ
sampler g_TextureSampler = 
sampler_state{
	Texture = <g_Texture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture g_ShadowMap;	// シャドウマップ
sampler g_ShadowMapSampler =
sampler_state{
	Texture = <g_ShadowMap>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

// 頂点情報入力用構造体
struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float3  normal  : NORMAL0;
	float2  uv		: TEXCOORD0;
};

// 頂点情報出力用構造体
struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2  uv		: TEXCOORD0;
	float3  normal	: TEXCOORD1;
	float4  WorldPos	: TEXCOORD2;	// ワールド空間での頂点座標
	float4  ShadowPos	: TEXCOORD3;
};

// 頂点シェーダ
VS_OUTPUT BasicTransform(VS_INPUT In /*頂点情報(ローカル座標*/)
{
	//ここでいろいろ自由に触ったり、座標変換を行ったりする。

	VS_OUTPUT Screen = (VS_OUTPUT)0;
	float4 pos;
	pos = mul(In.pos, World);	// ワールド座標に変換
	Screen.WorldPos = pos;
	pos = mul(pos, View);			// ビュー座標に変換
	pos = mul(pos, Proj);			// プロジェクション座標に変換
	Screen.pos = pos;
	Screen.color = In.color;
	Screen.uv = In.uv;
	Screen.normal = mul(In.normal, Rota);		// 法線を回す
	return Screen;	// 頂点情報(スクリーン座標)←スクリーン座標を返さなければエラーとなってしまう。
};

VS_OUTPUT ShadowVertex(VS_INPUT In){
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos;
	pos = mul(In.pos, World);
	Out.WorldPos = pos;
	Out.ShadowPos = mul(pos, LightViewProj);
	pos = mul(pos, View);
	pos = mul(pos, Proj);
	Out.pos = pos;
	Out.color = In.color;
	Out.uv = In.uv;
	Out.normal = mul(In.normal, Rota);
	return Out;
}

float4 ShadowPixel(VS_OUTPUT In) :	COLOR{
	float4 lig = 0.0f;
	// ディフューズライトを計算
	{
		float3 diff = 0.0f;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			diff += max(0.0f, dot(In.normal.xyz, -diffuseLightDirection[i].xyz)) * diffuseLightColor[i].xyz;
		}
		lig.xyz += diff;
	}
	// スペキュラライトを計算
	{
		float3 spec = 0.0f;
			float3 toEyeDir = normalize(EyePosition - In.WorldPos);
			float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			// スペキュラ成分を計算
			// 反射ベクトルを計算
			float3 L = -diffuseLightDirection[i].xyz;
				spec += diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * diffuseLightColor[i].w;	// スペキュラ強度
		}
		lig.xyz += spec;
	}
	lig.xyz += ambientLight;
	float4 color = tex2D(g_TextureSampler, In.uv);	// テクスチャを貼り付ける
	color.xyz *= lig;	// テクスチャのカラーとライトを乗算
	float4 ShadowPos = In.ShadowPos;
	float2 shadowMapUV = float2(0.5f, -0.5f) * ShadowPos.xy / ShadowPos.w + float2(0.5f, 0.5f);
	float4 shadow_val = tex2D(g_ShadowMapSampler, shadowMapUV);
	color *= shadow_val;
	return color;
}

// ピクセルシェーダ
float4 TextureShader(VS_OUTPUT In) : COLOR{
	float4 lig = 0.0f;
	// ディフューズライトを計算
	{
		float3 diff = 0.0f;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			diff += max(0.0f, dot(In.normal.xyz, -diffuseLightDirection[i].xyz)) * diffuseLightColor[i].xyz;
		}
		lig.xyz += diff;
	}
	// スペキュラライトを計算
	{
		float3 spec = 0.0f;
		float3 toEyeDir = normalize(EyePosition - In.WorldPos);
		float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			// スペキュラ成分を計算
			// 反射ベクトルを計算
			float3 L = -diffuseLightDirection[i].xyz;
			spec += diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * diffuseLightColor[i].w;	// スペキュラ強度
		}
		lig.xyz += spec;
	}
	lig.xyz += ambientLight;
	float4 color = tex2D(g_TextureSampler, In.uv);	// テクスチャを貼り付ける
	color.xyz *= lig;	// テクスチャのカラーとライトを乗算
	return color;
};

float4 NoWorkingPixelShader(VS_OUTPUT In) :COLOR{
	float4 lig = 0.0f;
	// ディフューズライトを計算
	{
		float3 diff = 0.0f;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			diff += max(0.0f, dot(In.normal.xyz, -diffuseLightDirection[i].xyz)) * diffuseLightColor[i].xyz;
		}
		lig.xyz += diff;
	}
	// スペキュラライトを計算
	{
		float3 spec = 0.0f;
			float3 toEyeDir = normalize(EyePosition - In.WorldPos);
			float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			// スペキュラ成分を計算
			// 反射ベクトルを計算
			float3 L = -diffuseLightDirection[i].xyz;
				spec += diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * diffuseLightColor[i].w;	// スペキュラ強度
		}
		lig.xyz += spec;
	}
	lig.xyz += ambientLight;
	In.color.xyz *= lig;
	return In.color;
};

technique ShadowTec{
	pass p0{
		VertexShader = compile vs_2_0 ShadowVertex();
		PixelShader = compile ps_2_0 ShadowPixel();
	}
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