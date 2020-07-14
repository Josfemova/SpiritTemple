using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

public sealed class Client
{
    private readonly object updateLock = new object();
    private static readonly Client instance = new Client();
    private Socket serverConnection;
    private int health = 3; //registers lives across levels
    static Client() { }
    private Client()
    {
        tcpConnectionStart();
    }
    ~Client()
    {
        Debug.Log("releasing socket");
        serverConnection.Shutdown(SocketShutdown.Both);
        serverConnection.Close();
    }
    public static Client Instance
    {
        get { return instance; }
    }

    private void tcpConnectionStart()
    {

        //Retrieves local IP adress
        IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
        IPAddress ipAddress = ipHostInfo.AddressList[0];
        //sets endpoint on ip adress
        IPEndPoint remoteEP = new IPEndPoint(ipAddress, 3000);

        // Create a TCP/IP  socket.  
        serverConnection = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
        serverConnection.Connect(remoteEP);


    }

    public void updateServer(string type,string message)
    {
        lock (updateLock)
        {
            int arraySize = 128;
            if(type == "loadLevel"){
                serverConnection.Send((byte[])Encoding.ASCII.GetBytes("loadLevel"));
                arraySize = 100000;
            }else if(type == "event"){
                serverConnection.Send((byte[])Encoding.ASCII.GetBytes("event"));
            }
            
            byte[] msg = Encoding.ASCII.GetBytes(message);
            int request = serverConnection.Send(msg);

            byte[] bytes = new byte[arraySize];
            int response = serverConnection.Receive(bytes);
            string srvcmd = Encoding.ASCII.GetString(bytes, 0, response);
            serverInstructions(srvcmd);
        }
    }
    private void serverInstructions(string cmd){

    }

}