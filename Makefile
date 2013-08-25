CFLAGS=-c
OBJS=src/main.o 
LIBS=external/wiringPi/wiringPi/wiringSerial.o
EXE=Debug/BatPie

all:	$(EXE)

$(EXE):	$(OBJS) $(LIBS)
	$(CXX) $(OBJS) $(LIBS) -o $(EXE)

main.o:	src/main.cpp
	$(CXX) $(CFLAGS) src/main.cpp -o src/main.o

clean:
	rm -f $(OBJS) $(EXE)
