// ��ʊE�[�x�p�V�F�[�_�[
texture g_scene;	//�V�[���e�N�X�`���B

sampler g_SceneSampler =
sampler_state
{
	Texture = <g_scene>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
};


struct VS_DEPTH_INPUT{
	float4	pos		: POSITION;
	float4  BlendWeights:BLENDWEIGHT;
	float4  BlendIndices:BLENDINDICES;
};
struct VS_OUTPUT_DEPTH{
	float4 pos : POSITION;
	float4 wpos : TEXCOORD0;
	float4 PintoPoint:TEXCOORD1;
};

struct VS_DEPTH_INPUT_PRIM{
	float4	pos		: POSITION;
	float2  uv		: TEXCOORD0;
};
struct VS_OUTPUT_DEPTH_PRIM{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
	float2 SplitedUV : TEXCOORD1;	// ��������uv
	float4 wpos : TEXCOORD2;
	float4 PintoPoint:TEXCOORD3;
};


texture g_DepthSample;

sampler g_DepthSampler = 
sampler_state{
	Texture = <g_DepthSample>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
};

texture g_PrimTex;

sampler g_PrimTexSampler = 
sampler_state{
	Texture = <g_PrimTex>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
};

texture g_ZMaskSample;

sampler g_ZMaskSampler =
sampler_state{
	Texture = <g_ZMaskSample>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
};

float4x4 g_World;
float4x4 g_View;
float4x4 g_Proj;
float2 g_FarNear:register(c85);
float4 g_PintoPoint;	// �ǂ̈ʒu�Ƀs���g�����킹�邩(�s��ϊ���̒l)
float4x4 g_PintoWorld; // �s���g�p�̃��[���h�s��

// �X�L���s��
#define MAX_MATRICES 26
float4x3 g_WorldMatrixArray[MAX_MATRICES]:WORLDMATRIXARRAY;
float g_numBone;		// ���̐�

// �p�[�e�B�N���p
int Split_X;	// �摜������(��)
int Split_Y;	// �摜������(�c)
int NowCol;		// ���R�}��(��)
int NowRow;		// ���R�}��(�c)
float Ratio_X;	// ���̉摜�T�C�Y���琶�����ꂽ�摜�T�C�Y���������䗦(��)
float Ratio_Y;	// ���̉摜�T�C�Y���琶�����ꂽ�摜�T�C�Y���������䗦(�c)
float2 g_ScreenSize;	// �X�N���[���̃T�C�Y
float2 g_PrimSize;		// �v���~�e�B�u�̃T�C�Y

VS_OUTPUT_DEPTH VS_DepthSampling(VS_DEPTH_INPUT In, uniform bool IsAnimation){
	VS_OUTPUT_DEPTH Out = (VS_OUTPUT_DEPTH)0.0f;
	float4 pos;
	if (!IsAnimation){
		pos = mul(In.pos, g_World);
		pos = mul(pos, g_View);
		Out.pos = mul(pos, g_Proj);
		Out.wpos = Out.pos;
	}
	else{
		// �u�����h����{�[���̃C���f�b�N�X
		int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

		// �u�����h���[�g
		float BlendWeightsArray[4] = (float[4])In.BlendWeights;
		int IndexArray[4] = (int[4])IndexVector;
		float LastWeight = 0.0f;
		float3 work = (float3)0.0f;
		for (int iBone = 0; iBone < g_numBone - 1; iBone++){
			LastWeight = LastWeight + BlendWeightsArray[iBone];
			work += mul(In.pos, g_WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		}
		LastWeight = 1.0f - LastWeight;
		work += (mul(In.pos, g_WorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
		pos = mul(float4(work, 1.0f), g_View);
		Out.pos = mul(pos, g_Proj);
		Out.wpos = Out.pos;
	}

	float3 PintoPoint = g_PintoPoint.xyz;
	PintoPoint = mul(PintoPoint, g_PintoWorld);
	Out.PintoPoint = mul(float4(PintoPoint, 1.0f), g_View);
	Out.PintoPoint = mul(Out.PintoPoint, g_Proj);
	return Out;
}

float4 PS_DepthSampling(VS_OUTPUT_DEPTH In,uniform bool hasZMask) :COLOR{

	if (hasZMask){
		float4 work;
		work.xyz = In.wpos.xyz / In.wpos.w;
		work.xy *= float2(0.5f, -0.5f);			//-0.5�`0.5�͈̔͂ɂ���
		work.xy += 0.5f;						//0.0�`1.0�͈̔͂���B
		float4 zmask = tex2D(g_ZMaskSampler, work.xy);
		clip(work.z - zmask.z);
	}

	// �s���g�����킹��ʒu���v�Z
	float pinto = /*0.5f*/(In.PintoPoint.z - g_FarNear.y) / (g_FarNear.x - g_FarNear.y);
	float offset = 0.5f - pinto;

	// ���_�̍��W��FarNear�̂ǂ̈ʒu�ɂ��邩�v�Z
	float linerDepth = (In.wpos.z - g_FarNear.y) / (g_FarNear.x - g_FarNear.y);
	// �s���g�����킹���ꏊ�𒆐S(0.5f)�Ƃ��A�s���g�������悤�ɒ���
	float Depth = clamp(linerDepth + offset,0.0f,1.0f);

	// �N���ɉf��͈͂��L���邽�߂ɐ[�x�l�𒲐����鏈��
	if (Depth > 0.6f){
		Depth = 2.5f * (1.0f - Depth);
	}
	else if(Depth <= 0.6f && Depth >= 0.4f){
		Depth = 1.0f;
	}
	else{
		Depth = 2.5f * Depth;
	}
	// ��O���͋}���ɂڂ���(�s���g��0.1���̏������l�̍ہA��O�����ڂ��Ȃ��Ȃ邽��)
	if(linerDepth < pinto){
		Depth = Depth * (linerDepth / pinto);
	}

	return float4(Depth, Depth, Depth, 1.0f);
}

// ���_�V�F�[�_
VS_OUTPUT_DEPTH_PRIM VS_DepthSampling_Primitive(VS_DEPTH_INPUT_PRIM In /*���_���(���[�J�����W*/)
{
	VS_OUTPUT_DEPTH_PRIM Out;
	float4 pos;
	pos = mul(In.pos, g_World);	// ���[���h���W�ɕϊ�
	Out.wpos = Out.pos = pos;

	float2 uv = Out.uv = In.uv;
	uv.x *= 1.0f / Split_X;
	uv.x *= Ratio_X;
	uv.x += ((float)NowCol / Split_X) * Ratio_X;
	uv.y *= 1.0f / Split_Y;
	uv.y *= Ratio_Y;
	uv.y += ((float)NowRow / Split_Y) * Ratio_Y;
	Out.SplitedUV = uv;

	float3 PintoPoint = g_PintoPoint.xyz;
	PintoPoint = mul(PintoPoint, g_PintoWorld);
	Out.PintoPoint = mul(float4(PintoPoint, 1.0f), g_View);
	Out.PintoPoint = mul(Out.PintoPoint, g_Proj);

	return Out;	// ���_���(�X�N���[�����W)���X�N���[�����W��Ԃ��Ȃ���΃G���[�ƂȂ��Ă��܂��B
};

// �s�N�Z���V�F�[�_
float4 PS_DepthSampling_Primitive(VS_OUTPUT_DEPTH_PRIM In) : COLOR0{
	// �s���g�����킹��ʒu���v�Z
	float pinto = (In.PintoPoint.z - g_FarNear.y) / (g_FarNear.x - g_FarNear.y);
	float offset = 0.5f - pinto;

	// ���_�̍��W��FarNear�̂ǂ̈ʒu�ɂ��邩�v�Z
	float linerDepth = (In.wpos.z - g_FarNear.y) / (g_FarNear.x - g_FarNear.y);
	// �s���g�����킹���ꏊ�𒆐S(0.5f)�Ƃ��A�s���g�������悤�ɒ���
	float Depth = clamp(linerDepth + offset, 0.0f, 1.0f);

	// �N���ɉf��͈͂��L���邽�߂ɐ[�x�l�𒲐����鏈��
	if (Depth > 0.6f){
		Depth = 2.5f * (1.0f - Depth);
	}
	else if (Depth <= 0.6f && Depth >= 0.4f){
		Depth = 1.0f;
	}
	else{
		Depth = 2.5f * Depth;
	}
	// ��O���͋}���ɂڂ���(�s���g��0.1���̏������l�̍ہA��O�����ڂ��Ȃ��Ȃ邽��)
	if (linerDepth < pinto){
		Depth = Depth * (linerDepth / pinto);
	}

	float4 TexColor = tex2D(g_PrimTexSampler, In.SplitedUV);

	//// ���łɕ`�����܂�Ă���F���擾
	//float2 uv;
	//float4 ExistingColor;
	//uv = float2(0.5f,-0.5f) * In.wpos.xy / In.wpos.w + float2(0.5f,0.5f);
	//ExistingColor = tex2D(g_DepthSampler, uv);
	//Depth = ExistingColor.x * (1.0f - TexColor.w) + Depth * TexColor.w;

	return float4(Depth, Depth, Depth,TexColor.w);
};

struct VS_INPUT{
	float4	pos : POSITION;
};

struct VS_OUTPUT{
	float4 pos : POSITION;
	float2  tex : TEXCOORD;
};

struct VS_BlurOutput{
	float4 pos	: POSITION;
	float2 tex0	: TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
	float2 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float2 tex5 : TEXCOORD5;
	float2 tex6 : TEXCOORD6;
	float2 tex7 : TEXCOORD7;
};
texture g_blur;	//�u���[�e�N�X�`��

sampler g_blurSampler =
sampler_state
{
	Texture = <g_blur>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

float2 g_TexSize;		//�e�N�X�`���̃T�C�Y�B
float2 g_offset;				//�I�t�Z�b�g
float  g_weight[8];				//�K�E�X�t�B���^�̏d�݁B

/*!
* @brief	X�u���[���_�V�F�[�_�[�B
*/
VS_BlurOutput VSXBlur(VS_INPUT In)
{
	VS_BlurOutput Out;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;
	tex += float2(0.5 / g_TexSize.x, 0.5 / g_TexSize.y);
	Out.tex0 = tex + float2(-1.0f / g_TexSize.x, 0.0f);
	Out.tex1 = tex + float2(-3.0f / g_TexSize.x, 0.0f);
	Out.tex2 = tex + float2(-5.0f / g_TexSize.x, 0.0f);
	Out.tex3 = tex + float2(-7.0f / g_TexSize.x, 0.0f);
	Out.tex4 = tex + float2(-9.0f / g_TexSize.x, 0.0f);
	Out.tex5 = tex + float2(-11.0f / g_TexSize.x, 0.0f);
	Out.tex6 = tex + float2(-13.0f / g_TexSize.x, 0.0f);
	Out.tex7 = tex + float2(-15.0f / g_TexSize.x, 0.0f);
	return Out;
}
/*!
* @brief	X�u���[�s�N�Z���V�F�[�_�[�B
*/
float4 PSXBlur(VS_BlurOutput In) : COLOR
{
	float4 Color;
	Color = g_weight[0] * (tex2D(g_blurSampler, In.tex0)
		+ tex2D(g_blurSampler, In.tex7 + g_offset));
	Color += g_weight[1] * (tex2D(g_blurSampler, In.tex1)
		+ tex2D(g_blurSampler, In.tex6 + g_offset));
	Color += g_weight[2] * (tex2D(g_blurSampler, In.tex2)
		+ tex2D(g_blurSampler, In.tex5 + g_offset));
	Color += g_weight[3] * (tex2D(g_blurSampler, In.tex3)
		+ tex2D(g_blurSampler, In.tex4 + g_offset));
	Color += g_weight[4] * (tex2D(g_blurSampler, In.tex4)
		+ tex2D(g_blurSampler, In.tex3 + g_offset));
	Color += g_weight[5] * (tex2D(g_blurSampler, In.tex5)
		+ tex2D(g_blurSampler, In.tex2 + g_offset));
	Color += g_weight[6] * (tex2D(g_blurSampler, In.tex6)
		+ tex2D(g_blurSampler, In.tex1 + g_offset));
	Color += g_weight[7] * (tex2D(g_blurSampler, In.tex7)
		+ tex2D(g_blurSampler, In.tex0 + g_offset));
	return Color;
}
/*!
* @brief	Y�u���[���_�V�F�[�_�[�B
*/
VS_BlurOutput VSYBlur(VS_INPUT In)
{
	VS_BlurOutput Out;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;
	tex += float2(0.5 / g_TexSize.x, 0.5 / g_TexSize.y);

	Out.tex0 = tex + float2(0.0f, -1.0f / g_TexSize.y);
	Out.tex1 = tex + float2(0.0f, -3.0f / g_TexSize.y);
	Out.tex2 = tex + float2(0.0f, -5.0f / g_TexSize.y);
	Out.tex3 = tex + float2(0.0f, -7.0f / g_TexSize.y);
	Out.tex4 = tex + float2(0.0f, -9.0f / g_TexSize.y);
	Out.tex5 = tex + float2(0.0f, -11.0f / g_TexSize.y);
	Out.tex6 = tex + float2(0.0f, -13.0f / g_TexSize.y);
	Out.tex7 = tex + float2(0.0f, -15.0f / g_TexSize.y);
	return Out;
}
/*!
* @brief	Y�u���[�s�N�Z���V�F�[�_�[�B
*/
float4 PSYBlur(VS_BlurOutput In) : COLOR
{
	float4 Color;
	Color = g_weight[0] * (tex2D(g_blurSampler, In.tex0)
		+ tex2D(g_blurSampler, In.tex7 + g_offset));
	Color += g_weight[1] * (tex2D(g_blurSampler, In.tex1)
		+ tex2D(g_blurSampler, In.tex6 + g_offset));
	Color += g_weight[2] * (tex2D(g_blurSampler, In.tex2)
		+ tex2D(g_blurSampler, In.tex5 + g_offset));
	Color += g_weight[3] * (tex2D(g_blurSampler, In.tex3)
		+ tex2D(g_blurSampler, In.tex4 + g_offset));
	Color += g_weight[4] * (tex2D(g_blurSampler, In.tex4)
		+ tex2D(g_blurSampler, In.tex3 + g_offset));
	Color += g_weight[5] * (tex2D(g_blurSampler, In.tex5)
		+ tex2D(g_blurSampler, In.tex2 + g_offset));
	Color += g_weight[6] * (tex2D(g_blurSampler, In.tex6)
		+ tex2D(g_blurSampler, In.tex1 + g_offset));
	Color += g_weight[7] * (tex2D(g_blurSampler, In.tex7)
		+ tex2D(g_blurSampler, In.tex0 + g_offset));
	return Color;
}

texture g_Texture;
sampler g_TextureSampler = 
sampler_state{
	Texture = <g_Texture>;
	MipFilter = POINT;
	MinFilter = POINT;
	MagFilter = POINT;
};

/*!
* @brief	�t�@�C�i���B
*/
VS_OUTPUT VSFinal(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;		//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.tex = (In.pos.xy * 0.5f) + 0.5f;
	Out.tex.y = 1.0f - Out.tex.y;
	//Out.tex += g_offset;
	return Out;
}
float4 PSFinal(VS_OUTPUT In) : COLOR
{
	float2 uv = In.tex;
	float4 Depth = tex2D(g_DepthSampler, uv);	// �[�x�e�N�X�`��
	float4 Color1 = tex2D(g_TextureSampler, uv);	// �{�P�Ȃ��e�N�X�`��
	float4 Color2 = tex2D(g_blurSampler, uv);// �{�P�e�N�X�`��
	float4 Color = float4(Color1.xyz * Depth.x + Color2.xyz * (1.0f - Depth.x), 1.0f);
	return Color;
}

// �[�x��񒊏o�e�N�j�b�N(�{�[���Ȃ�)
technique DepthSampling_NonAnimation{
	pass p0{
		VertexShader = compile vs_3_0 VS_DepthSampling(false);
		PixelShader = compile ps_3_0 PS_DepthSampling(false);
	}
}
// �[�x��񒊏o�e�N�j�b�N(�{�[������)
technique DepthSampling_Animation{
	pass p0{
		VertexShader = compile vs_3_0 VS_DepthSampling(true);
		PixelShader = compile ps_3_0 PS_DepthSampling(false);
	}
}
// �[�x��񒊏o�e�N�j�b�N(�{�[���Ȃ��AZMask)
technique DepthSampling_NonAnimation_Z{
	pass p0{
		VertexShader = compile vs_3_0 VS_DepthSampling(false);
		PixelShader = compile ps_3_0 PS_DepthSampling(true);
	}
}
// �[�x��񒊏o�e�N�j�b�N(�{�[������AZMask)
technique DepthSampling_Animation_Z{
	pass p0{
		VertexShader = compile vs_3_0 VS_DepthSampling(true);
		PixelShader = compile ps_3_0 PS_DepthSampling(true);
	}
}
// �[�x��񒊏o�e�N�j�b�N(�p�[�e�B�N��)
technique DepthSampling_Primitive{
	pass p0{
		VertexShader = compile vs_3_0 VS_DepthSampling_Primitive();
		PixelShader = compile ps_3_0 PS_DepthSampling_Primitive();
	}
}

/*!
* @brief	���u���[
*/
technique XBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSXBlur();
		PixelShader = compile ps_3_0 PSXBlur();
	}
}

/*!
* @brief	�c�u���[
*/
technique YBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSYBlur();
		PixelShader = compile ps_3_0 PSYBlur();
	}
}
technique Final
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSFinal();
		PixelShader = compile ps_3_0 PSFinal();
	}
}