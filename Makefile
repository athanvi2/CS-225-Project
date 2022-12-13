CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cpp src/graph.cpp src/utils.cpp 
	${CXX} ${CXX_FLAGS} src/main.cpp src/graph.cpp src/utils.cpp  -o bin/exec

bin/tests: tests/tests.cc 
	${CXX} ${CXX_FLAGS} tests/tests.cc src/main.cpp src/graph.cpp src/utils.cpp -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
		rm -fr bin/*
