CXX = g++
CXXFLAGS = -Wall

proj3: CTree.o Driver.cpp
	$(CXX) $(CXXFLAGS) CTree.o Driver.cpp -o proj3

CTree.o: CTree.h CTree.cpp
	$(CXX) $(CXXFLAGS) -c CTree.cpp

run:
	./proj3

clean:
	rm *~

cleaner:
	rm *~
	rm *.o
