BatPi
=====

BatPi reads the range detected by an ultrasonic sensor attached to a Raspberry
Pi and reports it as vibration output.

In order to autostart it when the Pi is started, call it from
``/etc/rc.local``.

############
Dependencies
############

In order to compile BatPi, the compiled sources from `wiringPi
<http://wiringpi.com/>`_ need to be available. The ``Makefile`` includes an
example of how to link them, remember to change the paths as necessary to match
your setup.

#################
Vibration scaling
#################

The currently maximum ultrasonic range is set to 400 cm. The ``gpio`` API
allows PWM intensities on a scale of 1 to 1023, which means that that is the
"resolution" of values sent to the vibration motor.

Currently, there are two branches controlling how vibration signals are sent to
the motor. ``main`` uses a linear scale for the vibration, which means that the
distance to faraway objects is scaled in vibration similarly to the distance of
nearby objects. Becaues nearby objects are often most relevant for navigation,
a second branch, ``logarithmic``, scales the vibration values logarithmically
in order to give the user finer signals for nearby objects at the loss of
information concerning faraway objects.

This is the logarithmic equation::

    y <- -236.7 * log2(x) + 2046

This is because this produces an amplitude of 1023 exactly, which matches my
vibration range, and it has its minimum at just about 0.

It would probably make sense to merge these two branches while preserving both
options, while allowing the user to specify whether he wants linear or
logarithmically scaled outputs.
