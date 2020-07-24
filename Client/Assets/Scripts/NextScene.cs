using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class NextScene : MonoBehaviour
{	private int NextSceneLoad;
    // Start is called before the first frame update
    void Start()
    {
    	//las escenas tienen un numero BuilIndex +1 lo que hace es cambiarlas
    	//basado en el número establecido

        NextSceneLoad = SceneManager.GetActiveScene().buildIndex + 1;

    }
    /// <summary>
    /// loads new scene on collision
    /// </summary>
    /// <param name="collision"></param>
    private void OnTriggerEnter2D(Collider2D collision)
    {
        SceneManager.LoadScene(NextSceneLoad);
    }
}
