using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class minimap : MonoBehaviour
{
    // Start is called before the first frame update
    public Transform target;
    public Camera MainCamera;
    void Start()
    {
        setPosition();
    }

    // Update is called once per frame
    void Update()
    {
        if(target != null){
            setPosition();  
        }
    }

    private void setPosition(){
        var newPos = target.position;
        newPos.y = transform.position.y;
        transform.position = newPos;
    }
}
