.PHONY:all
all:set list

list:list.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread

set:set.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread




.PHONY:clean
clean:
	rm -f list
	rm -f set