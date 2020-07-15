using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemContainer : MonoBehaviour
{
    public string itemType;
    public Animator animator;
    public GameObject itemSprite;
    void Start()
    {
        animator = itemSprite.GetComponent<Animator>();
    }

        void Update()
    {  
        //constains teasure
        openChest();
        //constains hearts
        openJar();
    }

    void openChest(){
        animator.SetBool("Open", true);
    }
    void openJar(){
        animator.SetBool("Open", true);
    }
}
