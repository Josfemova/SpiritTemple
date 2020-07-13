using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class Player : MonoBehaviour
{

    private Animator animator;
    public GameObject playerSprite;
    private int orientationX = 0; //1 right, -1, left
    private int orientationY = -1; //1 up, -1 down

    // Start is called before the first frame update
    void Start()
    {
        animator = playerSprite.GetComponent<Animator>();
    }
    void Update()
    {
        Vector3 change = Vector3.zero;
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
    void attackAnimation()
    {

    }
}
