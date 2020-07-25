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
    private Vector3 movement;
    private int moveCnt = 0;
    
    /// <summary>
    /// In charge of smoothly moving the enemy
    /// </summary>
    void Update()
    {
        /**if (moveCnt == 3)
        {
            movement = Vector3.zero;
            moveCnt = 0;
        }
        else
        {
            transform.position = transform.position + movement / 3;
            moveCnt++;
        }**/
    }

    /// <summary>
    /// Moves associated GameObject based on a given vector representing a delta 
    /// </summary>
    /// <param name="change">vector representing a distance delta</param>
    public void move(Vector3 change)
    {
        //change.x = Input.GetAxisRaw("Horizontal");
        //change.y = Input.GetAxisRaw("Vertical");

        if (change != Vector3.zero)
        {
            //movement = change;
            transform.position = transform.position + change;
            orientationX = (int)change.x;
            orientationY = (int)change.y;
            animator.SetFloat("MoveX", change.x);
            animator.SetFloat("MoveY", change.y);
        }

    }
    /// <summary>
    /// teleports enemy to given position
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    public void teleport(int x, int y){
        transform.position = new Vector3(x,y);
    }
}
