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

    public void resolveEvent(string message)
    {
        lock (updateLock)
        {
            byte[] bytes = new byte[1024];
            byte[] msg = Encoding.ASCII.GetBytes(message);
            int request = serverConnection.Send(msg);
            int response = serverConnection.Receive(bytes);
            Debug.Log("Server response = " + Encoding.ASCII.GetString(bytes, 0, response));
        }
    }

}