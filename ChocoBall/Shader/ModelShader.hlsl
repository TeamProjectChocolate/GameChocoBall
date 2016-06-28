
float4x4 World;	// ���[���h�ϊ��s��錾
float4x4 View;	// �r���[�ϊ��s��錾
float4x4 Proj;	// �ˉe�ϊ��s��錾
float4x4 Rota;	// ��]�s��B�@�������f���Ɠ����ʂ�����]�����邽�߂ɕK�v
float3 EyePosition;	// ���_
float4x4 LightViewProj;		// ���C�g�r���[�v���W�F�N�V�����s��

float2 g_FarNear;

float Alpha;		// �����x

#define DIFFUSE_LIGHT_NUM 4		// �f�B�t���[�Y���C�g�̐�
float4 diffuseLightDirection[DIFFUSE_LIGHT_NUM];	// �f�B�t���[�Y���C�g�̕���
float4 diffuseLightColor[DIFFUSE_LIGHT_NUM];	// �f�B�t���[�Y���C�g�̃J���[
float4 ambientLight;							// ����

// �X�L���s��
#define MAX_MATRICES 26
float4x3 g_WorldMatrixArray[MAX_MATRICES]:WORLDMATRIXARRAY;
float g_numBone;		// ���̐�

float4x4 g_CameraRotaInverse;	// �J�����̉�]�s��̋t�s��

float g_luminance;	// �P�x�̌��̗ʂ𒲐����邽�߂̕ϐ�

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
texture g_ZMask;	// Z�}�X�N
sampler g_ZMaskSampler =
sampler_state{
	Texture = <g_ZMask>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};
texture g_normalMap;	// �@���}�b�v
sampler g_normalMapSampler = 
sampler_state{
	Texture = <g_normalMap>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

// ���_�����͗p�\����
struct VS_INPUT{
	float4	pos		: POSITION;
	float4  BlendWeights:BLENDWEIGHT;
	float4  BlendIndices:BLENDINDICES;
	float4	color	: COLOR0;
	float3  normal  : NORMAL0;	// ���[���h���W�ɂ�����@��?
	float2  uv		: TEXCOORD0;
	float3  tangent : TANGENT0;	// �ڃx�N�g��(�|���S�����甭�����@���ƒ��p�Ɍ����x�N�g���A�|���S���ɉ���)
};

// ���_���o�͗p�\����
struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2  uv		: TEXCOORD0;
	float3  normal	: TEXCOORD1;
	float4  WorldPos	: TEXCOORD2;	// ���[���h��Ԃł̒��_���W
	float4  ShadowPos	: TEXCOORD3;
	float3  tangent :  TEXCOORD4;	// �ڃx�N�g��
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
	Screen.tangent = mul(In.tangent, Rota);		// �ڃx�N�g������
	return Screen;	// ���_���(�X�N���[�����W)���X�N���[�����W��Ԃ��Ȃ���΃G���[�ƂȂ��Ă��܂��B
}

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
	Out.tangent = mul(In.tangent, Rota);
	return Out;
}

VS_OUTPUT AnimationVertex(VS_INPUT In){
	VS_OUTPUT Out = (VS_OUTPUT)0;

	// �u�����h����{�[���̃C���f�b�N�X
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	// �u�����h���[�g
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int IndexArray[4] = (int[4])IndexVector;
	float LastWeight = 0.0f;
	float3 pos = 0.0f;
	float3 normal = 0.0f;
	for (int iBone = 0; iBone < g_numBone - 1; iBone++){
		LastWeight = LastWeight + BlendWeightsArray[iBone];
		pos += mul(In.pos, g_WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		normal += mul(In.normal, g_WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;
	pos += (mul(In.pos, g_WorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
	normal += mul(In.normal, g_WorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight;

	Out.WorldPos = float4(pos.xyz, 1.0f);
	Out.pos = mul(Out.WorldPos, View);
	Out.pos = mul(Out.pos, Proj);
	Out.normal = normal;// mul(normalize(normal), Rota);
	Out.color = In.color;
	Out.uv = In.uv;
	return Out;
}

float4 CalcDiffuseLight(float3 normal){
	float4 lig = 0.0f;
	// �f�B�t���[�Y���C�g���v�Z
	float3 diff = 0.0f;
	for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
		lig.xyz += max(0.0f, dot(normal.xyz, -diffuseLightDirection[i].xyz)) * diffuseLightColor[i].xyz;
	}
	return lig;
}

float4 CalcSpeculerLight(float3 normal,float4 worldpos){
	float4 lig = 0.0f;
	float3 toEyeDir = normalize(EyePosition - worldpos);
	float3 R = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
		// �X�y�L�����������v�Z
		// ���˃x�N�g�����v�Z
		float3 L = -diffuseLightDirection[i].xyz;
		lig += diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * diffuseLightColor[i].w;	// �X�y�L�������x
	}
	return lig;
}

/*!
* @brief	�A���t�@�ɖ��ߍ��ދP�x���v�Z�B
*/
float CalcLuminance(float3 color)
{
	float luminance = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f)) + g_luminance;
	if (luminance > 1.0f){
		luminance = 1.0f / luminance;
	}
	else{
		luminance = 0.0f;
	}
	return luminance;
}


float4 ShadowPixel(VS_OUTPUT In, uniform bool hasNormalMap, uniform bool hasZMask ,uniform bool isIluminance) :	COLOR{
	float3 normal;		// �@���}�b�v�ɏ������܂�Ă���@��
	if (hasNormalMap){
		normal = tex2D(g_normalMapSampler, In.uv);	// �����œ�����l��0.0����1.0(�{����-1.0����1.0�̈Ӗ��łȂ���΂Ȃ�Ȃ�)
		// -1.0�`1.0�͈̔͂ɒ�������
		normal = (normal * 2.0f) - 1.0f;

		float3 biNormal;	// �]�x�N�g��(�|���S���ɉ����x�N�g���A�O������Ԃł͎����O�K�v�Ȃ��߁A�@���Ɛڃx�N�g���Ə]�x�N�g�����g�p����)
		biNormal = normalize(cross(In.tangent, In.normal));	// �ڃx�N�g���ƃ|���S������o��@���̊O�ς����߁A�]�x�N�g�������߂�

		float4x4 TangentSpaceMatrix;	// �|���S���̃��[�J�����W(�|���S���𒆐S�Ƃ����O���̌���)���i�[�����s��
		TangentSpaceMatrix[0] = float4(In.tangent, 0.0f);	// �ڃx�N�g��
		TangentSpaceMatrix[1] = float4(biNormal, 0.0f);		// 
		TangentSpaceMatrix[2] = float4(In.normal, 0.0f);	// 
		TangentSpaceMatrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);	// 

		// �|���S���̊�ꎲ(���[���h���W���猩���|���S���̎��̌���)�Ɩ@���}�b�v���瓾���l���g���ă��[���h���W�ł̖@�������߂�
		normal = TangentSpaceMatrix[0] * normal.x + TangentSpaceMatrix[1] * normal.y + TangentSpaceMatrix[2] * normal.z;
	}
	else{
		normal = In.normal;
	}
	if (hasZMask){
		float4 screenPos = In.WorldPos;
		screenPos = mul(screenPos, View);			// �r���[���W�ɕϊ�
		screenPos = mul(screenPos, Proj);			// �v���W�F�N�V�������W�ɕϊ�
		screenPos.xyz /= screenPos.w;
		screenPos.xy *= float2(0.5f, -0.5f);			//-0.5�`0.5�͈̔͂ɂ���
		screenPos.xy += 0.5f;						//0.0�`1.0�͈̔͂���B
		float4 zmask = tex2D(g_ZMaskSampler, screenPos.xy);
		if (zmask.z > screenPos.z){
			clip(-1.0f);
		}
	}

	float4 color = tex2D(g_TextureSampler, In.uv);	// �e�N�X�`����\��t����
	// �f�B�t���[�Y���C�g�̌v�Z
	float4 light = CalcDiffuseLight(normal);
	// �X�y�L�������C�g���v�Z
	light += CalcSpeculerLight(normal, In.WorldPos);
	// �A���r�G���g���C�g�����Z
	light.xyz += ambientLight;

	color *= light;	// �e�N�X�`���̃J���[�ƃ��C�g����Z

	// �e�̕`��
	float4 ShadowPos = In.ShadowPos;
	float2 shadowMapUV = float2(0.5f, -0.5f) * ShadowPos.xy / ShadowPos.w + float2(0.5f, 0.5f);
	float4 shadow_val = float4(1.0f,1.0f,1.0f,1.0f);
	if (shadowMapUV.x <= 1.0f && shadowMapUV.x >= 0.0f){
		if (shadowMapUV.y <= 1.0f && shadowMapUV.y >= 0.0f){
			if (dot(float3(0.0f, 1.0f, 0.0f), normal) >= 0.1f){
				shadow_val = tex2D(g_ShadowMapSampler, shadowMapUV);
			}
		}
	}
	float depth = (ShadowPos.z - g_FarNear.y) / (g_FarNear.x - g_FarNear.y);

	if (depth > shadow_val.z){
		// �e�ɂȂ��Ă���
		color.xyz *= shadow_val.xyz;	// �e����������
	}

	if (isIluminance){
		// ���ɋP�x�𖄂ߍ���
		color.a = CalcLuminance(color.xyz);
	}
	else{
		color.w = Alpha;
	}
	return color;
}

// �s�N�Z���V�F�[�_
float4 TextureShader(VS_OUTPUT In, uniform bool hasNormalMap,uniform bool hasIluminance) : COLOR{
	float3 normal;		// �@���}�b�v�ɏ������܂�Ă���@��
	if (hasNormalMap){
		normal = tex2D(g_normalMapSampler, In.uv);	// �����œ�����l��0.0����1.0(�{����-1.0����1.0�̈Ӗ��łȂ���΂Ȃ�Ȃ�)
		// -1.0�`1.0�͈̔͂ɒ�������
		normal = (normal * 2.0f) - 1.0f;

		float3 biNormal;	// �]�x�N�g��(�|���S���ɉ����x�N�g���A�O������Ԃł͎����O�K�v�Ȃ��߁A�@���Ɛڃx�N�g���Ə]�x�N�g�����g�p����)
		biNormal = normalize(cross(In.tangent, In.normal));	// �ڃx�N�g���ƃ|���S������o��@���̊O�ς����߁A�]�x�N�g�������߂�

		float4x4 TangentSpaceMatrix;	// �|���S���̃��[�J�����W(�|���S���𒆐S�Ƃ����O���̌���)���i�[�����s��
		TangentSpaceMatrix[0] = float4(In.tangent, 0.0f);	// �ڃx�N�g��
		TangentSpaceMatrix[1] = float4(biNormal, 0.0f);		// 
		TangentSpaceMatrix[2] = float4(In.normal, 0.0f);	// 
		TangentSpaceMatrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);	// 

		// �|���S���̊�ꎲ(���[���h���W���猩���|���S���̎��̌���)�Ɩ@���}�b�v���瓾���l���g���ă��[���h���W�ł̖@�������߂�
		normal = TangentSpaceMatrix[0] * normal.x + TangentSpaceMatrix[1] * normal.y + TangentSpaceMatrix[2] * normal.z;
	}
	else{
		normal = In.normal;
	}
	// �f�B�t���[�Y���C�g�̌v�Z
	float4 light = CalcDiffuseLight(normal);
	// �X�y�L�������C�g���v�Z
	light += CalcSpeculerLight(normal,In.WorldPos);
	// �A���r�G���g���C�g�����Z
	light.xyz += ambientLight;

	float4 color = tex2D(g_TextureSampler, In.uv);	// �e�N�X�`����\��t����
	color *= light;	// �e�N�X�`���̃J���[�ƃ��C�g����Z
	if (hasIluminance){
		color.a = CalcLuminance(color.xyz);
	}
	else{
		color.w = Alpha;
	}
	return color;
}

float4 NoWorkingPixelShader(VS_OUTPUT In, uniform bool hasNormalMap) :COLOR{
	float3 normal;		// �@���}�b�v�ɏ������܂�Ă���@��
	if (hasNormalMap){
		normal = tex2D(g_normalMapSampler, In.uv);	// �����œ�����l��0.0����1.0(�{����-1.0����1.0�̈Ӗ��łȂ���΂Ȃ�Ȃ�)
		// -1.0�`1.0�͈̔͂ɒ�������
		normal = (normal * 2.0f) - 1.0f;

		float3 biNormal;	// �]�x�N�g��(�|���S���ɉ����x�N�g���A�O������Ԃł͎����O�K�v�Ȃ��߁A�@���Ɛڃx�N�g���Ə]�x�N�g�����g�p����)
		biNormal = normalize(cross(In.tangent, In.normal));	// �ڃx�N�g���ƃ|���S������o��@���̊O�ς����߁A�]�x�N�g�������߂�

		float4x4 TangentSpaceMatrix;	// �|���S���̃��[�J�����W(�|���S���𒆐S�Ƃ����O���̌���)���i�[�����s��
		TangentSpaceMatrix[0] = float4(In.tangent, 0.0f);	// �ڃx�N�g��
		TangentSpaceMatrix[1] = float4(biNormal, 0.0f);		// 
		TangentSpaceMatrix[2] = float4(In.normal, 0.0f);	// 
		TangentSpaceMatrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);	// 

		// �|���S���̊�ꎲ(���[���h���W���猩���|���S���̎��̌���)�Ɩ@���}�b�v���瓾���l���g���ă��[���h���W�ł̖@�������߂�
		normal = TangentSpaceMatrix[0] * normal.x + TangentSpaceMatrix[1] * normal.y + TangentSpaceMatrix[2] * normal.z;
	}
	else{
		normal = In.normal;
	}

	// �f�B�t���[�Y���C�g�̌v�Z
	float4 light = CalcDiffuseLight(normal);
	// �X�y�L�������C�g���v�Z
	light += CalcSpeculerLight(normal,In.WorldPos);
	// �A���r�G���g���C�g�����Z
	light.xyz += ambientLight;

	float4 color = In.color;	// �e�N�X�`����\��t����
	color *= light;	// �e�N�X�`���̃J���[�ƃ��C�g����Z
	color.w = Alpha;
	return color;
}

float4 FresnelShader(VS_OUTPUT In, uniform bool hasNormalMap,uniform bool hasShadow,uniform bool hasluminance) :COLOR{
	float3 normal;		// �@���}�b�v�ɏ������܂�Ă���@��
	if (hasNormalMap){
		normal = tex2D(g_normalMapSampler, In.uv);	// �����œ�����l��0.0����1.0(�{����-1.0����1.0�̈Ӗ��łȂ���΂Ȃ�Ȃ�)
		// -1.0�`1.0�͈̔͂ɒ�������
		normal = (normal * 2.0f) - 1.0f;

		float3 biNormal;	// �]�x�N�g��(�|���S���ɉ����x�N�g���A�O������Ԃł͎����O�K�v�Ȃ��߁A�@���Ɛڃx�N�g���Ə]�x�N�g�����g�p����)
		biNormal = normalize(cross(In.tangent, In.normal));	// �ڃx�N�g���ƃ|���S������o��@���̊O�ς����߁A�]�x�N�g�������߂�

		float4x4 TangentSpaceMatrix;	// �|���S���̃��[�J�����W(�|���S���𒆐S�Ƃ����O���̌���)���i�[�����s��
		TangentSpaceMatrix[0] = float4(In.tangent, 0.0f);	// �ڃx�N�g��
		TangentSpaceMatrix[1] = float4(biNormal, 0.0f);		// 
		TangentSpaceMatrix[2] = float4(In.normal, 0.0f);	// 
		TangentSpaceMatrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);	// 

		// �|���S���̊�ꎲ(���[���h���W���猩���|���S���̎��̌���)�Ɩ@���}�b�v���瓾���l���g���ă��[���h���W�ł̖@�������߂�
		normal = TangentSpaceMatrix[0] * normal.x + TangentSpaceMatrix[1] * normal.y + TangentSpaceMatrix[2] * normal.z;
	}
	else{
		normal = In.normal;
	}

	// �f�B�t���[�Y���C�g�̌v�Z
	float4 light = CalcDiffuseLight(normal);
	// �X�y�L�������C�g���v�Z
	light += CalcSpeculerLight(normal, In.WorldPos);
	// �A���r�G���g���C�g�����Z
	light.xyz += ambientLight;

	// �t�@�[���C�e�B���O���v�Z
	// �@�����J�������W�n�ɕϊ�����
	float3 normalInCamera = mul(normal, g_CameraRotaInverse);
	float fresnel = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
	fresnel = pow(fresnel, 1.5f);
	float4 color = tex2D(g_TextureSampler, In.uv);	// �e�N�X�`����\��t����
	color *= light;	// �e�N�X�`���̃J���[�ƃ��C�g����Z
	color += fresnel;
	float4 shadow_val = float4(1.0f, 1.0f, 1.0f, 1.0f);

	if (hasShadow){
		// �e�̕`��
		float4 ShadowPos = In.ShadowPos;
		float2 shadowMapUV = float2(0.5f, -0.5f) * ShadowPos.xy / ShadowPos.w + float2(0.5f, 0.5f);
		if (shadowMapUV.x <= 1.0f && shadowMapUV.x >= 0.0f){
			if (shadowMapUV.y <= 1.0f && shadowMapUV.y >= 0.0f){
				if (dot(float3(0.0f, 1.0f, 0.0f), normal) >= 0.1f){
					shadow_val = tex2D(g_ShadowMapSampler, shadowMapUV);
				}
			}
		}
		float depth = (ShadowPos.z - g_FarNear.y) / (g_FarNear.x - g_FarNear.y);

		if (depth > shadow_val.z){
			// �e�ɂȂ��Ă���
			color.xyz *= shadow_val.xyz;
		}
	}
	
	if (hasluminance){
		// ���ɋP�x�𖄂ߍ���
		color.a = CalcLuminance(color.xyz);
	}
	else{
		color.w = Alpha;
	}
	return color;
}

float4 ZMaskPsShader(VS_OUTPUT In) : COLOR {
	float4 screenPos = In.WorldPos;
	screenPos = mul(screenPos, View);			// �r���[���W�ɕϊ�
	screenPos = mul(screenPos, Proj);			// �v���W�F�N�V�������W�ɕϊ�
	return screenPos.z / screenPos.w;
}

technique ShadowTec{
	pass p0{
		VertexShader = compile vs_3_0 ShadowVertex();
		PixelShader = compile ps_3_0 ShadowPixel(true, false,false);
	}
};

technique TextureTec{
	pass p0{
		VertexShader = compile vs_3_0 BasicTransform();	// ���_�V�F�[�_
		PixelShader = compile ps_3_0 TextureShader(true,false);		// �s�N�Z���V�F�[�_
	}
};

technique BasicTec{
	pass p0{
		VertexShader = compile vs_3_0 BasicTransform();
		PixelShader = compile ps_3_0 NoWorkingPixelShader(true);
	}
};

technique NotNormalMapAnimationTec{
	pass p0{
		VertexShader = compile vs_3_0 AnimationVertex();
		PixelShader = compile ps_3_0 TextureShader(false,false);
	}
};

technique NotNormalMapShadowTec{
	pass p0{
		VertexShader = compile vs_3_0 ShadowVertex();
		PixelShader = compile ps_3_0 ShadowPixel(false, false,false);
	}
};

technique NotNormalMapTextureTec{
	pass p0{
		VertexShader = compile vs_3_0 BasicTransform();	// ���_�V�F�[�_
		PixelShader = compile ps_3_0 TextureShader(false,false);		// �s�N�Z���V�F�[�_
	}
};

technique NotNormalMapBasicTec{
	pass p0{
		VertexShader = compile vs_3_0 BasicTransform();
		PixelShader = compile ps_3_0 NoWorkingPixelShader(false);
	}
};

technique NotNormalMapAnimationFresnelTec{
	pass p0{
		VertexShader = compile vs_3_0 AnimationVertex();
		PixelShader = compile ps_3_0 FresnelShader(false,false,true);
	}
}

technique NotNormalMapNonAnimationFresnelTec{
	pass p0{
		VertexShader = compile vs_3_0 BasicTransform();
		PixelShader = compile ps_3_0 FresnelShader(false,false,false);
	}
}

technique ZMask{
	pass p0{
		VertexShader = compile vs_3_0 BasicTransform();
		PixelShader = compile ps_3_0 ZMaskPsShader();
	}
}


technique ShadowMaskTec{
	pass p0{
		VertexShader = compile vs_3_0 ShadowVertex();
		PixelShader = compile ps_3_0 ShadowPixel(true, true,false);
	}
};

technique NotNormalMapNonAnimationFresnelShadowTec{
	pass p0{
		VertexShader = compile vs_3_0 ShadowVertex();
		PixelShader = compile ps_3_0 FresnelShader(false,true,false);
	}
}

technique NotNormalMapNonAnimationBloomTec{
	pass p0{
		VertexShader = compile vs_3_0 BasicTransform();
		PixelShader = compile ps_3_0 TextureShader(false,true);
	}
}