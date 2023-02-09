build: cppcode/main.cpp
	g++ cppcode/main.cpp -o bin/backend -lpigpio -lrt -pthread -fpermissive
