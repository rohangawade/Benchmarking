
This assignment mainly consist of 4 parts below are the commands for running the desired part







1. CPU BENCHMARK: 


   To run the CPU benachmark the user must be having C compiler or  install gcc 

	
	a. Open command prompt redirect to the folder location  


	b. Use the commands below to complie and run the code


	c. To run the Normal Instructions for Interger Operations and Float Operations 

		
		make experiment1


	d. To run the AVX Instructions for Interger Operations and Float Operations 

       		
		make experiment2 
	


2. MEMORY BENCHMARK:

  
   To run the MEMORY benachmark the user must be having C compiler or  install gcc 

	
	a. Open command prompt redirect to the folder location  

	
	b. Use the commands below to complie and run the code


	c. To run the memory operations type 
		
		
		make experiment
	
	
	d. Four options will be shown 
		
		1. Sequential Read Write
	
		2. Random Read Write 
	
		3. Sequential Write 
		
		4. Random Write
	
	
	e. Select the reqiured operation







 



3.DISK BENCHMARK: 
	
 
   To run the DISK benachmark the user must be having C compiler or  install gcc 

	
	a. Open command prompt redirect to the folder location  


	b. Use the commands below to complie and run the code

	
	c. To write a file type  

	
		make experiment1

	
	d. If you want to increase the size of the file then in fwrite function increase  the second parameter 
	
	
	e. To run the disk operations type 
		
	
		make experiment2
	

	f. Four options will be shown 
		
		1. Sequential Read Write
		
		2. Random Read Write 
		
		3. Sequential Read 
		
		4. Random Read
	
	
	g. Select the reqiured operation











4.NETWORK BENCHMARK:

    
	To run the NETWORK benachmark the user must be having JAVA environment
 

	a. Open command prompt redirect to the folder location  

	
	b. Use the commands below to complie and run the code


	c. To write a file type  

		
		make experiment1

	
	d. If you want to increase the size of the file then in fwrite function increase  the second parameter 
	
	
	e. To run the TCP operations type 
		
	
		1. Open One Terminal for Server and type

			
			sh TCPServerscript.sh
	
	
		2. You need to enter the number of threads

	
		3. Open another termianl for Client and type 
	

			sh TCPClientrscript.sh 
	
	
		4. Again enter number of threads

	
	f. To run the UDP operations type 
		
	
		1. Open One Terminal for Server and type

	
			sh UDPServerscript.sh
	
		
		2. You need to enter the number of threads

		
		3. Open another termianl for Client and type 
	
		
			sh UDPClientrscript.sh 
	
		
		4. Again enter number of threads
				 
	

 
