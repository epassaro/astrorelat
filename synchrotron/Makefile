CC = g++
CXX = g++
CXXFLAGS = -Wall -O3
LIBS = -lgsl -lgslcblas -lm

all: program

program: quad.o main.o
	$(CXX) -o a.out quad.o main.o $(LIBS)

%.o: %.cpp
	$(CXX) -c $< 

plot:
	@gnuplot sync.gp

clean:
	rm -f *.o *.dat *.png a.out 