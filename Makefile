LIBS    = -pthread -lpthread -lCppLinuxSerial
VER 	= -std=c++17

PKG-LIBS = opencv4
PKG-CON = `pkg-config --cflags --libs $(PKG-LIBS)`

all:
	
	g++ $(VER) -o math.o main.cpp $(LIBS) $(PKG-CON)

opt:
	
	g++ -O3 $(VER) -o math.o main.cpp $(LIBS) $(PKG-CON)
#~ 	echo "makefile time!"
#~ 	./math.o 7 30 40
	
donot:
	g++ -c main.cpp $(LIBS)
clean:
	rm *.o
