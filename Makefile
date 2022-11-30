CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)


exec: bin/exec

bin/exec: src/main.cpp src/graph.cpp src/utils.cpp
	${CXX} ${CXX_FLAGS} src/main.cpp src/graph.cpp src/utils.cpp -o bin/exec

.PHONY: clean exec 

clean:
		rm -fr bin/*
