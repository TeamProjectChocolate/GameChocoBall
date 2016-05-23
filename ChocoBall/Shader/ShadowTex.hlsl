float4x4 World;
float4x4 View;
float4x4 Proj;

// スキン行列
#define MAX_MATRICES 26
float4x3 g_WorldMatrixArray[MAX_MATRICES]:WORLDMATRIXARRAY;
float g_numBone;		// 骨の数

struct VS_INPUT{
	float4	pos		: POSITION;
	float4  BlendWeights:BLENDWEIGHT;
	float4  BlendIndices:BLENDINDICES;
};

// 頂点情報出力用構造体
struct VS_OUTPUT{
	float4	pos		: POSITION;
};

VS_OUTPUT VS_ShadowMain(VS_INPUT In, uniform bool isBone){
	float4x4 LightViewProj;	// ライトから見たときのビュープロジェクション行列
	LightViewProj = mul(View, Proj);
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos = 0.0f;

	if (isBone){
		// ブレンドするボーンのインデックス
		int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

		// ブレンドレート
		float BlendWeightsArray[4] = (float[4])In.BlendWeights;
		int IndexArray[4] = (int[4])IndexVector;
		float LastWeight = 0.0f;
		for (int iBone = 0; iBone < g_numBone - 1; iBone++){
			LastWeight = LastWeight + BlendWeightsArray[iBone];
			pos.xyz += mul(In.pos.xyz, g_WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		}
		LastWeight = 1.0f - LastWeight;
		pos.xyz += (mul(In.pos.xyz, g_WorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);

		Out.pos = mul(float4(pos.xyz, 1.0f), View);
		Out.pos = mul(Out.pos, Proj);
	}
	else{
		pos = mul(In.pos, World);
		pos.w = 1.0f;
	}
	Out.pos = mul(pos, LightViewProj);
	return Out;
}

float4 PS_ShadowMain(VS_OUTPUT In)	: COLOR{
	return float4(0.5f,0.5f,0.5f,1.0f);
}

technique BonelessShadowMapping{
	pass p0{
		VertexShader = compile vs_2_0 VS_ShadowMain(false);
		PixelShader = compile ps_2_0 PS_ShadowMain();
	}
};

technique BoneShadowMapping{
	pass p0{
		VertexShader = compile vs_2_0 VS_ShadowMain(true);
		PixelShader = compile ps_2_0 PS_ShadowMain();
	}
};