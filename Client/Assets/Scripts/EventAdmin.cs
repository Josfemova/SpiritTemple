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
    private GameObject[] enemies;
    private GameObject[] items;
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        playerScript = player.GetComponent(typeof(Player)) as Player;
        groundMap = GameObject.FindGameObjectWithTag("GroundTile").GetComponent(typeof(Tilemap)) as Tilemap;
        obstacleMap = GameObject.FindGameObjectWithTag("ObstacleTile").GetComponent(typeof(Tilemap)) as Tilemap;
        safeSpaceMap = GameObject.FindGameObjectWithTag("SafeSpaces").GetComponent(typeof(Tilemap)) as Tilemap;
        enemies = GameObject.FindGameObjectsWithTag("Enemy");
        items = GameObject.FindGameObjectsWithTag("Item");
        loadInServer();
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
            if (!obstacleMap.HasTile(newPosition) && !(overlapsOne(newPosition, enemies))
            && !(overlapsOne(newPosition, items)))
            {
                player.transform.position = newPosition;
            }
            JsonReq req = new JsonReq("movePlayer", newPosition.x, newPosition.y);
            //Client.Instance.updateServer("event",JsonUtility.ToJson(req));
            Debug.Log(JsonUtility.ToJson(req));
        }
    }
    private bool overlapsOne(Vector3Int comparePosition, GameObject[] collection)
    {
        Vector3Int objPos;
        foreach (GameObject x in collection)
        {
            objPos = Vector3Int.FloorToInt(x.transform.position);
            if (objPos == comparePosition)
                return true;
        }
        return false;
    }
    private void executeServerCmd(string cmds)
    {

    }
    private void loadInServer()
    {
        int lenghtx = groundMap.size.x;
        int lenghty = groundMap.size.y;
        CEList<Enemy> enemylist = new CEList<Enemy>();
        CEList<Item> itemlist = new CEList<Item>();
        CEList<EspecialTile> objlist = new CEList<EspecialTile>();

        foreach (GameObject x in enemies)
        {
            Vector3Int coord = groundMap.WorldToCell(x.transform.position);
            EnemyContainer enemyScript = x.GetComponent(typeof(EnemyContainer)) as EnemyContainer;
            Enemy newEnemy = new Enemy(x.GetInstanceID(), enemyScript.enemyType, coord.x, coord.y);
            enemylist.push(newEnemy);
        }
        foreach (GameObject x in items)
        {
            Vector3Int coord = groundMap.WorldToCell(x.transform.position);
            ItemContainer itemScript = x.GetComponent(typeof(ItemContainer)) as ItemContainer;
            Enemy newEnemy = new Enemy(x.GetInstanceID(), itemScript.itemType, coord.x, coord.y);
        }
        for (int i = 0; i < lenghtx;i++)
        {
            for (int j = 0; j < lenghty; j++)
            {
                Vector3Int testLocation = new Vector3Int(i, j, 0);
                if (obstacleMap.HasTile(testLocation))
                    Debug.Log(testLocation);
            }
        }

    }
}
[Serializable]
struct test
{
    public Enemy[] items;
}

