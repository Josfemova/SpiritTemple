using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class PlayerMovement : MonoBehaviour
{

    private Vector3 change;
    private Animator animator;
    public Tilemap groundMap;
    public Tilemap obstacleMap;
    public GameObject playerSprite;
    private int orientationX = 0; //1 right, -1, left
    private int orientationY = -1; //1 up, -1 down


    // Start is called before the first frame update
    void Start()
    {
        animator = playerSprite.GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {

        change = Vector3.zero;
        change.x = Input.GetAxisRaw("Horizontal");
        change.y = Input.GetAxisRaw("Vertical");
        if (change != Vector3.zero)
        {
            MoveCharacter();
        }
        if (Input.GetKeyDown(KeyCode.Space)){
            //attack routine
        }


    }
    void MoveCharacter()
    {
        //keeps track of orientation for attacks
        orientationX = (int)change.x;
        orientationY = (int)change.y;
		animator.SetFloat("MoveX", change.x);
        animator.SetFloat("MoveY", change.y);
        Vector3 newPosition = transform.position + change;
        if (!obstacleMap.HasTile(Vector3Int.FloorToInt(newPosition))){
            transform.position = newPosition;
            Vector3Int pos = Vector3Int.FloorToInt(transform.position);
            Debug.Log("-Origin: " + groundMap.origin + "\n-HasTile :  " + groundMap.HasTile(pos));
            Debug.Log("-name: " + groundMap.GetSprite(pos) + " \nlocation: " + pos);
        }

    }
}
