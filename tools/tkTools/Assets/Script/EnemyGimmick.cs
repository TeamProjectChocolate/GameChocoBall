using UnityEngine;
using System.Collections;


public class EnemyGimmick : MonoBehaviour {
    public int enemyType = -1;
    public int gimmickType = -1;
    public GimmickTypeText GimmickTypeText;
    public EnemyTypeText EnemyTypeText;
    // Use this for initialization
    void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        if(enemyType==0)
        {
            gimmickType = -1;
        }
        else if(gimmickType==1)
        {
            enemyType = -1;
        }
	
	}
    //public class GimmickTyep : MonoBehaviour
    //{
    //    public string GimmicktypeText = "ギミックタイプ一覧";
    //}
  
}

[System.Serializable]
public class GimmickTypeText
{
    public int Chocoball = 0;
    public int Wall = 1;
    public int FallFloor = 2;
    public int MoveFloor = 3;
}

[System.Serializable]
public class EnemyTypeText
{
    public int EnemyLR = 0;
    public int EnemyFB = 1;
    public int EnemyJamp = 2;
    public int Enemy = 3;
}