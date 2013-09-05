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

Currently, there are three available scaling schemes:

* ``linear`` scales the vibration linearly from its maximum to its
  minimum, starting at the minimum range and ending at the maximum detectable
  range.
* ``logarithmic`` scales the vibration logarithmically from its maximum to its
  minimum from the minimum to the maximum detectable range.
* ``bilinear`` scales the first half of the detectable range more steeply than
  the second, providing the user with a higher "resolution" at close range (at
  the current range under 2m).
