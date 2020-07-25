using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemContainer : MonoBehaviour
{
    public string itemType;
    public Animator animator;
    int cnt = 0;
    bool dissapear = false;
    void Update()
    {  
        if(dissapear){
            if(cnt==3){
                transform.position = new Vector3(-4,-4);
                this.gameObject.SetActive(false);
            }
            else
                cnt+=1;
        }
    }

    public void openChest(){
        dissapear = true;
        animator.SetBool("Open", true);
    }
    public void openJar(){
        dissapear  = true;
        animator.SetBool("Open", true);
    }
}
