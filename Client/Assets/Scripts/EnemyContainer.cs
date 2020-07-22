using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyContainer : MonoBehaviour
{
    public string enemyType;
    public Animator animator;
    private int orientationX = 0; //1 right, -1, left
    private int orientationY = -1; //1 up, -1 down

    //public GameObject enemySprite;
   

    void Start()
    {
        //animator = enemySprite.GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {   
        move(Vector3.zero);
    }

    /// <summary>
    /// Moves associated GameObject based on a given vector representing a delta 
    /// </summary>
    /// <param name="change">vector representing a distance delta</param>
    public void move(Vector3 change){
        change.x = Input.GetAxisRaw("Horizontal");
        change.y = Input.GetAxisRaw("Vertical");

        if (change != Vector3.zero)
        {
            orientationX = (int)change.x;
            orientationY = (int)change.y;
            animator.SetFloat("MoveX", change.x);
            animator.SetFloat("MoveY", change.y);
        }       

    }
}
