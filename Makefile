CFLAGS=-c
OBJS=src/main.o              \
		 src/rangefinder.o       \
		 src/ultrasonic_sensor.o \
		 src/vibration_motor.o   \
		 src/vibration_scalers.o
LIBS=external/wiringPi/wiringPi/wiringSerial.o \
   	 external/wiringPi/wiringPi/wiringPi.o	   \
	   external/wiringPi/wiringPi/piHiPri.o	     \
  	 /lib64/libpthread.so.0                    \
  	 /lib/arm-linux-gnueabihf/libpthread.so.0
EXE=Debug/BatPi

all:	$(EXE)

$(EXE):	$(OBJS) $(LIBS)
	$(CXX) $(OBJS) $(LIBS) -o $(EXE)

src/main.o:	src/main.cpp io.o
	$(CXX) $(CFLAGS) src/main.cpp -o src/main.o
	
src/rangefinder.o: src/rangefinder.hpp src/rangefinder.cpp         \
									 src/vibration_scalers.o src/ultrasonic_sensor.o \
									 src/vibration_motor.o
	$(CXX) $(CFLAGS) src/rangefinder.cpp -o src/rangefinder.o
	
src/ultrasonic_sensor.o: src/ultrasonic_sensor.hpp src/ultrasonic_sensor.cpp
	$(CXX) $(CFLAGS) src/ultrasonic_sensor.cpp -o src/ultrasonic_sensor.o
												 
src/vibration_motor.o: src/vibration_motor.hpp src/vibration_motor.cpp
	$(CXX) $(CFLAGS) src/vibration_motor.cpp -o src/vibration_motor.o
	
src/vibration_scalers.o: src/vibration_scalers.hpp src/vibration_scalers.cpp
	$(CXX) $(CFLAGS) src/vibration_scalers.cpp -o src/vibration_scalers.o

clean:
	rm -f $(OBJS) $(EXE)
