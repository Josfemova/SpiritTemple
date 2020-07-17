using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class CanvasHealth : MonoBehaviour
{
    
    // Start is called before the first frame update
    public string cHearts;
    public int health;
    public int numOfHearts;
    public Image[] hearts;
    public Sprite fullHeart;
    public Sprite emptyHeart;
    void Start()
    {   //exaple
        numOfHearts = 4;
        health = 1;

    }

    // Update is called once per frame
    void Update(){

        heartsPlayer(numOfHearts, health);
    }
/*
numOfHearts = number of hearts, bc I don't remember
health = number that change the number of hearts,
 increase or decrease hearts

*/
    void heartsPlayer(int numOfHearts, int health){

        for(int i = 0; i < hearts.Length; i++){
            if(i < health){
                hearts[i].sprite = fullHeart;
            }else{
                hearts[i].sprite = emptyHeart;
            }
            if(i < numOfHearts){
                hearts[i].enabled = true;
            }else{
                hearts[i].enabled = false;
            }
        }
    }
    
}
