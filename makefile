server:
	g++ src/server.cpp -o out/server
	./out/server

client:
	g++ src/client.cpp -o out/client
	./out/client