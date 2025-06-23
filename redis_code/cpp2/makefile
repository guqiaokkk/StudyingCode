.PHONY:all
all:hash zset

hash:hash.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread

zset:zset.cc
	g++ -o $@ $^ -std=c++17 /usr/local/lib/libredis++.a /usr/lib/x86_64-linux-gnu/libhiredis.a -pthread

.PHONY:clean
clean:
	rm -f hash
	rm -f zset
