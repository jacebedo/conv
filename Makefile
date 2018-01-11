conv: conv.cpp ./functions/functions.cpp
	g++ -o conv conv.cpp ./functions/functions.cpp -lsqlite3 -std=c++11
