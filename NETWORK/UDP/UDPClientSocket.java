import java.io.*;
import java.util.*;
import java.net.*;

class UDPClient implements Runnable
{
	int port_num =5004;
	int blockSize = 64000;
	public static DatagramSocket client_socket;
	public int threadInit;
	public double start_time,end_time;
	long fileSize;
	public int num_thread;
	
	public void establishConnection()
	{
		try
		{
			Scanner scr= new Scanner(System.in);
			
			System.out.println("Enter number of threads"); 
			int num_threads = scr.nextInt();
			client_socket = new DatagramSocket();
			System.out.println("Number of threads"+num_threads);
			for(int nt_thread = 1;nt_thread<=num_threads;nt_thread++)				{

					UDPClient udpc = new UDPClient();
					
					System.out.println("Thread = "+nt_thread);
					udpc.threadInit = nt_thread;
					new Thread(udpc).start();
					Thread.sleep(1000);
				}	
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}	
		
	}
	public void send_receiveData()
	{
		try
		{
			File file = new File("FileRead.txt");
			fileSize = file.length();
			byte [] sendData = new byte[blockSize];	
			
			FileInputStream fileinput = new FileInputStream(file);
			InetAddress inet_address = InetAddress.getByName("127.0.0.1");
			int readptr = 0 , totalsize = 0;
			start_time = System.currentTimeMillis();
			
			while((readptr = fileinput.read(sendData))>0)
			{

				DatagramPacket datapkt_Client = new DatagramPacket(sendData, sendData.length, inet_address, 5005);
				totalsize = totalsize +readptr; 

				client_socket.send(datapkt_Client);

				byte [] recData = new byte[blockSize];	
				datapkt_Client = new DatagramPacket(recData,recData.length);
				client_socket.receive(datapkt_Client);
			}
			end_time = System.currentTimeMillis();
			calculateBenchMark();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}	
	
	}	
	public void calculateBenchMark()
	{
		double timediff = end_time - start_time;
		
		timediff = timediff/1000;
		System.out.println("Performance of thread ="+threadInit);
	
		System.out.println("Execution Time in "+timediff+"sec");	
		double throughput = (2*((fileSize*8)/(1024.0*1024.0)))/(timediff);
		System.out.println("Throughput in "+throughput+"Mbps");
		double latency = (timediff*1000)/2;
		System.out.println("Latency = "+latency+"ms");
	}

	public void run()
	{
		send_receiveData();
	}
}
public class UDPClientSocket
{
	public static void main(String args[])
	{
		UDPClient udp = new UDPClient();
		udp.establishConnection();
	}
}
	
