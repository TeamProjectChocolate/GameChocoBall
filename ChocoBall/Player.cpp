#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"
#include "RenderContext.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

CPlayer::~CPlayer(){ }

void CPlayer::Initialize()
{

	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = D3DXVECTOR3(0.00f, 30.0f, -49.42f);
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Up.x = 0.0f;
	m_Up.y = 1.0f;
	m_Up.z = 0.0f;
	
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 1.0f;

	SetAlive(true);
	SetAlpha(1.0f);
	
	LockOnflag = false;
	Shotflag = false;
	Jumpflag = false;

	m_GameState = GAMEEND_ID::CONTINUE;

	m_Courcedef.Initialize();

	// ���C�g�֘A�̏�����
	this->ConfigLight();

	m_IsIntersect.CollisitionInitialize(&m_transform.position,m_radius);

	C3DImage::SetImage();

	m_lockonEnemyIndex = 0;
}

void CPlayer::Update()
{
	if (m_GameState == GAMEEND_ID::CONTINUE)
	{
		// �f�o�C�X���؂�ւ�����ꍇ�͎����Ő؂�ւ���
		SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);

		m_currentAnimNo = 0;

		// ���C�g�̍X�V
		this->UpdateLight();

		// ���C���V�[���̏�Ԃ��Ǘ����鏈��
		StateManaged();

		// �e���ˏ���
		BulletShot();

		//�Q�[���p�b�h�ł̃v���C���[�̈ړ��B
		Move();

		// �A�j���[�V�����Đ��֐����Ăяo��
		m_animation.PlayAnimation(m_currentAnimNo, 0.1f);

		//�v���C���[�̋������R�[�X��`�ɉ��������̂ɕ␳���鏈��
		BehaviorCorrection();

		//���b�N�I������
		LockOn();


		//�v���C���[�̏����̍Ō�ɂȂ�ׂ�������
		m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);

		//��]�s��
		SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_currentAngleY);

		C3DImage::Update();
	}

	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
}

void CPlayer::Draw(){
	/*IMAGE3D* img = GetImage();
	LPD3DXMESH mesh = img->pModel->GetFrameRoot()->pMeshContainer->MeshData.pMesh;
	LPDIRECT3DVERTEXBUFFER9 pVB;
	mesh->GetVertexBuffer(&pVB);
	int numVertex = mesh->GetNumVertices();
	D3DVERTEXBUFFER_DESC desc;
	pVB->GetDesc(&desc);
	int stride = desc.Size / numVertex;
	char* pData;
	pVB->Lock(0, 0, (void**)&pData, D3DLOCK_DISCARD);
	float YMax, YMin;
	YMax = -FLT_MAX;
	YMin = FLT_MAX;
	for (int i = 0; i < numVertex; i++){
	float* pos = (float*)pData;
	YMax = max(YMax, pos[1]);
	YMin = Minx(YMin, pos[1]);
	pData += stride;
	}
	float size = YMax + fabsf(YMin);
	float center = (YMax + YMin)*0.5f;
	pVB->Unlock();*/

	SetUpTechnique();
	C3DImage::Draw();
}

void CPlayer::UpdateLight(){
	this->SetUpLight();
}

void CPlayer::ConfigLight(){
	// �f�B�t���[�Y���C�g(�L�������C�g)�̌����ݒ�(���C�g1�`4)
	m_lightDir[0] = D3DXVECTOR3(0.707f, 0.707f, 0.0f);
	m_lightDir[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_lightDir[2] = D3DXVECTOR3(1.0f, -1.0f, 0.5f);
	m_lightDir[3] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// �f�B�t���[�Y���C�g(�L�������C�g)�̐F�ݒ�(���C�g1�`4)
	m_lightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_lightColor[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_lightColor[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_lightColor[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	// �A���r�G���g���C�g(����)�̋����ݒ�
	D3DXVECTOR4 ambientLight;
	ambientLight = D3DXVECTOR4(0.2f, 0.0f, 0.0f, 100.0f);

	// ���C�g�̐ݒ�𔽉f
	ReflectionLight(ambientLight);
}

void CPlayer::ReflectionLight(D3DXVECTOR4 ambient){
	this->SetUpLight();
	m_light.SetAmbientLight(ambient);
}

void CPlayer::SetUpLight(){
	for (short num = 0; num < NUM_DIFFUSE_LIGHT; num++){
		D3DXVECTOR4 dir;
		dir.x = m_lightDir[num].x;
		dir.y = m_lightDir[num].y;
		dir.z = m_lightDir[num].z;
		dir.w = 1.0f;
		m_light.SetDiffuseLightDirection(num, dir);
		m_light.SetDiffuseLightColor(num, m_lightColor[num]);
	}
	SINSTANCE(CRenderContext)->SetCurrentLight(&m_light);
}

void CPlayer::Move()
{
	isTurn = false;

	//���n���Ă���̂Ńt���O��false
	if (m_transform.position.y <= -0.7f)
	{
		Jumpflag = false;
	}
	if (m_pInput->IsTriggerSpace() && Jumpflag == false)
	{
		m_moveSpeed.y = 20.0f;
		Jumpflag = true;
	}


	float X = m_pInput->GetStickL_XFloat();
	float Y = m_pInput->GetStickL_YFloat();

	//�O��̓���
	if (fabs(Y) > 0.0f)
	{
		if (Jumpflag == false)
		{
			//m_transform.position.z = MOVE_SPEED;
			m_moveSpeed.z = Y * MOVE_SPEED;
			isTurn = true;
			m_currentAnimNo = 1;
		}
	}

	//���E�̓���
	if (fabsf(X) > 0.0f)
	{
		if (Jumpflag == false)
		{
			//m_transform.position.z = MOVE_SPEED;
			m_moveSpeed.x = X * MOVE_SPEED;
			isTurn = true;
			m_currentAnimNo = 1;
		}
	}

	if (fabsf(X) <= 0.0001f){
		if (Jumpflag == false)
		{
			m_moveSpeed.x = 0.0f;
		}
	}
	if (fabsf(Y) <= 0.0001f){
		if (Jumpflag == false)
		{
			m_moveSpeed.z = 0.0f;
		}
	}

	if (Jumpflag == false)
	{
		//D3DXToRadian�̒l�͊e���Őݒ肷��B ��@����D3DXToRadian(0.0f)
		//isTurn��Update�̍ŏ���false�ɂ��āA��]������������true�ɂ���B
		m_currentAngleY = m_Turn.Update(isTurn, m_targetAngleY);
	}
}

void CPlayer::LockOn()
{
	float _X = 0.0f;

	//���b�N�I����Ԃɂ���B
	if (m_pInput->IsTriggerLeftShift() && LockOnflag == false)
	{
		LockOnflag = true;
		m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
	}
	//���b�N�I����Ԃ̉���
	else if (m_pInput->IsTriggerLeftShift() && LockOnflag == true)
	{
		LockOnflag = false;
	}
	//���b�N�I����Ԓ��̉�]�̌v�Z
	if (LockOnflag)
	{
		_X = m_LockOn.LockOnRotation(_X, m_transform.position, m_lockonEnemyIndex);
	}
	//���b�N�I����Ԃ̎��ɏ�Ƀv���C���[��G�Ɍ�������
	if (LockOnflag){
		m_targetAngleY = _X;
	}

}

void CPlayer::BehaviorCorrection()
{
	//���s����x�N�g�������߂�B
	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_transform.position);
	m_V1 = Cource.endPosition - Cource.startPosition;
	D3DXVec3Normalize(&V1, &m_V1);//3D �x�N�g���𐳋K�������x�N�g����Ԃ��B
	D3DXVec3Cross(&m_V2, &V1, &m_Up);//2��3D�x�N�g���̏�����̊O�ς����߂遨���s����V2��������B
	D3DXVec3Normalize(&V2, &m_V2);

	//m_V3 = V1 + V2;
	//V3 = D3DXVec3Length(&m_V3);

	//�R�[�X��`�ɂ��������ăv���C���[�̐i�s�����ƋȂ�������w��
	if (!Jumpflag){
		D3DXVECTOR3 t0, t1;
		t0 = V1 * m_moveSpeed.z;
		t1 = V2 * -m_moveSpeed.x;
		t0 += t1;
		m_moveSpeed.x = t0.x;
		m_moveSpeed.z = t0.z;
	}
	//m_moveSpeed.x = m_moveSpeed.x * -m_V3.x;
	//m_moveSpeed.z = m_moveSpeed.z * m_V3.z;


	//�R�[�X��`�ɏ]�����v���C���[�̉�]�̏���
	float L;
	D3DXVECTOR3		NV2;
	float			cos;
	D3DXVECTOR3		Back;
	D3DXVECTOR3     NV3;
	Back.x = 0.0f;
	Back.y = 0.0f;
	Back.z = -1.0f;

	D3DXVECTOR3 moveXZ = m_moveSpeed;
	moveXZ.y = 0.0f;
	L = D3DXVec3Length(&moveXZ);//m_moveSpeed�̃x�N�g���̑傫����Ԃ��A��̌v�Z�����Ă����B
	if (L > 0)
	{
		D3DXVec3Normalize(&NV2, &moveXZ);
		D3DXVec3Cross(&NV3, &NV2, &Back);
		cos = D3DXVec3Dot(&NV2, &Back);///2��3D�x�N�g���̏�����̓��ς����߂遨V1��V2�̂Ȃ��p��cos�Ƃ�������B
		m_targetAngleY = acos(cos);
		if (NV3.y > 0)
		{
			m_targetAngleY = m_targetAngleY*-1;
		}
	}

}

void CPlayer::StateManaged()
{
	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
	m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
	CEnemy* Enemy = EnemyManager->GetEnemy(m_lockonEnemyIndex);
	D3DXVECTOR3 dist;
	dist = Enemy->GetPos() - m_transform.position;
	float R;
	R = D3DXVec3Length(&dist);//�x�N�g���̒������v�Z

	if (R <= 1)
	{
		m_GameState = GAMEEND_ID::OVER;
		return;
	}

	//�Q�[���I�[�o�[����
	if (m_transform.position.y <= -10.0f)
	{
		m_GameState = GAMEEND_ID::OVER;
		return;
	}

	//�Q�[���N���A
	D3DXVECTOR3 Endposition;
	Endposition = m_Courcedef.EndCource();
	if (Endposition.x - 0.5 < m_transform.position.x&&Endposition.z - 10 < m_transform.position.z)
	{
		m_GameState = GAMEEND_ID::CLEAR;
		return;
	}
}

void CPlayer::BulletShot()
{
	if (m_pInput->IsTriggerRightShift())
	{
		Shotflag = true;
	}
	else if (m_pInput->IsTriggerDecsion() && Shotflag == true)
	{
		Shotflag = false;
	}

}