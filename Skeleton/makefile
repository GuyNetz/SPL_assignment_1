# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.

all: link

link: compile
	@echo "linking object files"
	g++ -o bin/main bin/main.o bin/Settlement.o

compile: src/main.cpp src/Settlement.cpp
	@echo "compiling source code"
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp
	
clean:
	@echo "Cleaning bin directory"
	rm -rf bin/*







