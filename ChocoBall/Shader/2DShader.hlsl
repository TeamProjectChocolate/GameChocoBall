
float4x4 World;	// ���[���h�ϊ��s��錾
float Alpha;	// �����x
int Split_X;	// �摜������(��)
int Split_Y;	// �摜������(�c)
int NowCol;		// ���R�}��(��)
int NowRow;		// ���R�}��(�c)
float Ratio_X;	// ���̉摜�T�C�Y���琶�����ꂽ�摜�T�C�Y���������䗦(��)
float Ratio_Y;	// ���̉摜�T�C�Y���琶�����ꂽ�摜�T�C�Y���������䗦(�c)
float g_brightness;

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
VS_OUTPUT vs_main(VS_INPUT In /*���_���(���[�J�����W*/)
{

	//�����ł��낢�뎩�R�ɐG������A���W�ϊ����s�����肷��B

	VS_OUTPUT Screen;
	float4 pos;
	pos = mul(In.pos, World);	// ���[���h���W�ɕϊ�
	Screen.pos = pos;
	Screen.color = In.color;
	float2 uv = In.uv;
	uv.x *= 1.0f / Split_X;
	uv.x *= Ratio_X;
	uv.x += ((float)NowCol / Split_X) * Ratio_X;
	uv.y *= 1.0f / Split_Y;
	uv.y *= Ratio_Y;
	uv.y += ((float)NowRow / Split_Y) * Ratio_Y;

	Screen.uv = uv;
	return Screen;	// ���_���(�X�N���[�����W)���X�N���[�����W��Ԃ��Ȃ���΃G���[�ƂȂ��Ă��܂��B
};

// �s�N�Z���V�F�[�_
float4 ps_main(VS_OUTPUT In) : COLOR0{
	In.color = (float4)0.0f;
	float4 color = tex2D(g_TextureSampler, In.uv);
	color.w *= Alpha;
	return color;	// �e�N�X�`����\��t����
};

float4 ps_mainAdd(VS_OUTPUT In) :COLOR{
	In.color = (float4)0.0f;
	float4 color = tex2D(g_TextureSampler, In.uv);
	color.xyz *= color.a * Alpha;
	return float4(color.xyz,color.w * 1.0f / g_brightness);
};

technique BasicTec{
	pass p0{
		VertexShader = compile vs_2_0 vs_main();	// ���_�V�F�[�_
		PixelShader = compile ps_2_0 ps_main();		// �s�N�Z���V�F�[�_
	}
}

// ���Z�����p�e�N�j�b�N
technique ColorTexPrimAdd{
	pass p0{
		VertexShader = compile vs_2_0 vs_main();	// ���_�V�F�[�_
		PixelShader = compile ps_2_0 ps_mainAdd();		// �s�N�Z���V�F�[�_
	}
}