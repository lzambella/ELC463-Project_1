CC=g++
DEPS=cache.h FIFOSet.h LRUSet.h Set.h cache_entry.h

make: app.cpp cache.cpp FIFOSet.cpp LRUSet.cpp cache_entry.cpp
	if [ ! -d "./binaries" ]; then mkdir ./binaries; fi
	$(CC) -o ./binaries/cache_sim app.cpp cache.cpp FIFOSet.cpp LRUSet.cpp cache_entry.cpp