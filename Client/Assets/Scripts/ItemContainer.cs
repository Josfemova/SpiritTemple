using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemContainer : MonoBehaviour
{
    public string itemType;
    public Animator animator;
    public GameObject chestSprite;
    void Start()
    {
        animator = chestSprite.GetComponent<Animator>();
    }

        void Update()
    {   //testing open chest with Keyboard
        openChest();
    }

    void openChest(){
        //open the chest
        //parameters, setting variable as boolean on animator (name,value)  
        animator.SetBool("Open", true);
        //Debug.Log("Entró");
    }
}
