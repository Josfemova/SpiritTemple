using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
	public Transform target;
	public float smoothing;
	public Vector2 maxPosition;
	public Vector2 minPosition;
    void Start()
    {
        
    }

    /// <summary>
    /// in charge of keeping camera looking for the player
    /// </summary>
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
			targetPosition.x = Mathf.Clamp(targetPosition.x,
			minPosition.x,
			maxPosition.x);

			targetPosition.y = Mathf.Clamp(targetPosition.y,
			minPosition.y,
			maxPosition.y);

    		transform.position = Vector3.Lerp(transform.position,
    			targetPosition,
    			smoothing);
    	}
        
    }
}
