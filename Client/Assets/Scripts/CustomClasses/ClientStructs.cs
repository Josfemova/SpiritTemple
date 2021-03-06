using System;

/// <summary>
/// STruct to store representation of server commands
/// </summary>
[Serializable]
struct ServerCmd
{
    public int ID;
    public string instruction;
    public ServerCmd(int id, string cmd)
    {
        ID = id;
        instruction = cmd;
    }
}
/// <summary>
/// struct to represent json client requests
/// </summary>
[Serializable]
struct JsonReq
{
    public string cmd;
    public string args;
    public int target;//-1 means player
    public int valx;
    public int valy;
    public int otherval;
    public JsonReq(string cmd, string args="", int target=-1, int valx = 0, int valy = 0, int otherval = 0)
    {
        this.cmd = cmd;
        this.args = args;
        this.target = target;
        this.valx = valx;
        this.valy = valy;
        this.otherval = otherval;
    }
}
/// <summary>
/// Struct to facilitate serialization from the server information
/// </summary>
[Serializable]
struct JsonReqArr{
    public JsonReq[] commands;
    JsonReqArr(JsonReq[] commands){
        this.commands = commands;
    }
}
/// <summary>
/// struct to store player info to be sent to the server as json
/// </summary>
[Serializable]
struct PlayerInfo
{
    public int ID;
    public int gridx;
    public int gridy;
    public PlayerInfo(int id, int gridx, int gridy)
    {
        this.ID = id;
        this.gridx = gridx;
        this.gridy = gridy;
    }
}
/// <summary>
/// Struct for Item information serializtion
/// </summary>
[Serializable]
struct Item
{
    public int ID;
    public string type;
    public int gridx;
    public int gridy;
    public Item(int id, string type, int gridx, int gridy)
    {
        this.ID = id;
        this.type = type;
        this.gridx = gridx;
        this.gridy = gridy;

    }
}
/// <summary>
/// Struct for enemy data json serialization
/// </summary>
[Serializable]
struct Enemy
{
    public int ID;
    public string type;
    public int gridx;
    public int gridy;
    public Enemy(int id, string type, int gridx, int gridy)
    {
        this.ID = id;
        this.type = type;
        this.gridx = gridx;
        this.gridy = gridy;

    }
}
/// <summary>
/// simple struct to indicate which tiles are especial tiles
/// </summary>
[Serializable]
struct EspecialTile
{
    public string type;
    public int gridx;
    public int gridy;
    public EspecialTile(string type, int gridx, int gridy)
    {
        this.type = type;
        this.gridx = gridx;
        this.gridy = gridy;

    }
}
/// <summary>
/// struct that represents initial payload to be delivered to the server on level start
/// </summary>
[Serializable]
struct InitialData
{

    public int lengthx;
    public int lengthy;
    public PlayerInfo player;
    public Enemy[] enemies;
    public Item[] items;
    public EspecialTile[] otherObj;
    public string end;
    public InitialData(int lengthx, int lengthy, PlayerInfo player, Enemy[] enemies, Item[] items, EspecialTile[] otherObj)
    {
        this.lengthx = lengthx;
        this.lengthy = lengthy;
        this.player = player;
        this.enemies = enemies;
        this.items = items;
        this.otherObj = otherObj;
        this.end = "end of message";
    }
}
