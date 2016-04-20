
float4x4 World;	// ���[���h�ϊ��s��錾
float4x4 View;	// �r���[�ϊ��s��錾
float4x4 Proj;	// �ˉe�ϊ��s��錾

texture g_Texture;			// �e�N�X�`��

// ���͗p�\����
struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
};

// �o�͗p�\����
struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
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
	return Screen;	// ���_���(�X�N���[�����W)���X�N���[�����W��Ԃ��Ȃ���΃G���[�ƂȂ��Ă��܂��B
};

// �s�N�Z���V�F�[�_
float4 NoWorkingPixelShader(VS_OUTPUT In) : COLOR{
	return In.color;	// �ŏI�I�ȃs�N�Z���̐F�ƃe�N�X�`���̍��W��Ԃ��B
};

technique BasicTec{
	pass p0{
		VertexShader = compile vs_2_0 BasicTransform();	// ���_�V�F�[�_
		PixelShader = compile ps_2_0 NoWorkingPixelShader();		// �s�N�Z���V�F�[�_
	}
};