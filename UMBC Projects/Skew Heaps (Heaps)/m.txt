CXX = g++
CXXFlags = -Wall

proj4: SkewHeap.o test0.cpp
	$(CXX) $(CXXFLAGS) SkewHeap.o test0.cpp -o proj4

SkewHeap.o: SkewHeap.h SkewHeap.cpp
	$(CXX) $(CXXFLAGS) -c SkewHeap.cpp

run:
	./proj4

val:
	valgrind proj4

clean:
	rm *~

cleaner:
	rm *~
	rm *.o
