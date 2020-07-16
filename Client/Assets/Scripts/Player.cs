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
    void Start()
    {
        animator = playerSprite.GetComponent<Animator>();
    }
    void Update()
    {
        Vector3 change = Vector3.zero;
        change.x = Input.GetAxisRaw("Horizontal");
        change.y = Input.GetAxisRaw("Vertical");
//Using configured keyword "attack" on Space doesn't work
//Using preconfugured keyword Space, doesn't work

        if(Input.GetKeyDown("j")){
            StartCoroutine(attackAnimation());

        }else if(Input.GetKeyDown("k")){
            //Debug.Log("defending");
            StartCoroutine(defendingAnimation());


        }else if(change != Vector3.zero){

            orientationX = (int)change.x;
            orientationY = (int)change.y;
            animator.SetFloat("MoveX", change.x);
            animator.SetFloat("MoveY", change.y);
        }
    }

    public IEnumerator attackAnimation(){  
        animator.SetBool("attacking",true);
        yield return null;
        animator.SetBool("attacking",false);
        yield return new WaitForSeconds(1);
    }

    public IEnumerator defendingAnimation(){
        Debug.Log("protecting");
        animator.SetBool("protecting",true);
        yield return null;
        animator.SetBool("protecting",false);
        yield return new WaitForSeconds(1);

    }
}
