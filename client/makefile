#make client binary
client: GetLastModifiedTime.o TimeComparison.o client.o NetworkConnection.o
	gcc -o ./bin/client GetLastModifiedTime.o TimeComparison.o client.o NetworkConnection.o -lpthread

#client object
client.o: client.c client_func.h
	gcc -Wshadow -pedantic -Wall -Wextra -g -c client.c

#TimeComparison object
TimeComparison.o: TimeComparison.c client_func.h
	gcc -Wshadow -pedantic -Wall -Wextra -g -c TimeComparison.c

#GetLastModifiedTime object
GetLastModifiedTime.o: GetLastModifiedTime.c client_func.h
	gcc -Wshadow -pedantic -Wall -Wextra -g -c GetLastModifiedTime.c

#NetworkConnection object
NetworkConnection.o: NetworkConnection.c client_func.h
	gcc -Wshadow -pedantic -Wall -Wextra -g -c NetworkConnection.c

#what to do when make clean
clean:
	rm -r *.o ./bin/client $(HOME)/FileSyncher/bin/

# NYI
install:
	mkdir $(HOME)/FileSyncher/bin/
	cp ./bin/client $(HOME)/FileSyncher/bin/
