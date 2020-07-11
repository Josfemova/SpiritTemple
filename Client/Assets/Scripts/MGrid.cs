using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MGrid : MonoBehaviour
{   
    //[SerializeField] GameObject enemy;


   /*
   Interactive objects
   */
    [SerializeField] GameObject obstacle;
    [SerializeField] GameObject player;

    /*
    some variables
    */
    GameObject playerObj;
    private Vector3 change;
    


    /*  propuesta:

        0-> FREEWAY
        1-> OBSTACLE
        2-> PLAYER
        3-> ENEMIES
        4-> TRUNK
        5-> SECURE ZONE
        6-> RATS
    */

 
    /*
    create matrix
    */
    void Start()
    {  

        int[][] gameMatrix = new int[20][];
        gameMatrix[0] = new int[20]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        gameMatrix[1] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[2] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[3] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[4] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[5] = new int[20]{ 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };
        gameMatrix[6] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[7] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[8] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[9] = new int[20]{ 1, 2, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[10] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[11] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[12] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[13] = new int[20]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
        gameMatrix[14] = new int[20]{ 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1 };
        gameMatrix[15] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[16] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[17] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[18] = new int[20]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 };
        gameMatrix[19] = new int[20]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        
        
        CreateMap(gameMatrix);
    }



    /*
    create map, server will update matrix
    */


    public void CreateMap(int[][] matrix)
    {
        for(int j = 0; j < matrix.Length; j++)
        {
            for(int k = 0; k < matrix[j].Length; k++)
            {
                int value = matrix[j][k];
                
                /*
                    GENERATE OBJECTS BY NUMBERS
                */
                //Debug.Log(matrix[j][k]);

                switch(value)
                {
                    case 1:
                        obstacle = Instantiate(obstacle, new Vector3(j,k,0),Quaternion.identity);
                        break;
                    case 2:
                        playerObj = Instantiate(player, new Vector3(j,k,0),Quaternion.identity);
                        break;
                }
            }
        }
    }




/*

Player move (keywords), client update matrix

IMPORTANT

(0,1)   UP
(1,0)   DOWN
(-1,0)  RIGHT
(0,-1)  LEFT

*/
     void MovePlayer(/*the json*/)
    {   
        change = Vector3.zero;
    	//access control, with buttons
    	change.x = Input.GetAxisRaw("Horizontal");
    	change.y = Input.GetAxisRaw("Vertical");
        //user press some key
    	if(change != Vector3.zero){
            Debug.Log("MoveX: " + change.x + "MoveY: " + change.y);

    	}

        /*
        if press keyword, update matrix and send to server, server update matrix and
         go back to client to interface update
        */

    }
}
