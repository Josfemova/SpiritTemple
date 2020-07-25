using System;
using System.Threading;
using System.Threading.Tasks;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;
using UnityEngine.SceneManagement;
public class EventAdmin : MonoBehaviour
{
    private GameObject player;
    private Player playerScript;
    private Tilemap groundMap;
    private Tilemap obstacleMap;
    private Tilemap safeSpaceMap;
    private GameObject[] enemies;
    private GameObject[] items;
    void Awake()
    {
        QualitySettings.vSyncCount = 0;
        Application.targetFrameRate = 15;
    }
    /// <summary>
    /// gets initial data
    /// </summary>
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
    /// <summary>
    /// checks if any event needs to be reported to the server
    /// </summary>
    void Update()
    {
        if (Input.GetKey("escape"))
        {
            Application.Quit();
        }
        JsonReq req = new JsonReq("no-action");
        Vector3 change = Vector3.zero;
        change.x = Input.GetAxisRaw("Horizontal");
        change.y = Input.GetAxisRaw("Vertical");
        if (Input.GetKeyDown("j"))
        {
            //attacks an enemy??
            GameObject targ = playerScript.whoWasAttacked(enemies);
            if (targ != null)
            {
                EnemyContainer enemyScript = targ.GetComponent(typeof(EnemyContainer)) as EnemyContainer;
                if (enemyScript.sameOrientation(playerScript.OrientationX, playerScript.OrientationY))
                {
                    //kill enemy
                    req = new JsonReq("kill-enemy", target: targ.GetInstanceID());
                    targ.SetActive(false);
                    enemyScript.teleport(-2,-2);
                }
                else
                {
                    req = new JsonReq("hit-enemy", target: targ.GetInstanceID());
                }
            }
            targ = playerScript.whoWasAttacked(items);
            if (targ != null)
            {
                ItemContainer itemScript = targ.GetComponent(typeof(ItemContainer)) as ItemContainer;
                if (itemScript.itemType == "jar")
                {
                    req = new JsonReq("open-jar", target: targ.GetInstanceID());
                    itemScript.openJar();

                }
                else
                {
                    req = new JsonReq("open-chest", target: targ.GetInstanceID());
                    itemScript.openChest();

                }

            }

        }
        else if (Input.GetKeyDown("k"))
        {
            req = new JsonReq("player-shield"); //Server should interpretate this as player being safe
        }
        else if (change != Vector3.zero)
        {
            Vector3Int newPosition = Vector3Int.FloorToInt(player.transform.position + change);
            if (!obstacleMap.HasTile(newPosition) && !(overlapsOne(newPosition, enemies))
            && !(overlapsOne(newPosition, items)))
            {

                playerScript.move(newPosition);
                req = new JsonReq("move-player", valx: newPosition.x, valy: newPosition.y);
            }
        }
        syncServer("event", JsonUtility.ToJson(req));
    }
    /// <summary>
    /// Checks if the given position collides with one of the positions of the GameOBject collection given
    /// </summary>
    /// <param name="comparePosition">current position</param>
    /// <param name="collection">collection to compare against</param>
    /// <returns>true if there is a collision, false otherwise</returns>
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

    /// <summary>
    /// gets called once per instantiation, loads client information in the server
    /// </summary>
    private void loadInServer()
    {
        int lengthx = groundMap.size.x;
        int lengthy = groundMap.size.y;
        CEList<Enemy> enemylist = new CEList<Enemy>();
        CEList<Item> itemlist = new CEList<Item>();
        CEList<EspecialTile> objlist = new CEList<EspecialTile>();

        foreach (GameObject x in enemies)
        {
            Vector3Int coord = groundMap.WorldToCell(x.transform.position);
            EnemyContainer enemyScript = x.GetComponent(typeof(EnemyContainer)) as EnemyContainer;
            Enemy newEnemy = new Enemy(x.GetInstanceID(), enemyScript.enemyType, coord.x, coord.y);
            Debug.Log(x.name + x.GetInstanceID().ToString());
            enemylist.push(newEnemy);
        }
        foreach (GameObject x in items)
        {
            Vector3Int coord = groundMap.WorldToCell(x.transform.position);
            ItemContainer itemScript = x.GetComponent(typeof(ItemContainer)) as ItemContainer;
            Item newItem = new Item(x.GetInstanceID(), itemScript.itemType, coord.x, coord.y);
            itemlist.push(newItem);
        }
        for (int i = 0; i < lengthx; i++)
        {
            for (int j = 0; j < lengthy; j++)
            {
                Vector3Int testLocation = new Vector3Int(i, j, 0);
                if (obstacleMap.HasTile(testLocation))
                {
                    objlist.push(new EspecialTile("obstacle", i, j));
                }
                else if (safeSpaceMap.HasTile(testLocation))
                {
                    objlist.push(new EspecialTile("safeSpace", i, j));
                }
            }
        }
        Vector3Int coordp = groundMap.WorldToCell(player.transform.position);
        PlayerInfo playerinfo = new PlayerInfo(player.GetInstanceID(), coordp.x, coordp.y);
        InitialData gameState = new InitialData(
            lengthx, lengthy, playerinfo, enemylist.asArray(), itemlist.asArray(), objlist.asArray()
        );
        string message = JsonUtility.ToJson(gameState, true);
        syncServer("loadLevel", message);
    }
    /// <summary>
    /// reports what happened in this frame to the server
    /// </summary>
    /// <param name="type">type of request</param>
    /// <param name="message">json payload</param>
    void syncServer(string type, string message)
    {
        try
        {
            String cmd = Client.Instance.updateServer(type, message);
            JsonReqArr arr = JsonUtility.FromJson<JsonReqArr>(cmd);
            foreach (JsonReq req in arr.commands)
            {
                executeServerCmd(req);
            }
        }
        catch
        {
            //Debug.Break();
        }
    }
    /// <summary>
    /// decodes json response given by the server
    /// </summary>
    /// <param name="req">json request sent by the server</param>
    private void executeServerCmd(JsonReq req)
    {
        //Debug.Log(JsonUtility.ToJson(req));
        EnemyContainer script;
        CanvasHealth health = GameObject.FindGameObjectWithTag("hearts").GetComponent(typeof(CanvasHealth)) as CanvasHealth;
        CanvasScore score = GameObject.FindGameObjectWithTag("score").GetComponent(typeof(CanvasScore)) as CanvasScore;
        switch (req.cmd)
        {
            case "set-lives":
                //Debug.Log("changed lifes");
                Client.Instance.health = req.otherval;
                health.health = req.otherval;
                break;
            case "move-enemy":
                script = getEntityByID(req.target, "enemy") as EnemyContainer;
                Vector3Int change = Vector3Int.zero;
                change.x = req.valx;
                change.y = req.valy;
                script.move(change);
                break;
            case "teleport-enemy":
                script = getEntityByID(req.target, "enemy") as EnemyContainer;
                script.teleport(req.valx, req.valy);
                break;
            case "attack-player":
                Client.Instance.health = req.otherval;
                health.health = req.otherval;
                /// trigger animation?
                break;
            case "set-score":
                //Debug.Log("changed score");
                Client.Instance.score = req.otherval;
                break;
            case "kill-player":
                SceneManager.LoadScene(0); // starts from level 1
                break;
            default:
                break;
        }
    }

    /// <summary>
    /// Returns reference to script of a game object based on its instance ID
    /// </summary>
    /// <param name="id">instance id</param>
    /// <param name="type">tag of the game object</param>
    /// <returns></returns>
    private MonoBehaviour getEntityByID(int id, String type)
    {
        GameObject obj = null;
        if (type == "enemy")
        {
            foreach (GameObject x in enemies)
            {
                if (x.GetInstanceID() == id)
                {
                    obj = x;
                    break;
                }
            }
        }
        else
        {
            foreach (GameObject x in items)
            {
                if (x.GetInstanceID() == id)
                {
                    obj = x;
                    break;
                }
            }
        }
        if (obj == null)
            throw new ArgumentException("Invalid object ID");
        MonoBehaviour script = obj.GetComponent(typeof(MonoBehaviour)) as MonoBehaviour;
        return script;
    }
}


