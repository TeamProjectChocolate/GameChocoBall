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
#include "FireJet.h"

CPlayer* g_player = NULL;
CPlayer::~CPlayer(){ 
	int bulletMax = m_bullets.size();
	for (int idx = 0; idx < bulletMax; idx++){
		SAFE_DELETE(m_bullets[idx]);
	}
	m_bullets.clear();

	list<CCBManager*>::iterator itr = m_CBManager.begin();
	for (; itr != m_CBManager.end();itr++){
		SINSTANCE(CObjectManager)->DeleteGameObjectImmediate(*itr);
	}
	m_CBManager.clear();
}

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
	m_PreviousJumpFlag = false;
	ChocoBall = false;
	
	GamaOverFlag = false;
	BusterEnemyNum = 0;
	m_size.x = 1.0f;
	m_size.y = 2.0f;
	m_size.z = 1.0f;

	//�W�����v�����n���̃^�C�}�[�֌W
	m_JumpParticleTime = 0.2f;
	m_JumpParticleTimer = 0.0f;
	
	//�e���ˎ��̃^�C�}�[�֌W
	//m_GunParticleTime = 0.2f;
	//m_GunParticleTimer = 0.0f;

	BulletShotInterval = 0;

	m_GameState = GAMEEND_ID::CONTINUE;

	m_Courcedef.SetStageID(m_StageID);
	m_Courcedef.Initialize();
	m_NowCourceNo = -1;

	// ���C�g�֘A�̏�����
	this->ConfigLight();
	
	m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius,CollisionType_Player);
	m_IsIntersect.SetAudio(m_pAudio);
	
	C3DImage::SetImage();

	deadTimer = 0.0f;
	m_lockonEnemyIndex = 0;	
	for (int idx = 0; idx < m_animation.GetNumAnimationSet(); idx++){
		m_animation.SetAnimationEndtime(idx,AnimationTime[idx]);
	}
	m_pCamera = SINSTANCE(CObjectManager)->FindGameObject<CCourceCamera>(_T("Camera"));
	CParticleEmitter::EmitterCreate(
		_T("ParticleEmitterStart"),
		PARTICLE_TYPE::STAR,
		m_transform.position,
		m_pCamera->GetCamera(),
		m_StageID,
		true
		);
	//�W�����v�����n���̉�
	m_pEmitter = CParticleEmitter::EmitterCreate(
		_T("ParticleEmitterSmoke"),
		PARTICLE_TYPE::SMOKE,
		m_transform.position,
		m_pCamera->GetCamera(),
		m_StageID,
		false
		);

	//�e���ˎ��̉�
	/*m_pEmitter2 = CParticleEmitter::EmitterCreate(
		_T("ParticleEmitterGunParticle"),
		PARTICLE_TYPE::GUNPARTICLE,
		m_transform.position,
		m_pCamera->GetCamera(),
		m_StageID,
		false
		);*/

	m_UseBorn = true;
	m_MoveFlg = true;
	m_vibration.Initialize();
}

void CPlayer::SetParent(MoveFloor* parent)
{
	//�e���ݒ肳�ꂽ�̂ŁA���[���h���W�����߂邽�߂ɁB��UUpdate���Ăяo���B

	
	if (parent != NULL){
		Update();
		
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
		this->parent = parent;
	}
}

void CPlayer::Update()
{
	if (m_GameState == GAMEEND_ID::CONTINUE)
	{
		//1�t���[���ł̃J�E���^�[�̉��Z����
		m_JumpParticleTimer += 1.0f / 60.0f;

		//�W�����v�����n���p�[�e�B�N���̔������Ԃ��J�E���^�[����������p�[�e�B�N�����������J�E���^�[��������
		if (m_JumpParticleTimer >= m_JumpParticleTime)
		{
			m_pEmitter->SetEmitFlg(false);
			m_JumpParticleTimer = 0.0f;
		}
		//�e���˂̃p�[�e�B�N����������
		/*if (m_GunParticleTimer >= m_GunParticleTime)
		{
			m_pEmitter2->SetEmitFlg(false);
			m_GunParticleTimer = 0.0f;
		}*/

		//�e������Ƃ��̏���
		if (parent)
		{
			D3DXMATRIX mParentWorld = parent->GetWorldMatrix();
			//�e�̃��[���h�s�����Z���āA���[�J�����W�����[���h���W�ɕϊ�����

			D3DXVECTOR4 pos;
			D3DXVec3Transform(&pos, &localPosition, &mParentWorld);
			m_transform.position.x = pos.x;
			m_transform.position.y = pos.y;
			m_transform.position.z = pos.z;
		}
		
		// �f�o�C�X���؂�ւ�����ꍇ�͎����Ő؂�ւ���
		SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);

		m_currentAnimNo = 0;		

		// ���C�g�̍X�V
		this->UpdateLight();

		// ���C���V�[���̏�Ԃ��Ǘ����鏈��
		StateManaged();

		//�Q�[���p�b�h�ł̃v���C���[�̈ړ��B
		if (m_MoveFlg){
			Move();
		}

		// �A�j���[�V�����Đ��֐����Ăяo��
		m_animation.PlayAnimation(m_currentAnimNo, 0.1f);

		//�v���C���[�̋������R�[�X��`�ɉ��������̂ɕ␳���鏈��
		BehaviorCorrection();

		//���b�N�I������
		if (m_MoveFlg){
			//���b�N�I�������������ł���܂ł͕ăA�E�g
			//LockOn();
		}

		for (auto itr : m_CBManager){
			if (itr != NULL)
			{
				//�`���R�{�[���ɓ������Ă��邩�̏���
				if (m_HitFlag = itr->IsHit(m_transform.position, m_size))
				{
					//�`���R�{�[���ɓ���������̏���
					ChocoHit();
				}
			}
			if (m_NowCourceNo != -1){
				if (m_NowCourceNo - itr->GetCourceNo() >= 5){
					DeleteChocoBall(itr);
				}
			}
		}

		if (GamaOverFlag==false)//�Q�[���I�[�o�[�ɂȂ��Ă��Ȃ����̏���
		{
			
			m_vibration.Update();
			// �U���������s��A�U�����I�����Ă��邩
			if (!m_vibration.GetIsVibration()){
				m_MoveFlg = true;
				m_pCamera->SetIsTarget(true);
			}


			//�v���C���[�̏����̍Ō�ɂȂ�ׂ�������
			m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed, Jumpflag);

			//���n���Ă���̂Ńt���O��false
			if (m_IsIntersect.IsHitGround())
			{
				//���n���̉����o������
				if (m_PreviousJumpFlag!=Jumpflag)
				{
					m_pEmitter->SetEmitFlg(true);
					// �����̎��͂Ƀp�[�e�B�N������
					//Set����Ə�Ƀv���C���[�̏ꏊ�Ƀp�[�e�B�N���̔�������
					D3DXVECTOR3 pos = m_transform.position;//�p�[�e�B�N����pos��ς��邽�߂����̊i�[
					pos.y = pos.y - 0.7f;
					m_pEmitter->SetEmitPos(pos);
					m_PreviousJumpFlag = Jumpflag;
					m_pAudio->PlayCue("Landing", true,this);
				}
				Jumpflag = false;
			}
			else
			{
				Jumpflag = true;
				//m_currentAnimNo = Jump;

			}
			// �e���ˏ���
			BulletShot();

			//��]�s��
			SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_currentAngleY);
		}
		else if (GamaOverFlag == true)//�Q�[���I�[�o�[��Ԃł̏���
		{
			//�Q�[���I�[�o�[��Ԃł̃`���R�{�[���ɗ�����鏈��
			RollingPlayer();
		}
		if (m_GameState!=GAMEEND_ID::CLEAR)
		{
			C3DImage::Update();
		}
	}

	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 15.0f, 0.0f));

	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		if (m_bullets[idx]->Update()){
			DeleteBullet(m_bullets[idx]);
		}
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
	ExcuteDeleteChocoBall();
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
	m_lightColor[0] = D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f);
	m_lightColor[1] = D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f);
	m_lightColor[2] = D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f);
	m_lightColor[3] = D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f);


	// �A���r�G���g���C�g(����)�̋����ݒ�
	D3DXVECTOR4 ambientLight;
	ambientLight = D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f);

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


	//�W�����v�֘A�̏���
	if (m_pInput->IsTriggerSpace() && Jumpflag == false)
	{
		m_pAudio->PlayCue("Jump", true,this);//�W�����vSE
		m_moveSpeed.y = PLAYER_JUMP_POWER;
		Jumpflag = true;
		m_pEmitter->SetEmitFlg(true);
		// �����̎��͂Ƀp�[�e�B�N������
		//Set����Ə�Ƀv���C���[�̏ꏊ�Ƀp�[�e�B�N���̔�������
		D3DXVECTOR3 pos = m_transform.position;//�p�[�e�B�N����pos��ς��邽�߂����̊i�[
		pos.y = pos.y - 0.5f;
		m_pEmitter->SetEmitPos(pos);
		m_PreviousJumpFlag = Jumpflag;
		m_currentAnimNo = 2;
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
		m_currentAnimNo = Walk;
	}

	//���E�̓���
	if (fabsf(X) > 0.0f)
	{
		m_moveSpeed.x = X * MOVE_SPEED;
		isTurn = true;
		m_currentAnimNo = Walk;
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
	V1 = m_pCamera->GetCamera()->GetTarget() - m_pCamera->GetCamera()->GetPos();
	
	D3DXVECTOR3		V2;
	D3DXVECTOR3		Up;

	Up.x = 0.0f;
	Up.y = 1.0f;
	Up.z = 0.0f;

	//���s����x�N�g�������߂�B
	//COURCE_BLOCK Cource = m_Courcedef.FindCource(m_transform.position);
	//V1 = Cource.endPosition - Cource.startPosition;
	D3DXVec3Normalize(&V1, &V1);//3D �x�N�g���𐳋K�������x�N�g����Ԃ��B
	D3DXVec3Cross(&V2, &V1,&Up);//2��3D�x�N�g���̏�����̊O�ς����߂遨���s����V2��������B
	D3DXVec3Normalize(&V2, &V2);

	//�J�����ɂ��������ăv���C���[�̐i�s�����ƋȂ�������w��
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
	//�Q�[���I�[�o�[����
	if (m_transform.position.y <= -15.0f)
	{
		m_GameState = GAMEEND_ID::OVER;
		return;
	}

	//�Q�[���N���A
	COURCE_BLOCK EndBlock = m_Courcedef.FindCource(m_Courcedef.GetCourceMax() - 1);
	COURCE_BLOCK nowBlock = m_Courcedef.FindCource(m_transform.position);
	m_NowCourceNo = nowBlock.blockNo;
	if (nowBlock.blockNo == EndBlock.blockNo){
		D3DXVECTOR3 LoadVec;
		LoadVec = EndBlock.startPosition - EndBlock.endPosition;
		D3DXVECTOR3 GoalToPlayerVec;
		GoalToPlayerVec = m_transform.position - EndBlock.endPosition;
		float Kyori = D3DXVec3Dot(&GoalToPlayerVec, &LoadVec);
		if (Kyori < 0.001f)
		{
			if (GamaOverFlag = true)
			{
				m_GameState = GAMEEND_ID::CLEAR;
				return;
			}	
		}
	}

	if (!m_vibration.GetIsVibration()){
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
				m_MoveFlg = false;
				m_pCamera->SetIsTarget(false);
				m_vibration.ThisVibration(&(m_transform.position), D3DXVECTOR3(0.002f, 0.0f, 0.0f), 0.5f, 0.01f);
				m_moveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_pAudio->PlayCue("ta_ge_denki01", true, this);
				//m_GameState = GAMEEND_ID::OVER;
				return;
			}
		}

		// ���̃M�~�b�N�Ƃ̓����蔻��
		for (int idx = 0;; idx++){
			string str = "firejet";
			char num[100];
			_itoa(idx, num, 10);
			str += num;
			CFireJet* firejet = SINSTANCE(CObjectManager)->FindGameObject<CFireJet>(_T(str.c_str()));
			if (firejet == nullptr){
				return;
			}
			if (firejet->IsCollision(m_transform.position, 1.0f)){
				m_MoveFlg = false;
				m_pCamera->SetIsTarget(false);
				m_vibration.ThisVibration(&(m_transform.position), D3DXVECTOR3(0.002f, 0.0f, 0.0f), 1.2f, 0.01f);
				m_moveSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//m_GameState = GAMEEND_ID::OVER;
				return;
			}
		}
	}
}
bool CPlayer::IsVibration() 
{
	return m_vibration.GetIsVibration();
}
void CPlayer::BulletShot()
{
	if (m_MoveFlg){
		BulletShotInterval++;
		if (BulletShotInterval % 5 == 0){

			if (m_pInput->IsPressRightShift())
			{
				//�v���C���[�̌����Ă���x�N�g�����v�Z
				D3DXVec3Normalize(&RV0, &RV0);
				D3DXMatrixRotationY(&Rot, m_currentAngleY);
				D3DXVec3Transform(&RV1, &RV0, &Rot);

				//D3DXVECTOR3 pos = m_transform.position;
				//pos.y += 0.3f;
				//�v���C���[�̌����ɍ��킹�ăp�[�e�B�N���̔����ꏊ�����炵�Ă���
				//pos = RV0*1.0f;
				//m_pEmitter2->SetEmitFlg(true);
				//m_pEmitter2->SetEmitPos(pos);

				CPlayerBullet* bullet = new CPlayerBullet;
				bullet->Initialize();
				bullet->SetPos(m_transform.position);
				bullet->SetDir(RV1);
				bullet->SetBulletSpeed(0.5f);
				bullet->SetAudio(m_pAudio);
				m_bullets.push_back(bullet);
				m_pAudio->PlayCue("Laser", true,this);
			}
		}
	}

	//�v���C���[�ƒe�̋�����20m�ɂȂ�ƒe��������Delete����B
	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		D3DXVECTOR3 V5;
		V5 = m_bullets[idx]->GetPos() - m_transform.position;
		float length = D3DXVec3Length(&V5);
		if (length > BULLET_LENG)
		{
			DeleteBullet(m_bullets[idx]);
		}
	}
}

void CPlayer::DeleteBullet(CPlayerBullet* bullet){
	m_Deletebullets.push_back(bullet);
}

void CPlayer::ExcuteDeleteBullets(){
	vector<CPlayerBullet*>::iterator itr;
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
	m_animation.SetAnimSpeed(1.0f);//�A�j���[�V�����Đ����x��ݒ�
}
void CPlayer::EnemyBulletHit( D3DXVECTOR3 moveDir )
{
	m_pAudio->PlayCue("�X�|�b�P", false, this);
	GamaOverFlag = true;
	btRigidBody* rb = m_IsIntersect.GetRigidBody();//�v���C���[�̍��̂��擾
	//m_IsIntersect.GetSphereShape()->setLocalScaling(btVector3(0.3f, 0.3f, 0.3f));//�v���C���[�̋����������ݒ肵�A�`���R�{�[���ɖ������悤�ɂ��Ă���B
	rb->setMassProps(1.0f, btVector3(0.01f, 0.01f, 0.01f));//�������͎��ʁA�������͉�]�̂��₷��
	moveDir *= 750.0f;
	rb->applyForce(btVector3(moveDir.x, moveDir.y + 1000.0f, moveDir.z), btVector3(1.0f, 1.0f, 1.0f));//�`���R�{�[���ɓ������Đ�����ԗ͂�ݒ�
	rb->setAngularVelocity(btVector3(5.0f, 5.0f, 5.0f));
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
	deadTimer += 1.0f / 60.0f;
	if (deadTimer >= 2.0f){
		m_GameState = GAMEEND_ID::OVER;
	}
}

void CPlayer::DeleteChocoBall(CCBManager* mgr){
	m_DeleteChocoBall.push_back(mgr);
}

void CPlayer::ExcuteDeleteChocoBall(){
	for (auto itr2 : m_DeleteChocoBall){
		for (list<CCBManager*>::iterator itr = m_CBManager.begin(); itr != m_CBManager.end();){
			if (*itr == itr2){
				(*itr)->NonActivate();
				SINSTANCE(CObjectManager)->DeleteGameObject(*itr);
				itr = m_CBManager.erase(itr);
			}
			else{
				itr++;
			}
		}
	}
	m_DeleteChocoBall.clear();
}