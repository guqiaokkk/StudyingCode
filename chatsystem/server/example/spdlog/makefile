all : sync async main

main : main.cc	
	g++ -o $@ $^ -std=c++17 -lspdlog -lpthread -lgflags
	

sync : sync.cc
	g++ -o $@ $^ -std=c++17 -lspdlog -lpthread

async : async.cc
	g++ -o $@ $^ -std=c++17 -lspdlog -lpthread