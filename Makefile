all:
	g++ -o samp Driver.cpp -std=c++11

test: 
	g++ -o tester Test.cpp -std=c++11
	./tester
	
