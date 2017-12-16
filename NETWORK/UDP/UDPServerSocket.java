import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.*;

class UDPServer implements Runnable
{
	public static DatagramSocket dg_serv_socket = null;
	public int numOfThreads;
	public static int thread_ID;	 
	File fileupload;
	public static int port_num = 5004;
	public int blockSize = 64000;
	public void startUDPServer()
	{
		try
		{
			System.out.println("Server is started");
			Scanner scr = new Scanner(System.in);
		
			dg_serv_socket = new DatagramSocket(port_num);
			System.out.println("Enter the number of threads");
			int num_threads = scr.nextInt();
		 
			//Create client connection
				
			dg_serv_socket= new DatagramSocket(5005);

			for(int i = 1; i<= num_threads; i++)
			{

				UDPServer server_udp = new UDPServer();
				server_udp.thread_ID = i;
				new Thread(server_udp).start();
				Thread.sleep(1000);
		
			}	
		}
		catch(Exception e)
		{
			System.out.println("error");
			e.printStackTrace();
		}
	}

	public void receive_sendData()
	{
		try
		{
			File fileUpload = new File("ClientUpload.txt");
			while(true)
			{
			byte[] dataReceive = new byte[blockSize];
			DatagramPacket datapkt = new DatagramPacket(dataReceive,dataReceive.length);
			dg_serv_socket.receive(datapkt);
			dataReceive =datapkt.getData();	
			datapkt =  new DatagramPacket(dataReceive,dataReceive.length,datapkt.getAddress(),datapkt.getPort());
			dg_serv_socket.send(datapkt);	
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
			
	}
	public void run()
	{
		
		receive_sendData();		
	}

}

public class UDPServerSocket
{
	public static void main(String args[])
	{
		UDPServer us = new UDPServer();
		us.startUDPServer();	
	}
}
