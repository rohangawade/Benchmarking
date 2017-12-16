excecute=./cpu 
excecute1=./a.out

experiment1:
	gcc -o cpu CPU.c -pthread
	$(excecute) 
experiment2:
	gcc -mavx CPUAVX.c -pthread
	$(excecute1) 
