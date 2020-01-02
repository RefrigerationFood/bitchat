

all: client server

client:
	g++ chat_client.cpp -o client -std=c++11 -lpthread -lboost_system -lboost_thread

server:
	g++ chat_server.cpp -o server -std=c++11 -lpthread -lboost_system -lboost_thread