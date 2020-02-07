CC=g++
DEPS=cache.h FIFOSet.h LRUSet.h Set.h

make: app.cpp cache.cpp FIFOSet.cpp LRUSet.cpp 
	if [ ! -d "./binaries" ]; then mkdir ./binaries; fi
	$(CC) -o ./binaries/cache_sim app.cpp cache.cpp FIFOSet.cpp LRUSet.cpp