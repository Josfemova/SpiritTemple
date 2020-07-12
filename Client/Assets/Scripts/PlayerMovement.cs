using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayerMovement : MonoBehaviour
{

	//how fast
	public float speed;
	private Rigidbody2D myRigidbody;
	private Vector3 change;
	//reference to Animator
	private Animator animator;
	public Tilemap molo;


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
        void MoveCharacter(){
		//Vector3Int originP = new Vector3Int(0,0,0);
		Vector3Int pos = Vector3Int.FloorToInt(transform.position);
		Vector3Int posExample = new Vector3Int(2, 2, 0);
		Debug.Log("---get empty vector (2,2):  "+ molo.GetSprite(posExample));
        Debug.Log("---actual Origin: " + molo.origin + "----¿sprite on Tilemap? :  " + molo.HasTile(pos) + "---name: " + molo.GetSprite(pos));

        //Debug.Log(transform.position);
        myRigidbody.MovePosition(
            transform.position + change
            );
    }

    private void FixedUpdate(){
        myRigidbody.velocity = new Vector2(change.x, myRigidbody.velocity.y);
    }
   
}
