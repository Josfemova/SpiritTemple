using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{

	//how fast
	public float speed;
	private Rigidbody2D myRigidbody;
	private Vector3 change;
	//reference to Animator
	private Animator animator;


    // Start is called before the first frame update
    void Start()
    {	animator = GetComponent<Animator>();
    	myRigidbody = GetComponent<Rigidbody2D> ();
    }

    // Update is called once per frame
    void Update()
    {
    	change = Vector3.zero;
    	//access control, with buttons
    	change.x = Input.GetAxisRaw("Horizontal");
    	change.y = Input.GetAxisRaw("Vertical");
    	if(change != Vector3.zero){
    		MoveCharacter();
    		animator.SetFloat("MoveX", change.x);
    		animator.SetFloat("MoveY", change.y);
            //Debug.Log("MoveX" + change.x + "MoveY" + change);

    	}

    	//Debug.Log(change); 
    }
    //move object to other places
	// if tal cosa se presiona, se manda al server,y l
    void MoveCharacter(){
		Debug.Log(transform.position);
    	myRigidbody.MovePosition(
    		transform.position + change
    		);

    }

    private void FixedUpdate(){
        myRigidbody.velocity = new Vector2(change.x, myRigidbody.velocity.y);
    }
   
}
