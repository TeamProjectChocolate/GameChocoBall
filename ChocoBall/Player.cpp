#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"
#include "RenderContext.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "PlayerParam.h"
#include "ParticleEmitter.h"
#include "MoveFloor.h"
#include "StageTable.h"

CPlayer* g_player = NULL;
CPlayer::~CPlayer(){  }

void CPlayer::Initialize()

{
	parent = NULL;
	g_player = this;
	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = PlayerTransformArray[m_StageID].pos;
	m_transform.angle = PlayerTransformArray[m_StageID].rotation;
	m_transform.scale = PlayerTransformArray[m_StageID].scale;

	// Unity����o�͂����|�W�V���������œK��
	m_transform.position.x *= -1.0f;
	m_transform.position.z *= -1.0f;

	RV0 = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	localPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 1.0f;

	deadTimer = 0.0f;

	SetAlive(true);
	SetAlpha(1.0f);
	
	LockOnflag = false;
	Shotflag = false;
	Jumpflag = false;
	ChocoBall = false;
	
	GamaOverFlag = false;
	BusterEnemyNum = 0;
	m_size.x = 1.0f;
	m_size.y = 2.0f;
	m_size.z = 1.0f;

	m_GameState = GAMEEND_ID::CONTINUE;

	m_Courcedef.SetStageID(m_StageID);
	m_Courcedef.Initialize();

	// ���C�g�֘A�̏�����
	this->ConfigLight();
	
	m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);
	
	m_CBManager =NULL;

	C3DImage::SetImage();

	deadTimer = 0.0f;
	m_lockonEnemyIndex = 0;	
	m_pEmitter = CParticleEmitter::EmitterCreate(
		_T("ParticleEmitterTEST"),
		PARTICLE_TYPE::FIRE,
		m_transform.position,
		SINSTANCE(CObjectManager)->FindGameObject<CCourceCamera>(_T("Camera"))->GetCamera()
	);
	CParticleEmitter::EmitterCreate(
		_T("ParticleEmitterPORIGON"),
		PARTICLE_TYPE::PORIGON,
		m_transform.position,
		SINSTANCE(CObjectManager)->FindGameObject<CCourceCamera>(_T("Camera"))->GetCamera()
		);

}

void CPlayer::SetParent(MoveFloor* parent)
{
	//�e���ݒ肳�ꂽ�̂ŁA���[���h���W�����߂邽�߂ɁB��UUpdate���Ăяo���B
	
	if (parent != NULL){
		//�e���ݒ肳�ꂽ�̂ŁA���[�J�����W��e�̃��[�J�����W�ɕϊ�����B
		D3DXMATRIX mParentWorldInv = parent->GetWorldMatrix();
		D3DXMatrixInverse(&mParentWorldInv, NULL, &mParentWorldInv);
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &m_transform.position, &mParentWorldInv);
		localPosition.x = pos.x;
		localPosition.y = pos.y;
		localPosition.z = pos.z;
		this->parent = parent;
	}
	else if (this->parent != NULL){
		
		D3DXMATRIX mParentWorld = this->parent->GetWorldMatrix();
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &localPosition, &mParentWorld);
		localPosition.x = pos.x;
		localPosition.y = pos.y;
		localPosition.z = pos.z;

		m_transform.position.x = pos.x;
		m_transform.position.y = pos.y;
		m_transform.position.z = pos.z;
		this->parent = parent;
	}
}

void CPlayer::Update()
{
	if (m_GameState == GAMEEND_ID::CONTINUE)
	{
		//�e������Ƃ��̏���
		if (parent)
		{
			D3DXMATRIX mParentWorld = parent->GetWorldMatrix();
			//�e�̃��[���h�s�����Z���āA���[�J�����W�����[���h���W�ɕϊ�����

			D3DXVECTOR4 pos;
			D3DXVec3Transform(&pos, &localPosition, &mParentWorld);
			m_transform.position.x = pos.x + parent->GetMoveSpeed().x;
			m_transform.position.y = pos.y + parent->GetMoveSpeed().y;
			m_transform.position.z = pos.z + parent->GetMoveSpeed().z;
		}
		
		// �f�o�C�X���؂�ւ�����ꍇ�͎����Ő؂�ւ���
		SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);

		m_currentAnimNo = 0;		

		// ���C�g�̍X�V
		this->UpdateLight();

		// ���C���V�[���̏�Ԃ��Ǘ����鏈��
		StateManaged();

		//�Q�[���p�b�h�ł̃v���C���[�̈ړ��B
		Move();

		// �A�j���[�V�����Đ��֐����Ăяo��
		m_animation.PlayAnimation(m_currentAnimNo, 0.1f);

		//�v���C���[�̋������R�[�X��`�ɉ��������̂ɕ␳���鏈��
		BehaviorCorrection();

		//���b�N�I������
		LockOn();

		if (m_CBManager != NULL)
		{
			//�`���R�{�[���ɓ������Ă��邩�̏���
			if (m_HitFlag = m_CBManager->IsHit(m_transform.position, m_size))
			{
				//�`���R�{�[���ɓ���������̏���
				ChocoHit();
			}
		}

		if (GamaOverFlag==false)//�Q�[���I�[�o�[�ɂȂ��Ă��Ȃ����̏���
		{
			
			//�v���C���[�̏����̍Ō�ɂȂ�ׂ�������
			m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);

			//���n���Ă���̂Ńt���O��false
			if (m_IsIntersect.IsHitGround())
			{
				Jumpflag = false;
			}

			// �e���ˏ���
			BulletShot();

			//��]�s��
			SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_currentAngleY);
		}
		else if (GamaOverFlag == true)
		{
			//�Q�[���I�[�o�[��Ԃł̃`���R�{�[���ɗ�����鏈��
			RollingPlayer();

		}
		C3DImage::Update();

		// �����̎��͂Ƀp�[�e�B�N������
		m_pEmitter->SetEmitPos(m_transform.position);
	}

	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		m_bullets[idx]->Update();
	}
}

void CPlayer::Draw(){
	
	SetUpTechnique();
	C3DImage::Draw();

	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		m_bullets[idx]->Draw();
	}

	// ��΂ɂ����ŌĂׂ�I�@��΂������I�H
	ExcuteDeleteBullets();
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


	if (m_pInput->IsTriggerSpace() && Jumpflag == false)
	{
		m_moveSpeed.y = PLAYER_JUMP_POWER;
		Jumpflag = true;
	}

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	float X = m_pInput->GetStickL_XFloat();
	float Y = m_pInput->GetStickL_YFloat();

	//�O��̓���
	if (fabs(Y) > 0.0f)
	{

		m_moveSpeed.z = Y * MOVE_SPEED;
		isTurn = true;
		m_currentAnimNo = 1;
	}

	//���E�̓���
	if (fabsf(X) > 0.0f)
	{
		m_moveSpeed.x = X * MOVE_SPEED;
		isTurn = true;
		m_currentAnimNo = 1;
	}
	//D3DXToRadian�̒l�͊e���Őݒ肷��B ��@����D3DXToRadian(0.0f)
	//isTurn��Update�̍ŏ���false�ɂ��āA��]������������true�ɂ���B
	m_currentAngleY = m_Turn.Update(isTurn, m_targetAngleY);
}

void CPlayer::LockOn()
{
	float _X = 0.0f;

	//���b�N�I����Ԃɂ���B
	if (m_pInput->IsTriggerLeftShift() && LockOnflag == false)
	{
		m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
		if (m_lockonEnemyIndex != -1){
			LockOnflag = true;
		}
		
	}
	//���b�N�I����Ԃ̉���
	else if (m_pInput->IsTriggerLeftShift() && LockOnflag == true)
	{
		LockOnflag = false;
	}
	//���b�N�I����Ԓ��̉�]�̌v�Z
	if (LockOnflag)
	{
		if (m_lockonEnemyIndex == -1){
			LockOnflag = false;
		}
		else{
			_X = m_LockOn.LockOnRotation(_X, m_transform.position, m_lockonEnemyIndex);
		}
	}
	//���b�N�I����Ԃ̎��ɏ�Ƀv���C���[��G�Ɍ�������
	if (LockOnflag){
		m_targetAngleY = _X;
	}

}

void CPlayer::BehaviorCorrection()
{
	D3DXVECTOR3		V1;
	D3DXVECTOR3		V2;
	D3DXVECTOR3		Up;

	Up.x = 0.0f;
	Up.y = 1.0f;
	Up.z = 0.0f;

	//���s����x�N�g�������߂�B
	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_transform.position);
	V1 = Cource.endPosition - Cource.startPosition;
	D3DXVec3Normalize(&V1, &V1);//3D �x�N�g���𐳋K�������x�N�g����Ԃ��B
	D3DXVec3Cross(&V2, &V1,&Up);//2��3D�x�N�g���̏�����̊O�ς����߂遨���s����V2��������B
	D3DXVec3Normalize(&V2, &V2);

	//�R�[�X��`�ɂ��������ăv���C���[�̐i�s�����ƋȂ�������w��
	D3DXVECTOR3 t0, t1;
	t0 = V1 * m_moveSpeed.z;
	t1 = V2 * -m_moveSpeed.x;
	t0 += t1;
	m_moveSpeed.x = t0.x;
	m_moveSpeed.z = t0.z;

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
	if (m_lockonEnemyIndex != -1){
		EnemyBase* Enemy = EnemyManager->GetEnemy(m_lockonEnemyIndex);
		D3DXVECTOR3 dist;
		dist = Enemy->GetPos() - m_transform.position;
		float R;
		R = D3DXVec3Length(&dist);//�x�N�g���̒������v�Z

		if (R <= 1)
		{
			m_GameState = GAMEEND_ID::OVER;
			return;
		}
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
	D3DXVECTOR3 StageEndPosition;
	StageEndPosition = Endposition - m_transform.position;
	float Kyori = D3DXVec3Length(&StageEndPosition);
	if (Kyori < 2)
	{
		m_GameState = GAMEEND_ID::CLEAR;
		return;
	}
}

void CPlayer::BulletShot()
{
	if (m_pInput->IsTriggerRightShift())
	{

		//�v���C���[�̌����Ă���x�N�g�����v�Z
		D3DXVec3Normalize(&RV0, &RV0);
		D3DXMatrixRotationY(&Rot, m_currentAngleY);
		D3DXVec3Transform(&RV1, &RV0, &Rot);


		Bullet* bullet = new Bullet;
		bullet->Initialize();
		bullet->SetPos(m_transform.position);
		bullet->SetDir(RV1);
		bullet->SetBulletSpeed(3.0f);
		m_bullets.push_back(bullet);
	}

	//�v���C���[�ƒe�̋�����20m�ɂȂ�ƒe��������Delete����B
	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		D3DXVECTOR3 V5;
		V5 = m_bullets[idx]->GetPos() - m_transform.position;
		float length = D3DXVec3Length(&V5);
		length = fabs(length);
		if (length > BULLET_LENG)
		{
			DeleteBullet(m_bullets[idx]);
		}
	}
}

void CPlayer::DeleteBullet(Bullet* bullet){
	m_Deletebullets.push_back(bullet);
}

void CPlayer::ExcuteDeleteBullets(){
	vector<Bullet*>::iterator itr;
	int size = m_Deletebullets.size();
	for (int idx = 0; idx < size; idx++){
		for (itr = m_bullets.begin(); itr != m_bullets.end();){
			if (m_Deletebullets[idx] == *itr){
				SAFE_DELETE(*itr);
				itr = m_bullets.erase(itr);
				break;
			}
			else{
				itr++;
			}
		}
	}
	m_Deletebullets.clear();
}

void CPlayer::ChocoHit()
{
	GamaOverFlag = true;
	btRigidBody* rb = m_IsIntersect.GetRigidBody();//�v���C���[�̍��̂��擾
	m_IsIntersect.GetSphereShape()->setLocalScaling(btVector3(0.3f, 0.3f, 0.3f));//�v���C���[�̋����������ݒ肵�A�`���R�{�[���ɖ������悤�ɂ��Ă���B
	rb->setMassProps(1.0f, btVector3(0.1f, 0.1f, 0.1f));//�������͎��ʁA�������͉�]�̂��₷��
	//rb->applyForce(btVector3(0.0f, 100.0f, 0.0f), btVector3(1.0f, 1.0f, 1.0f));//�`���R�{�[���ɓ������Đ�����ԗ͂�ݒ�
	m_animation.SetAnimSpeed(2.0f);//�A�j���[�V�����Đ����x��ݒ�
}

void CPlayer::RollingPlayer()
{
	btRigidBody* rb = m_IsIntersect.GetRigidBody();//�v���C���[�̍��̂��擾

	//�����G���W���Ōv�Z�����ړ����v���C���[�ɔ��f
	btVector3 pos = rb->getWorldTransform().getOrigin();
	m_transform.position.x = pos.x();
	m_transform.position.y = pos.y();
	m_transform.position.z = pos.z();

	//�����G���W���Ōv�Z������]���v���C���[�ɔ��f
	btQuaternion rot = rb->getWorldTransform().getRotation();
	m_transform.angle.x = rot.x();
	m_transform.angle.y = rot.y();
	m_transform.angle.z = rot.z();
	m_transform.angle.w = rot.w();

	//�Q�[���I�[�o�[�ɂȂ�܂ł̑ҋ@���Ԃ̐ݒ�
	deadTimer += 1.0 / 60.0f;
	if (deadTimer >= 2.0f){
		m_GameState = GAMEEND_ID::OVER;
	}
}

