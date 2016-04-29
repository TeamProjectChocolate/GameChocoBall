#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"
#include "GraphicsDevice.h"

HRESULT C3DImage::SetImage(){
	IMAGE3D* Image = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (Image != nullptr){
		m_NumMaterials = Image->NumMaterials;
		m_pMeshMat = Image->pMat;
		m_pMeshTex = Image->ppTex;
		m_pMesh = Image->pMesh;
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::ReSet(){
	IMAGE3D* Image = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (Image != nullptr){
		m_NumMaterials = Image->NumMaterials;
		m_pMeshMat = Image->pMat;
		m_pMeshTex = Image->ppTex;
		m_pMesh = Image->pMesh;
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::LoadXFile(){
	DWORD i;

	// X�t�@�C�����[�h
	if (FAILED(D3DXLoadMeshFromX(m_pFileName, D3DXMESH_MANAGED, graphicsDevice(), NULL, &m_pMaterials, NULL, &m_NumMaterials, &m_pMesh))){		// X�t�@�C���ǂݎ��
		return E_FAIL;
	};

	// X�t�@�C���ɖ@�����Ȃ��ꍇ�́A�@������������
	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL)){
		ID3DXMesh* pTempMesh = NULL;
		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF() | D3DFVF_NORMAL, graphicsDevice(), &pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	// �}�e���A���A�e�N�X�`���̏���
	m_pMeshMat = new D3DMATERIAL9[m_NumMaterials];		// ���b�V�������m��
	m_pMeshTex = new LPDIRECT3DTEXTURE9[m_NumMaterials];		// �e�N�X�`�����m��

	D3DXMATERIAL* d3Mat = (D3DXMATERIAL*)m_pMaterials->GetBufferPointer();

	for (i = 0; i < m_NumMaterials; i++){
		m_pMeshMat[i] = d3Mat[i].MatD3D;		// �}�e���A�����Z�b�g
		m_pMeshMat[i].Ambient = m_pMeshMat[i].Diffuse;		// ����������

		m_pMeshTex[i] = NULL;		// �e�N�X�`��������
		if (d3Mat[i].pTextureFilename != NULL && lstrlen(d3Mat[i].pTextureFilename) > 0){		// �g�p���Ă���e�N�X�`��������Γǂݍ���

			if (FAILED(D3DXCreateTextureFromFile(graphicsDevice(), d3Mat[i].pTextureFilename, &m_pMeshTex[i]))){
				return E_FAIL;
			}
		}
	}

	SINSTANCE(CImageManager)->Add3D(m_pFileName, m_pMeshMat, m_pMeshTex, m_NumMaterials, m_pMesh);		// IMAGE���z��ɒǉ�
	m_pMaterials->Release();		// �}�e���A�������
	return S_OK;
}

void C3DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// �g�p����shader�t�@�C�����w��(�f�t�H���g)


	//// �����_�����O�^�[�Q�b�g�����H
	//(*graphicsDevice()).CreateDepthStencilSurface(WINDOW_WIDTH, WINDOW_HEIGHT, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pMapZ, NULL);
	//(*graphicsDevice()).CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pShadow, NULL);
	//m_pShadow->GetSurfaceLevel(0, &m_pOriginalSurf);


	m_lightDir[0] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_lightDir[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_lightDir[2] = D3DXVECTOR3(1.0f, -1.0f, 0.5f);
	m_lightDir[3] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(m_lightDir[0].x, m_lightDir[0].y, m_lightDir[0].z, 0.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(m_lightDir[1].x, m_lightDir[1].y, m_lightDir[1].z, 0.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(m_lightDir[2].x, m_lightDir[2].y, m_lightDir[2].z, 0.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(m_lightDir[3].x, m_lightDir[3].y, m_lightDir[3].z, 0.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.2f, 0.0f, 0.0f,100.0f));

	count = 0;
	dir = D3DXVECTOR3(1,1,1);
}

void C3DImage::Update(){
	if (m_lightDir[0].x > 1.0f){
		dir.x *= -1;
	}
	else if (m_lightDir[0].x < -1.0f){
		dir.x *= -1;
	}
	m_lightDir[0].x += 0.1f * dir.x;

	if (m_lightDir[0].y > 1.0f){
		dir.y *= -1;
	}
	else if (m_lightDir[0].y < -1.0f){
		dir.y *= -1;
	}
	m_lightDir[0].y += 0.1f * dir.y;

	if (m_lightDir[0].z > 1.0f){
		dir.z *= -1;
	}
	else if (m_lightDir[0].z < -1.0f){
		dir.z *= -1;
	}
	m_lightDir[0].z += 0.1f * dir.z;

	if (count % 60 == 0){
		D3DXVECTOR3 work = m_lightDir[0];
		m_lightDir[0] = m_lightDir[1];
		m_lightDir[1] = m_lightDir[2];
		m_lightDir[2] = m_lightDir[3];
		m_lightDir[3] = work;
		count = 0;
	}

	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(m_lightDir[0].x, m_lightDir[0].y, m_lightDir[0].z, 0.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(m_lightDir[1].x, m_lightDir[1].y, m_lightDir[1].z, 0.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(m_lightDir[2].x, m_lightDir[2].y, m_lightDir[2].z, 0.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(m_lightDir[3].x, m_lightDir[3].y, m_lightDir[3].z, 0.0f));

	count++;
}

void C3DImage::Draw(){

	D3DXMATRIX Trans;	// �ړ��s��
	D3DXMATRIX Rota;	// ��]�s��
	D3DXMATRIX Scale;	// �g��E�k���s��

	D3DXMatrixIdentity(&mWorld);	// �s�񏉊���

	D3DXMatrixScaling(&Scale, m_transform.scale.x, m_transform.scale.y, m_transform.scale.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Scale);

	D3DXMatrixRotationX(&Rota, m_transform.angle.x);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Rota);

	D3DXMatrixRotationY(&Rota, m_transform.angle.y);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Rota);

	D3DXMatrixRotationZ(&Rota, m_transform.angle.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Rota);

	Rota = mWorld;

	D3DXMatrixTranslation(&Trans, m_transform.position.x, m_transform.position.y, m_transform.position.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Trans);

//
//	// ���Ƃ̃����_�����O�^�[�Q�b�g��ۑ�
//	IDirect3DSurface9* pOldBackBuffer;
//	IDirect3DSurface9* pOldZBuffer;
//
//	(*graphicsDevice()).GetRenderTarget(0, &pOldBackBuffer);
//	(*graphicsDevice()).GetDepthStencilSurface(&pOldZBuffer);
//
//	// �����_�����O�^�[�Q�b�g�̕ύX
//	(*graphicsDevice()).SetRenderTarget(0, m_pOriginalSurf);
//	(*graphicsDevice()).SetDepthStencilSurface(m_pMapZ);
//
//	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
//
//	// �I�t�X�N���[�������_�����O
////m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ShadowMap.hlsl"));	// �g�p����shader�t�@�C�����V���h�E�}�b�v�p�ɕύX
//	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// �g�p����shader�t�@�C�����V���h�E�}�b�v�p�ɕύX
//
//	SetUpTechnique();
//	//m_pEffect->SetTechnique("ShadowMapping");
//	if (m_pEffect == nullptr){
//		m_pEffect->SetTechnique("BasicTec");
//	}
//	m_pEffect->Begin(NULL, 0);
//	m_pEffect->BeginPass(0);
//	//m_pEffect->SetTexture("g_ShadowMap", m_pShadow);
//	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
//	m_pEffect->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &mWorld/*�ݒ肵�����s��ւ̃|�C���^*/);
//	// ���_�t�H�[�}�b�g���Z�b�g
//	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());
//
//	
//	for (DWORD i = 0; i < m_NumMaterials; i++){
//		m_pEffect->SetTexture("g_Texture", m_pMeshTex[i]);	// �e�N�X�`�������Z�b�g
//		m_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B
//		m_pMesh->DrawSubset(i);						// ���b�V����`��
//	}
//	m_pEffect->EndPass();
//	m_pEffect->End();
//	// �����_�����O�^�[�Q�b�g�����ɖ߂�
//	(*graphicsDevice()).SetRenderTarget(0, pOldBackBuffer);
//	(*graphicsDevice()).SetDepthStencilSurface(pOldZBuffer);
//	//pOldBackBuffer->Release();
//	//pOldZBuffer->Release();
//	

	// �ʏ�`��
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// �g�p����shader�t�@�C�����w��(�f�t�H���g)
	SetUpTechnique();
	if (m_pMeshTex[0] == nullptr){
		m_pEffect->SetTechnique("BasicTec");
	}

	UINT numPass;
	m_pEffect->Begin(&numPass/*�e�N�j�b�N���ɒ�`����Ă���p�X�̐����ԋp�����*/, 0);
	m_pEffect->BeginPass(0);	//�p�X�̔ԍ����w�肵�Ăǂ̃p�X���g�p���邩�w��

	// ���݂̃v���W�F�N�V�����s��ƃr���[�s����V�F�[�_�[�ɓ]��
	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);

	// �f�B�t���[�Y���C�g�̌������V�F�[�_�[�ɓ]��
	m_pEffect->SetVectorArray("diffuseLightDirection", m_light.GetDiffuseLightDirection(), NUM_DIFFUSE_LIGHT);
	// �f�B�t���[�Y���C�g�̃J���[���V�F�[�_�[�ɓ]��
	m_pEffect->SetVectorArray("diffuseLightColor", m_light.GetDiffuseLightColor(), NUM_DIFFUSE_LIGHT);
	// �������V�F�[�_�[�ɓ]��
	m_pEffect->SetVector("ambientLight", &m_light.GetAmbientLight());
	// ���_���V�F�[�_�[�ɓ]��
	m_pEffect->SetVector("EyePosition", reinterpret_cast<D3DXVECTOR4*>(&SINSTANCE(CRenderContext)->GetCurrentCamera()->GetPos()));

	//�����ŌŒ�`��Ɠ����悤�ɁA���[�J�����W�ɐݒ肳�ꂽ���_�Q���f�o�C�X�ɓn���B�ʏ�Ɠ������@�B
	//	���b�V�����������A�}�e���A����e�N�X�`����ݒ�
	//DrawSubset()���Ăяo���ĕ`��

	// ���[���h�g�����X�t�H�[��(��΍��W�ϊ�)
	// ���[���h�s�񐶐�


	m_pEffect->SetMatrix("Rota", &Rota);
	m_pEffect->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &mWorld/*�ݒ肵�����s��ւ̃|�C���^*/);

	// ���_�t�H�[�}�b�g���Z�b�g
	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());

	for (DWORD i = 0; i < m_NumMaterials; i++){
		//m_pEffect->SetTexture("g_Texture", m_pShadow);	// �e�N�X�`�������Z�b�g
		m_pEffect->SetTexture("g_Texture", m_pMeshTex[i]);	// �e�N�X�`�������Z�b�g
		m_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B
		m_pMesh->DrawSubset(i);						// ���b�V����`��
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}