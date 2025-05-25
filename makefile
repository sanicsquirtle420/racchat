.SILENT: server
server:
	g++ src/server.cpp -o out/server
	./out/server

.SILENT: client
client:
	g++ src/client.cpp -o out/client
	./out/client