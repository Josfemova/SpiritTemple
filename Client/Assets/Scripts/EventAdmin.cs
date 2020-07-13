using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;
public class EventAdmin : MonoBehaviour
{
    private GameObject player;
    private Player playerScript;
    private Tilemap groundMap;
    private Tilemap obstacleMap;
    private Tilemap safeSpaceMap;
    private GameObject[] Enemies;
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        playerScript = player.GetComponent(typeof(Player)) as Player;
        groundMap = GameObject.FindGameObjectWithTag("GroundTile").GetComponent(typeof(Tilemap)) as Tilemap;
        obstacleMap = GameObject.FindGameObjectWithTag("ObstacleTile").GetComponent(typeof(Tilemap)) as Tilemap;
        safeSpaceMap = GameObject.FindGameObjectWithTag("SafeSpaces").GetComponent(typeof(Tilemap)) as Tilemap;
        Enemies = GameObject.FindGameObjectsWithTag("Enemy");
    }
    // Update is called once per frame
    void Update()
    {
        Vector3 change = Vector3.zero;
        change.x = Input.GetAxisRaw("Horizontal");
        change.y = Input.GetAxisRaw("Vertical");
        if (Input.GetKeyDown(KeyCode.Space))
        {
            //attack routine
        }
        else if (change != Vector3.zero)
        {
            Vector3Int newPosition = Vector3Int.FloorToInt(player.transform.position + change);
            if (!obstacleMap.HasTile(newPosition) && !(enemyCollision(newPosition)))
            {
                player.transform.position = newPosition;
            }
            JsonReq req = new JsonReq("movePlayer", newPosition.x, newPosition.y);
            //Client.Instance.updateServer("event",JsonUtility.ToJson(req));
            Debug.Log(JsonUtility.ToJson(req));
        }
    }
    private bool enemyCollision(Vector3Int comparePosition)
    {
        Vector3Int enemyPos;
        foreach (GameObject x in Enemies)
        {
            enemyPos = Vector3Int.FloorToInt(x.transform.position);
            if (enemyPos == comparePosition)
            {
                return true;
            }
        }
        return false;
    }
    private void executeServerCmd(string cmds){

    }
}
[Serializable]
struct ServerCmd{
    public int ID;
    public string instruction;
    public ServerCmd(int id, string cmd){
        ID = id;
        instruction = cmd;
    }
}
