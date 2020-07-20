using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PrevScene : MonoBehaviour{
    private int nextSceneToLoad;
    // Start is called before the first frame update
    private void Start()
    {
    	//las escenas tienen un numero BuilIndex -1 lo que hace es cambiarlas
    	//basado en el número establecido

        nextSceneToLoad = SceneManager.GetActiveScene().buildIndex + 1;

    }

    // Update is called once per frame
    private void OnTriggerEnter2D(Collider2D collision)
    {
         SceneManager.LoadScene(nextSceneToLoad);
    }
}
