objects = main.o
CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11

edit: $(objects)
	@echo "Linking executable edit..."
	$(CXX) -o edit $(objects)

main.o: main.cpp include/constants.h include/operator.h
	@echo "Compiling main.cpp to main.o..."
	$(CXX) $(CXXFLAGS) -c main.cpp

.PHONY: clean
clean:
	@echo "Cleaning up generated files..."
	-rm -f edit $(objects)
