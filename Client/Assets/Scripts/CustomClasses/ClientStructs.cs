using System;

[Serializable]
struct JsonReq
{
    public string reqType;
    public int valx;
    public int valy;
    public JsonReq(string reqType, int valx, int valy)
    {
        this.reqType = reqType;
        this.valx = valx;
        this.valy = valy;
    }
}
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
[Serializable]
struct InitialData
{
    public int lenghtx;
    public int lenghty;
    public Enemy[] enemies;
    public EspecialTile[] otherObj;
    public InitialData(int lenghtx, int lenghty, Enemy[] enemies, EspecialTile[] otherObj){
        this.lenghtx = lenghtx;
        this.lenghty = lenghty;
        this. enemies = enemies;
        this.otherObj = otherObj;
    }
}
