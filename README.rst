##########
UltraPilot
##########

UltraPilot is a system for coupling remote sensing ranging data with haptic
feedback, developed primarily with the goal of helping visually impaired
persons be able to independently navigate unfamiliar territory without the
disadvantages of traditional sight aids.

The library contains facilities to obtain ranging data from an ultrasonic
sensor using a Raspberry Pi and produce vibrotactile feedback using
vibrotactors that are also attached to a Raspberry Pi. The feedback from a
single sensor can be scaled across multiple vibrotactors.

In order to autostart it when the Pi is started, call it from
``/etc/rc.local``.

============
Dependencies
============

In order to compile UltraPilot, the compiled sources from `wiringPi
<http://wiringpi.com/>`_ need to be available. The ``Makefile`` includes an
example of how to link them. Remember to change the paths as necessary to match
your setup.

===========
Basic usage
===========

The package contains an example main program which connects a single ultrasonic
sensor and a single vibrotactor.  The currently maximum ultrasonic range is set
to 400 cm. The ``gpio`` API allows PWM intensities on a scale of 1 to 1023,
which means that that is the "resolution" of values sent to the vibration
motor.

For more information on how to use the program, call it without arguments.
