CXX = g++
CXXFLAGS = -Wall

proj3: treap.o driver.cpp
	$(CXX) $(CXXFLAGS) treap.o driver.cpp -o proj3

treap.o: treap.h treap.cpp
	$(CXX) $(CXXFLAGS) -c treap.cpp

run:
	./proj3

val:
	valgrind proj3

clean:
	rm *~

cleaner:
	rm *~
	rm *.o
