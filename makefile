all:list_test.cpp ulliststr.o
	g++ -g -Wall list_test.cpp ulliststr.o -o prog

stringparser:ulliststr.o stackstring.o stringparser.cpp
	g++ -g -Wall stringparser.cpp ulliststr.o stackstring.o -o prog

ulliststr.o:ulliststr.cpp ulliststr.h
	g++ -g -Wall -c ulliststr.cpp -o ulliststr.o

stackstrin.o: stackstring.cpp stackstring.h ulliststr.o
	g++ -g -Wall -c stackstring.cpp -o stackstring.o
