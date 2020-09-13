# Author Philip Zhang
# Created on 08/11/2018

obj = keywordcounter.o FibonacciHeap.o

keywordcounter: $(obj)
	g++ -o keywordcounter $(obj)
	
keywordcounter.o: keywordcounter.cpp FibonacciHeap.h
	g++ -c keywordcounter.cpp
	
FibonacciHeap.o: FibonacciHeap.cpp FibonacciHeap.h
	g++ -c FibonacciHeap.cpp
	
clean:
	rm -rf $(obj) output_file.txt keywordcounter