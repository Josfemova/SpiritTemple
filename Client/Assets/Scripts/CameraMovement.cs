using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
	public Transform target;
	public float smoothing;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update pasa cada frame
    // Late Update pasa de forma tardía
    void LateUpdate()
    {
    	if(transform.position != target.position)
    	{
    		//interpolacion polar con Lerp
    		//parametros -> (posicion donde está, 
    		//posicion donde quiero que vaya,
    		// cantidad que quiero que cubra
    		Vector3 targetPosition = new Vector3(target.position.x,
    			target.position.y,
    			transform.position.z
    			);
    		transform.position = Vector3.Lerp(transform.position,
    			targetPosition,
    			smoothing);
    	}
        
    }
}