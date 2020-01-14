CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: test

clean:
	rm test JsonAutograderOutput.o

JsonAutograderOutput.o: JsonAutograderOutput.cpp
	$(CXX) $(CXXFLAGS) JsonAutograderOutput.cpp -c

test-main.o: JsonAutograderOutput.o tests-main.cpp 
	$(CXX) $(CXXFLAGS) tests-main.cpp -c	

test: JsonAutograderOutput.o tests-main.o run-tests.cpp
	$(CXX) $(CXXFLAGS) JsonAutograderOutput.o tests-main.o run-tests.cpp -o test
