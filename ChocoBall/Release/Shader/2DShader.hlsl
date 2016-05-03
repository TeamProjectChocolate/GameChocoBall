
float4x4 World;	// ���[���h�ϊ��s��錾

texture g_Texture;			// �e�N�X�`��
sampler g_TextureSampler =
sampler_state{
	Texture = g_Texture;
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
VS_OUTPUT vs_main(VS_INPUT In /*���_���(���[�J�����W*/)
{

	//�����ł��낢�뎩�R�ɐG������A���W�ϊ����s�����肷��B

	VS_OUTPUT Screen;
	float4 pos;
	pos = mul(In.pos, World);	// ���[���h���W�ɕϊ�
	Screen.pos = pos;
	Screen.color = In.color;
	Screen.uv = In.uv;
	return Screen;	// ���_���(�X�N���[�����W)���X�N���[�����W��Ԃ��Ȃ���΃G���[�ƂȂ��Ă��܂��B
};

// �s�N�Z���V�F�[�_
float4 ps_main(VS_OUTPUT In) : COLOR0{
	return tex2D(g_TextureSampler, In.uv) * In.color;	// �e�N�X�`����\��t����
};

technique BasicTec{
	pass p0{
		VertexShader = compile vs_2_0 vs_main();	// ���_�V�F�[�_
		PixelShader = compile ps_2_0 ps_main();		// �s�N�Z���V�F�[�_
	}
}