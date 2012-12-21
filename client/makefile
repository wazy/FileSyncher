#make client binary
client: splitter.o TimeComparison.o client.o
	gcc -o ./bin/client splitter.o TimeComparison.o client.o -lpthread

#client object
client.o: client.c client_func.h
	gcc -c client.c

#TimeComparison object
TimeComparison.o: TimeComparison.c client_func.h
	gcc -c TimeComparison.c

#splitter object
splitter.o: splitter.c client_func.h
	gcc -c splitter.c

#what to do when make clean
clean:
	rm *.o ./bin/client

# NYI
install:
	cp client /home/user/FileSyncher
