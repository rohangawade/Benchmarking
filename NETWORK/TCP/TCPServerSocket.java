import java.io.*;
import java.net.*;
import java.util.*;

class TCPServer implements Runnable
{
	private  ServerSocket tcp_serversocket;
	private Socket client_socket;
	DataInputStream dinput;
	DataOutputStream doutput;
	public int blockSize = 65536;
	public File fileUpload;
	String filename="";
	int port_num=5001;
	long client_filesize;
	public void startServer()
	{
		try
		{
			System.out.println("Starting the server");
			//creating the socket on port number
			
			Scanner scr = new Scanner(System.in);
			
			tcp_serversocket = new ServerSocket(port_num);
			System.out.println("Enter the number of threads");
			int num_threads = scr.nextInt();
			//wait for client socket connection
			Socket client_connect = tcp_serversocket.accept(); 
			if(client_connect!=null)
			{
				System.out.println("Client Connected");
				for(int nt_thread = 1;nt_thread<=num_threads;nt_thread++)				{
					
 					TCPServer tcpss = new TCPServer();
					tcpss.client_socket = client_connect;
					new Thread(tcpss).start();
					Thread.sleep(1000);
				}
			}
			else
			{
				System.out.println("Client not connected");
			}
	 	}
		catch(Exception e)
		{
		e.printStackTrace();	
	 	}		
	}
	public void readFromClient()	
	{
		try
		{
		//Read the file sent by the client
			dinput = new DataInputStream(client_socket.getInputStream());
			
			fileUpload = new File("ClientUpload.txt");
			client_filesize = dinput.readLong();

			FileOutputStream fileoutstream = new FileOutputStream(fileUpload);
			byte[] content = new byte[blockSize];
			int readptr =0,totalBytes = 0;
			while((readptr = dinput.read(content))>0)
			{

				fileoutstream.write(content,0,readptr);
				totalBytes = totalBytes + readptr;
				if((long)totalBytes >= client_filesize)
					break;	
			}
			

		}
		catch(Exception e)
		{
		e.printStackTrace();
		}
	}

	public void sendToClient()
	{
		try
		{
			int readptr = 0,totalBytes =0;
			byte[] content = new byte[blockSize];
			// read the file and store in output buffer
			doutput = new DataOutputStream(client_socket.getOutputStream());
			fileUpload = new File("ClientUpload.txt");
			FileInputStream fileinstream= new FileInputStream(fileUpload);
			while((readptr = fileinstream.read(content))>0)
			{
				doutput.write(content,0,readptr);
				totalBytes = totalBytes + readptr;
				if((long)totalBytes >= client_filesize)
					break;
			}	
			
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	@Override
	public void run()
	{

		readFromClient(); 

		sendToClient();	
	}
	
}

public class TCPServerSocket{
	public static void main(String args[]){
			TCPServer ts= new TCPServer();
			ts.startServer();

	}
}


