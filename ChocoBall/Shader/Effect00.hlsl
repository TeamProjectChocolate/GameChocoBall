
float4x4 World;	// ���[���h�ϊ��s��錾
float4x4 View;	// �r���[�ϊ��s��錾
float4x4 Proj;	// �ˉe�ϊ��s��錾

texture g_Texture;			// �e�N�X�`��
sampler g_TextureSampler = 
sampler_state{
	Texture = g_Texture;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

// ���_�����͗p�\����
struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2  uv		: TEXCOORD0;	// ���_�ɓ\��ׂ��e�N�X�`���̃A�h���X�H
};

// ���_���o�͗p�\����
struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2  uv		: TEXCOORD0;
};

// ���_�V�F�[�_
VS_OUTPUT BasicTransform(VS_INPUT In /*���_���(���[�J�����W*/)
{

	//�����ł��낢�뎩�R�ɐG������A���W�ϊ����s�����肷��B

	VS_OUTPUT Screen;
	float4 pos;
	pos = mul(In.pos, World);	// ���[���h���W�ɕϊ�
	pos = mul(pos, View);			// �r���[���W�ɕϊ�
	pos = mul(pos, Proj);			// �v���W�F�N�V�������W�ɕϊ�
	Screen.pos = pos;
	Screen.color = In.color;
	Screen.uv = In.uv;
	return Screen;	// ���_���(�X�N���[�����W)���X�N���[�����W��Ԃ��Ȃ���΃G���[�ƂȂ��Ă��܂��B
};

// �s�N�Z���V�F�[�_
float4 TextureShader(VS_OUTPUT In) : COLOR{
	return tex2D(g_TextureSampler,In.uv);	// �e�N�X�`����\��t����
};

float4 NoWorkingPixelShader(VS_OUTPUT In) :COLOR{
	return In.color;
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