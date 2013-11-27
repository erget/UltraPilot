ULTRASONIC_DEPENDENCIES=src/sensors.o
RANGEFINDER_DEPENDENCIES=$(ULTRASONIC_DEPENDENCIES) \
						 src/ultrasonic_sensor.o \
                         src/vibration_motor.o   \
                         src/vibration_scalers.o
MAIN_DEPENDENCIES=src/rangefinder.o $(RANGEFINDER_DEPENDENCIES)

CFLAGS=-c -std=c++0x
OBJS=src/main.o $(MAIN_DEPENDENCIES)
EXTERNAL_LIBS=external/wiringPi/wiringPi/wiringSerial.o \
   	          external/wiringPi/wiringPi/wiringPi.o	    \
              external/wiringPi/wiringPi/piHiPri.o	    \
  	          /lib/arm-linux-gnueabihf/libpthread.so.0
EXE=Debug/UltraPilot-1

all:	$(EXE)

$(EXE):	$(OBJS) $(EXTERNAL_LIBS)
	$(CXX) $(OBJS) $(EXTERNAL_LIBS) -o $(EXE)

src/main.o:	src/main.cpp $(MAIN_DEPENDENCIES)
	$(CXX) $(CFLAGS) src/main.cpp -o src/main.o
	
src/rangefinder.o: src/rangefinder.hpp src/rangefinder.cpp
	$(CXX) $(CFLAGS) src/rangefinder.cpp -o src/rangefinder.o
	
src/vibration_motor.o: src/vibration_motor.hpp src/vibration_motor.cpp
	$(CXX) $(CFLAGS) src/vibration_motor.cpp -o src/vibration_motor.o
	
src/vibration_scalers.o: src/vibration_scalers.hpp src/vibration_scalers.cpp
	$(CXX) $(CFLAGS) src/vibration_scalers.cpp -o src/vibration_scalers.o

src/ultrasonic_sensor.o: src/ultrasonic_sensor.hpp src/ultrasonic_sensor.cpp
	$(CXX) $(CFLAGS) src/ultrasonic_sensor.cpp -o src/ultrasonic_sensor.o

src/sensors.o: src/sensors.hpp src/sensors.cpp
	$(CXX) $(CFLAGS) src/sensors.cpp -o src/sensors.o
												 
clean:
	rm -f $(OBJS) $(EXE)
