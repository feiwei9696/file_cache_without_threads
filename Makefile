CXX = gcc
FLAGS = -ggdb -Wall

main: main.c
	${CXX} ${FLAGS} -w -o file_cache file_cache.h file_cache.c main.c

clean:
	rm -f file_cache
