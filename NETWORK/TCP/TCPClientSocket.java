import java.io.*;
import java.util.*;
import java.net.*;

class TCPClient implements Runnable
{
        int port_num =5001;
        int blockSize = 65536;
        public static Socket client_socket;
        public int threadInit;
        DataOutputStream doutclient;
        DataInputStream dinclient;
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
                        client_socket = new Socket("127.0.0.1	",port_num);
                        System.out.println("Successful Connection");
                        System.out.println("Number of threads"+num_threads);
                        num_thread=num_threads;
                        for(int nt_thread = 1;nt_thread<=num_threads;nt_thread++)                               {

                                        TCPClient tcpc = new TCPClient();

                                        System.out.println("Thread = "+nt_thread);
                                        tcpc.threadInit = nt_thread;
                                        new Thread(tcpc).start();
                                        Thread.sleep(1000);
                                }

                }
                catch(Exception e)
                {
                        System.out.println("connection established");
                        e.printStackTrace();
                }
        }

        public void run()
        {
                try
                {
                        doutclient = new DataOutputStream(client_socket.getOutputStream());
                        File file = new File("FileRead.txt");
                        fileSize = file.length();
                        doutclient.writeLong(fileSize);
                        FileInputStream fileinclient =  new FileInputStream(file);
                        byte[] content = new byte[blockSize];

                        int readptr = 0 , totalsize = 0;
                        start_time = System.currentTimeMillis();

                        while((readptr = fileinclient.read(content))>0)
                        {

                                doutclient.write(content,0,readptr);
                                totalsize = totalsize +readptr;

                                if(totalsize == fileSize)
                                        break;

                        }

                         content = new byte[blockSize];
                        dinclient = new DataInputStream(client_socket.getInputStream());
                        File outfile = new File("DownloadServer.txt");
                        FileOutputStream  fileoutclient = new FileOutputStream(outfile);
                        readptr = 0;totalsize = 0;
                        while((readptr = dinclient.read(content))>0)
                        {
                                fileoutclient.write(content,0,readptr);
                                totalsize = totalsize + readptr;
                        }

                        end_time = System.currentTimeMillis();
                        double timediff = end_time - start_time;

                timediff = timediff/1000;
                System.out.println("Performance of thread ="+threadInit);


                double throughput = (2*((fileSize*8)/(1024.0*1024.0)))/(timediff);
                System.out.println("Throughput in "+throughput+"Mbps for Thread  "+threadInit);
                double latency = (timediff*1000)/2;
                System.out.println("Latency = "+latency+"ms for Thread "+threadInit);


                }
                catch(Exception e)
                {
                        e.printStackTrace();
                }
        }
}

public class TCPClientSocket
{
        public static void main(String args[]){
                        TCPClient tc= new TCPClient();
                        tc.establishConnection();

        }

}



