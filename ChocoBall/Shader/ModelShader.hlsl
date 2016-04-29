
float4x4 World;	// ���[���h�ϊ��s��錾
float4x4 View;	// �r���[�ϊ��s��錾
float4x4 Proj;	// �ˉe�ϊ��s��錾
float4x4 Rota;	// ��]�s��B�@�������f���Ɠ����ʂ�����]�����邽�߂ɕK�v
float3 EyePosition;	// ���_
float4x4 LightViewProj;		// ���C�g�r���[�v���W�F�N�V�����s��

#define DIFFUSE_LIGHT_NUM 4		// �f�B�t���[�Y���C�g�̐�
float4 diffuseLightDirection[DIFFUSE_LIGHT_NUM];	// �f�B�t���[�Y���C�g�̕���
float4 diffuseLightColor[DIFFUSE_LIGHT_NUM];	// �f�B�t���[�Y���C�g�̃J���[
float4 ambientLight;							// ����

texture g_Texture;			// �e�N�X�`��
sampler g_TextureSampler = 
sampler_state{
	Texture = <g_Texture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

texture g_ShadowMap;	// �V���h�E�}�b�v
sampler g_ShadowMapSampler =
sampler_state{
	Texture = <g_ShadowMap>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

// ���_�����͗p�\����
struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float3  normal  : NORMAL0;
	float2  uv		: TEXCOORD0;
};

// ���_���o�͗p�\����
struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2  uv		: TEXCOORD0;
	float3  normal	: TEXCOORD1;
	float4  WorldPos	: TEXCOORD2;	// ���[���h��Ԃł̒��_���W
	float4  ShadowPos	: TEXCOORD3;
};

// ���_�V�F�[�_
VS_OUTPUT BasicTransform(VS_INPUT In /*���_���(���[�J�����W*/)
{
	//�����ł��낢�뎩�R�ɐG������A���W�ϊ����s�����肷��B

	VS_OUTPUT Screen = (VS_OUTPUT)0;
	float4 pos;
	pos = mul(In.pos, World);	// ���[���h���W�ɕϊ�
	Screen.WorldPos = pos;
	pos = mul(pos, View);			// �r���[���W�ɕϊ�
	pos = mul(pos, Proj);			// �v���W�F�N�V�������W�ɕϊ�
	Screen.pos = pos;
	Screen.color = In.color;
	Screen.uv = In.uv;
	Screen.normal = mul(In.normal, Rota);		// �@������
	return Screen;	// ���_���(�X�N���[�����W)���X�N���[�����W��Ԃ��Ȃ���΃G���[�ƂȂ��Ă��܂��B
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
	// �f�B�t���[�Y���C�g���v�Z
	{
		float3 diff = 0.0f;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			diff += max(0.0f, dot(In.normal.xyz, -diffuseLightDirection[i].xyz)) * diffuseLightColor[i].xyz;
		}
		lig.xyz += diff;
	}
	// �X�y�L�������C�g���v�Z
	{
		float3 spec = 0.0f;
			float3 toEyeDir = normalize(EyePosition - In.WorldPos);
			float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			// �X�y�L�����������v�Z
			// ���˃x�N�g�����v�Z
			float3 L = -diffuseLightDirection[i].xyz;
				spec += diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * diffuseLightColor[i].w;	// �X�y�L�������x
		}
		lig.xyz += spec;
	}
	lig.xyz += ambientLight;
	float4 color = tex2D(g_TextureSampler, In.uv);	// �e�N�X�`����\��t����
	color.xyz *= lig;	// �e�N�X�`���̃J���[�ƃ��C�g����Z
	float4 ShadowPos = In.ShadowPos;
	float2 shadowMapUV = float2(0.5f, -0.5f) * ShadowPos.xy / ShadowPos.w + float2(0.5f, 0.5f);
	float4 shadow_val = tex2D(g_ShadowMapSampler, shadowMapUV);
	color *= shadow_val;
	return color;
}

// �s�N�Z���V�F�[�_
float4 TextureShader(VS_OUTPUT In) : COLOR{
	float4 lig = 0.0f;
	// �f�B�t���[�Y���C�g���v�Z
	{
		float3 diff = 0.0f;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			diff += max(0.0f, dot(In.normal.xyz, -diffuseLightDirection[i].xyz)) * diffuseLightColor[i].xyz;
		}
		lig.xyz += diff;
	}
	// �X�y�L�������C�g���v�Z
	{
		float3 spec = 0.0f;
		float3 toEyeDir = normalize(EyePosition - In.WorldPos);
		float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			// �X�y�L�����������v�Z
			// ���˃x�N�g�����v�Z
			float3 L = -diffuseLightDirection[i].xyz;
			spec += diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * diffuseLightColor[i].w;	// �X�y�L�������x
		}
		lig.xyz += spec;
	}
	lig.xyz += ambientLight;
	float4 color = tex2D(g_TextureSampler, In.uv);	// �e�N�X�`����\��t����
	color.xyz *= lig;	// �e�N�X�`���̃J���[�ƃ��C�g����Z
	return color;
};

float4 NoWorkingPixelShader(VS_OUTPUT In) :COLOR{
	float4 lig = 0.0f;
	// �f�B�t���[�Y���C�g���v�Z
	{
		float3 diff = 0.0f;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			diff += max(0.0f, dot(In.normal.xyz, -diffuseLightDirection[i].xyz)) * diffuseLightColor[i].xyz;
		}
		lig.xyz += diff;
	}
	// �X�y�L�������C�g���v�Z
	{
		float3 spec = 0.0f;
			float3 toEyeDir = normalize(EyePosition - In.WorldPos);
			float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			// �X�y�L�����������v�Z
			// ���˃x�N�g�����v�Z
			float3 L = -diffuseLightDirection[i].xyz;
				spec += diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * diffuseLightColor[i].w;	// �X�y�L�������x
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
		VertexShader = compile vs_2_0 BasicTransform();	// ���_�V�F�[�_
		PixelShader = compile ps_2_0 TextureShader();		// �s�N�Z���V�F�[�_
	}
};

technique BasicTec{
	pass p0{
		VertexShader = compile vs_2_0 BasicTransform();
		PixelShader = compile ps_2_0 NoWorkingPixelShader();
	}
};