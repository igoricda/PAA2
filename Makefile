# Variables
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

FILES := shortestPaths.cpp graph.cpp fileUtils.cpp minHeap.cpp

# Default target
all: main dijkstra bellmanFord

main: main.cpp $(FILES)
	$(CXX) $(CXXFLAGS) main.cpp $(FILES) -o main

dijkstra: dijkstra.cpp $(FILES)
	$(CXX) $(CXXFLAGS) dijkstra.cpp $(FILES) -o dijkstra

bellmanFord: bellmanFord.cpp $(FILES)
	$(CXX) $(CXXFLAGS) bellmanFord.cpp $(FILES) -o bellmanFord

# Clean
clean:
	rm -f main dijkstra bellmanFord

.PHONY: all clean
