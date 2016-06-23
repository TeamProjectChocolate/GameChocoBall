float4x4 World;
float4x4 View;
float4x4 Proj;

float2 g_FarNear;	// �����ʂƋߕ��ʁBx�ɉ����ʁAy�ɋߕ���

// �X�L���s��
#define MAX_MATRICES 26
float4x3 g_WorldMatrixArray[MAX_MATRICES]:WORLDMATRIXARRAY;
float g_numBone;		// ���̐�

struct VS_INPUT{
	float4	pos		: POSITION;
	float4  BlendWeights:BLENDWEIGHT;
	float4  BlendIndices:BLENDINDICES;
};

// ���_���o�͗p�\����
struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4  depth	: TEXCOORD;
};

VS_OUTPUT VS_ShadowMain(VS_INPUT In, uniform bool isBone){
	float4x4 LightViewProj;	// ���C�g���猩���Ƃ��̃r���[�v���W�F�N�V�����s��
	LightViewProj = mul(View, Proj);
	VS_OUTPUT Out = (VS_OUTPUT)0;

	if (isBone){
		float4 pos = 0.0f;
		// �u�����h����{�[���̃C���f�b�N�X
		int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

		// �u�����h���[�g
		float BlendWeightsArray[4] = (float[4])In.BlendWeights;
		int IndexArray[4] = (int[4])IndexVector;
		float LastWeight = 0.0f;
		for (int iBone = 0; iBone < g_numBone - 1; iBone++){
			LastWeight = LastWeight + BlendWeightsArray[iBone];
			pos.xyz += mul(In.pos, g_WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		}
		LastWeight = 1.0f - LastWeight;
		pos.xyz += (mul(In.pos, g_WorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);

		Out.pos = float4(pos.xyz, 1.0f);
	}
	else{
		Out.pos = mul(In.pos, World);
	}
	Out.pos = mul(Out.pos, LightViewProj);
	Out.depth = Out.pos;
	return Out;
}

float4 PS_ShadowMain(VS_OUTPUT In)	: COLOR{
	float z = (In.depth.z - g_FarNear.y) / (g_FarNear.x - g_FarNear.y);
	return float4(z,z,z,z);
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