flags=-lcurl -lssh -pthread
compile=g++

nesca4: nesca4.o
	$(compile) -c nesca4.cpp $(flags)
	$(compile) -o nesca4 nesca4.o $(flags)
	rm -rf *.o 
