#include "stdafx.h"
#include "Field.h"
#include "CollisionType.h"
#include "ObjectManager.h"
#include "StageTable.h"
#include "ZBufferSphere.h"
#include "RenderContext.h"
#include "Camera.h"

CField::~CField()
{

}

void CField::Initialize(){
	m_czbuffersphere = NULL;
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXToRadian(90.0f));
	//m_transform.angle = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	strcpy(m_pFileName, FieldNameArray[m_StageID]);

	//���̂��������B
	{
		//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
		SCollisionInfo* Table = collisionInfoTableArray[m_StageID];
		int arraySize = collisionInfoTableSizeArray[m_StageID];	//�z��̗v�f����Ԃ��B
		for (int i = 0; i < arraySize; i++) {
			SCollisionInfo& collision = Table[i];
			btBoxShape* work = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			m_groundShape.push_back(work);
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, -collision.pos.z));
			groundTransform.setRotation(btQuaternion(-collision.rotation.x, collision.rotation.y, -collision.rotation.z, collision.rotation.w));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, work, btVector3(0, 0, 0));
			btRigidBody* work2 = new btRigidBody(rbInfo);
			m_rigidBody.push_back(work2);
			work2->activate();
			m_rigidBody[i]->setUserIndex(CollisionType_Map);
			//���[���h�ɒǉ��B
			SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->AddRigidBody(work2);
		}
	}

	SetAlive(true);

	C3DImage::Initialize();
	C3DImage::SetImage();
}

void CField::Update(){
	C3DImage::Update();
}

void CField::Draw(){
	SetUpTechnique();
	if (m_czbuffersphere == NULL){
		m_czbuffersphere = SINSTANCE(CObjectManager)->FindGameObject<CZBufferSphere>(_T("ZBufferSphere"));
	}
	if (m_czbuffersphere){
		m_pEffect->SetTexture("g_ZMask", m_czbuffersphere->GetTexture());
	}
	C3DImage::Draw();
}

void CField::DrawDepth(LPD3DXEFFECT effect, const D3DXVECTOR2& FarNear){
	D3DXMATRIX World;
	World = m_World;

	C3DImage* pPintoObject = SINSTANCE(CObjectManager)->FindGameObject<C3DImage>(_T("TEST3D"));
	D3DXMATRIX work = pPintoObject->GetWorldMatrix();
	D3DXMATRIX PintoWorld;
	D3DXMatrixIdentity(&PintoWorld);
	memcpy(&PintoWorld.m[3][0], &work.m[3][0], sizeof(float)* 4);


	effect->SetTechnique("DepthSampling_NonAnimation_Z");
	effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	effect->BeginPass(0);


	// ���݂̃v���W�F�N�V�����s��ƃr���[�s����V�F�[�_�[�ɓ]��
	effect->SetVector("g_FarNear", &(static_cast<D3DXVECTOR4>(FarNear)));
	D3DXVECTOR3 pos = pPintoObject->GetPos();

	if (m_czbuffersphere == NULL){
		m_czbuffersphere = SINSTANCE(CObjectManager)->FindGameObject<CZBufferSphere>(_T("ZBufferSphere"));
	}
	if (m_czbuffersphere){
		effect->SetTexture("g_ZMaskSample", m_czbuffersphere->GetTexture());
	}

	effect->SetVector("g_PintoPoint", &(static_cast<D3DXVECTOR4>(pos)));
	effect->SetMatrix("g_Proj", &(SINSTANCE(CRenderContext)->GetCurrentCamera()->GetProj()));
	effect->SetMatrix("g_View", &(SINSTANCE(CRenderContext)->GetCurrentCamera()->GetView()));
	effect->SetMatrix("g_PintoWorld", &PintoWorld);// �s���g�����킹��|�C���g���s��ϊ����邽�߂̃��[���h�s��
	effect->SetMatrix("g_World", &World/*�ݒ肵�����s��ւ̃|�C���^*/);

	D3DXMESHCONTAINER_DERIVED* container = GetImage()->pModel->GetContainer();

	for (DWORD i = 0; i < container->NumMaterials; i++){
		effect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B
		container->MeshData.pMesh->DrawSubset(i);						// ���b�V����`��
	}
	effect->EndPass();
	effect->End();


}