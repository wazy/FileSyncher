#make client binary
client: splitter.o TimeComparison.o client.o
	gcc -o ./bin/client splitter.o TimeComparison.o client.o -lpthread

#client object
client.o: client.c client_func.h
	gcc -W -Wall -g -c client.c

#TimeComparison object
TimeComparison.o: TimeComparison.c client_func.h
	gcc -W -Wall -g -c TimeComparison.c

#splitter object
splitter.o: splitter.c client_func.h
	gcc -W -Wall -g -c splitter.c

#what to do when make clean
clean:
	rm -r *.o ./bin/client $(HOME)/FileSyncher/bin/

# NYI
install:
	mkdir $(HOME)/FileSyncher/bin/
	cp ./bin/client $(HOME)/FileSyncher/bin/
