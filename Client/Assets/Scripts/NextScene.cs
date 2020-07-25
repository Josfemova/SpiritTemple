using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class NextScene : MonoBehaviour
{	private int NextSceneLoad;
    // Start is called before the first frame update
    
    private string message;
    void Start()
    {
        JsonReq req = new JsonReq("final-level", otherval: 1);
        message = JsonUtility.ToJson(req);
    	//las escenas tienen un numero BuilIndex +1 lo que hace es cambiarlas
    	//basado en el número establecido
        NextSceneLoad = 0;

    }
    void update(){
        Client.Instance.updateServer("event", message);
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
