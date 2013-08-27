CFLAGS=-c
OBJS=src/main.o src/io.o
LIBS=external/wiringPi/wiringPi/wiringSerial.o
EXE=Debug/BatPie

all:	$(EXE)

$(EXE):	$(OBJS) $(LIBS)
	$(CXX) $(OBJS) $(LIBS) -o $(EXE)

main.o:	src/main.cpp io.o
	$(CXX) $(CFLAGS) src/main.cpp -o src/main.o
	
io.o: src/io.cpp src/io.h
	$(CXX) $(CFLAGS) src/io.cpp -o src/io.o

clean:
	rm -f $(OBJS) $(EXE)
