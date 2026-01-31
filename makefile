all: main

out = bin/
server = server/
client = client/
flag = -g

main: main.o send_recieve.o ui.o log_manager.o connection.o
	gcc $(out)main.o $(out)connection.o $(out)server.o $(out)client.o $(out)send_recieve.o $(out)ui.o $(out)log_manager.o -o $(out)application $(flag)

main.o: main.c
	gcc -c main.c -o $(out)main.o $(flag)

connection.o: connection.c
	gcc -c connection.c -o $(out)connection.o $(flag)

server.o: $(server)server.c
	gcc -c $(server)server.c -o $(out)server.o $(flag)

client.o: $(client)client.c
	gcc -c $(client)client.c -o $(out)client.o $(flag)

send_recieve.o: send_recieve.c
	gcc -c send_recieve.c -o $(out)send_recieve.o $(flag)

ui.o: ui.c
	gcc -c ui.c -o $(out)ui.o $(flag)

log_manager.o: logger/log_manager.c
	gcc -c logger/log_manager.c -o $(out)log_manager.o $(flag)

clean:
	rm -f $(out)*