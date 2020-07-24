using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CanvasScore : MonoBehaviour
{
    // Start is called before the first frame update
    public string cScore;
    public Text scoreText;
    public int score = 750;
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update()
    { 
        sumScore(score);
        
    }
//1 hit, loss 1 live
//1 found hearts, 1 more live
   
    
    /// <summary>
    /// keeps track of player score
    /// </summary>
    /// <param name="score"></param>
    public void sumScore(int score){
        scoreText.text = "score"+ score;
    }
}
