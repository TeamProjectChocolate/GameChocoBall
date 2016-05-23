
float4x4 World;	// ワールド変換行列宣言
float Alpha;	// 透明度
int Split_X;	// 画像分割数(横)
int Split_Y;	// 画像分割数(縦)
int NowCol;		// 現コマ数(横)
int NowRow;		// 現コマ数(縦)

texture g_Texture;			// テクスチャ
sampler g_TextureSampler =
sampler_state{
	Texture = g_Texture;
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
VS_OUTPUT vs_main(VS_INPUT In /*頂点情報(ローカル座標*/)
{

	//ここでいろいろ自由に触ったり、座標変換を行ったりする。

	VS_OUTPUT Screen;
	float4 pos;
	pos = mul(In.pos, World);	// ワールド座標に変換
	Screen.pos = pos;
	Screen.color = In.color;
	Screen.uv = In.uv;
	return Screen;	// 頂点情報(スクリーン座標)←スクリーン座標を返さなければエラーとなってしまう。
};

// ピクセルシェーダ
float4 ps_main(VS_OUTPUT In) : COLOR0{
	In.color = (float4)0.0f;
	In.uv.x = In.uv.x / Split_X * (NowCol + 1);
	In.uv.y = In.uv.y / Split_Y * (NowRow + 1);
	float4 color = tex2D(g_TextureSampler, In.uv);
	color.w = Alpha;
	return color;	// テクスチャを貼り付ける
};

technique BasicTec{
	pass p0{
		VertexShader = compile vs_2_0 vs_main();	// 頂点シェーダ
		PixelShader = compile ps_2_0 ps_main();		// ピクセルシェーダ
	}
}
