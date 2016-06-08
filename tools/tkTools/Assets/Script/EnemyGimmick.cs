using UnityEngine;
using System.Collections;

public class EnemyGimmick : MonoBehaviour {
    public int enemyType = -1;
    public int gimmickType = -1;
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
}
