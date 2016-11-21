Backlog
=======

MOSFET drive
  Get a MOSFET switching the needed power with acceptable losses for a acceptable range of battery voltage.
  This is the very most basic basic way to drive a vaporizer.
  The voltage range of the battery should be fine for the control from 2.7 – 4,2 V. The MOSFET should always be quite saturated with that voltage to avoid a voltage drop at the MOSFET.

Voltage measurement
  Relaize a prototypic voltage measurement that works fine for the batteries voltage range.

Basic architecture
  Create the basic ideas of the fundamental architecture. Choose C or C++ as development language. Create a design for the separation of the applications core (we assume the firmware to be single-threaded and raw-on-chip), the power control parts (including the battery voltage measurement and the voltage control/switch with the coild resistance and maybe voltage/current measurement) and the user interface.

Realize the basic control
  As user interface, the serial port is fine at this point.

Basic build environment
  Set up the whole build chain properly. This shall include the documentation but have not to include a solution for the firmware download. Also the variation Management is not a must have here.

First FogDrive control (t.b.s.)
  Realize the first FogDrive control.

Publish Mira 0.1 :)