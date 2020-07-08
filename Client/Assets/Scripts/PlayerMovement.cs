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
    	//access to contros with buttons
    	change.x = Input.GetAxisRaw("Horizontal");
    	change.y = Input.GetAxisRaw("Vertical");
    	if(change != Vector3.zero){
    		MoveCharacter();
    		animator.SetFloat("MoveX", change.x);
    		animator.SetFloat("MoveY", change.y);
    	}

    	//Debug.Log(change); 
    }
    //move object to other places
    void MoveCharacter(){
    	myRigidbody.MovePosition(
    		transform.position + change * speed * Time.deltaTime
    		);

    }
//nuevo método
    private void FixedUpdate(){
        myRigidbody.velocity = new Vector2(change.x, myRigidbody.velocity.y);
    }
   
}
