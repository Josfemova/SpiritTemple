using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

public sealed class Client
{
    private readonly object updateLock = new object();
    private static readonly Client instance = new Client();
    private Socket serverConnection;
    public int health = 3; //registers lives across levels
    static Client() { }
    private Client()
    {
        tcpConnectionStart();
    }
    ~Client()
    {
        Debug.Log("releasing socket");
        updateServer("kill", "kill");
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
    /// <summary>
    /// Sends a message to the server and waits for a response
    /// </summary>
    /// <param name="type">type of request</param>
    /// <param name="message">content of the message to be sent</param>
    /// <returns>commands to be processed by client</returns>
    public String updateServer(string type, string message)
    {
        lock (updateLock)
        {
            int arraySize = 128;
            if (type == "loadLevel")
            {
                serverConnection.Send((byte[])Encoding.ASCII.GetBytes("loadLevel"));

            }
            else if (type == "event")
            {
                serverConnection.Send((byte[])Encoding.ASCII.GetBytes("event"));
            }
            byte[] msg = Encoding.ASCII.GetBytes(message);
            serverConnection.Send(msg);
            byte[] bytes = new byte[arraySize];
            int response = serverConnection.Receive(bytes);
            return Encoding.ASCII.GetString(bytes, 0, response);
        }
    }
    

}