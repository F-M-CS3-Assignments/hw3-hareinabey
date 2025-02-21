all: 
	g++ -Wall TimeCode.cpp TimeCodeTests.cpp -o tct

run: 
	./tct

try: all run
