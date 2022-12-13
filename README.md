# CS225 Final Project - Open Flights

### Group members:
* Idrees Mohammed, imoha9
* Khatija Syeda, kasyeda2
* Zainab Sajid, zsajid2
* Abhi Thanvi, athanvi2

### Video Presentation
https://mediaspace.illinois.edu/media/t/1_4rho6pks/

## File Organization
We tried to mimic the CS 225 labs and mps as structures for our file organization!
* Documentations - Project Proposal and Team Contract
* bin - for running cmake
* entry - contains `main.cpp`
* src - has `airport.h`, `graph.h`, `graph.cpp`, `utils.cpp`, `utils.h`
* tests - `test.cpp`
* main folder - CSV datasets, `results.md`, an image of our self constructed sample graph, jupyter notebook (Python) csv cleaning, and presentation video

## How does our project work?
Our program uses data from [Open Flights](https://openflights.org/data.html) to find the shortest path between two airports.
We use BFS Traversal to find the shortest path from a starting airport to destination airport based on least amount of connected flights. We use Dijkstra's algorithm to find the shortest path from a starting airport to destination airport based on shortest numeric distance. NEED TO DO PAGERANK

Our presentation video: NEED TO DO

## Running Instructions

To download our program, copy and paste this line to your terminal:

```
git clone https://github.com/athanvi2/CS-225-Project.git
```

1. Create the build folder
```make
mkdir build
```
and then
```make
cd build
```
and finally run,
```make
cmake ..
```
*This is similar in method to cloning CS 225 release repo/setup*

2. To build the program, you can run:
```make
make
```
in the terminal.

3. Different Run Options: 
* To run main -run `./main`
* To run tests -run `./test`
* To run tests with time metrics -run `time ./test`
*These commands are expected to run in the build directory*

# What to expect:
* From `./test`:
*   We are running test cases regarding our constructor and BFS, Dijkstra, and PageRank algorithms.
*   You should be expecting to pass 18 tests
