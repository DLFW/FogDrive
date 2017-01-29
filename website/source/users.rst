.. _users:

=====
Users
=====

So, if you’re a *modder* and want to build a mod with :ref:`mira` (the only FogDrive at the moment), this
page is for you.

The basic workflow
==================

What you should keep in mind!
=============================
→ safety

Micro-controllers
=================

.. _users_programming:

Programming a micro-controller
==============================

So, :ref:`mira` uses a μC which has to be programmed with the firmware. The firmware is a single file with the
file name suffix ``hex``. This kind of firmware is directly written to the flash. Many small devices nowadays that are running
on a μC use a bootloader. If a bootloader is “flashed” as basic firmware, the actual program can then be downloaded to
the μC by the help of a convienient PC application e.g. via a USB connection.

Mira does not support such a booloader and as of now, a bootloader feature has quite a low priority in the FogDrive development.
As a result, the firmware must be programmed via one of the μCs native interfaces.

Building the board
==================

License
=======