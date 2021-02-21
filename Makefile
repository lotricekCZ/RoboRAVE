LIBS    = -pthread -lpthread -lCppLinuxSerial
VER 	= -std=c++17
COMP	= g++


PKG-LIBS = opencv4
PKG-CON = `pkg-config --cflags --libs $(PKG-LIBS)`

all:
	$(COMP) $(VER) -o math.o main.cpp $(LIBS) $(PKG-CON) -I ./libtorch/lib/include/  -L ./libtorch/lib/ -ltorch -lcaffe2 -lc10 -lpthread -lX11

opt:
	$(COMP) -O3 $(VER) -o math.o main.cpp $(LIBS) $(PKG-CON)

depression:
	$(COMP) -Wall $(VER) -o math.o main.cpp $(LIBS) $(PKG-CON)
#~ 	echo "makefile time!"
#~ 	./math.o 7 30 40
	
illegal:
	$(COMP) -c main.cpp $(LIBS)
clean:
	rm *.o
