LIBS    = -pthread


all:
	
	g++ -o math.o main.cpp $(LIBS)
#~ 	echo "makefile time!"
#~ 	./math.o 7 30 40
	
clean:
	rm *.o
