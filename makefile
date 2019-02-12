all:list_test.cpp ulliststr.o
	g++ -g -Wall list_test.cpp ulliststr.o -o prog

ulliststr.o:ulliststr.cpp ulliststr.h
	g++ -g -Wall -c ulliststr.cpp -o ulliststr.o
