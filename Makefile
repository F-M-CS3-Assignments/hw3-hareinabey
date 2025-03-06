all:
	g++ -g -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -g -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
	g++ -g -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt

run:
	valgrind --leak-check=full ./pdt

try: all run
