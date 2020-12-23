LIBS    = -pthread -lserial -lpthread
VER = -std=c++11

all:
	
	g++ $(VER) -o math.o main.cpp $(LIBS)
#~ 	echo "makefile time!"
#~ 	./math.o 7 30 40
	
donot:
	g++ -c main.cpp $(LIBS)
clean:
	rm *.o
