.PHONY:all
all:list string

list:list.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread

string:string.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread

hello:hello.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread

generic:generic.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread


.PHONY:clean
clean:
	rm -f hello
	rm -f generic
	rm -f string
	rm -f list
