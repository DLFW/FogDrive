.. _developers:

===========
Development
===========

To install Git on a Debian-flavor Linux, just install the ``git`` package by for example::

    apt-get install git
    



Building FogDrive
=================

So far, FogDrive was only built on Linux. It should not be a huge challange to port the build process to Windows, but so far the build works only on a Linux system.

FogDrive needs the following stuff to get built:

 * `avr-gcc`_ and `avr-libc`_, the free compiler tool chain and the free AVR libraries to compile the actual firmware
 * SCons_, the build orchestrator which runs the build process
 * Sphinx_ with the Alabaster_ theme, the documentation tool used to build this documentation
 
SCons and Sphinx depend on Python and some Python_ packages.
 
.. _avr-gcc: http://www.nongnu.org/avr-libc/
.. _avr-libc: http://www.nongnu.org/avr-libc/
.. _Scons: http://scons.org
.. _Sphinx: http://www.sphinx-doc.org
.. _Alabaster: alabaster.readthedocs.io
.. _Python: https://www.python.org

These software should be packaged for most Linux distributions. On a Debian flavor Linux, you can install evething by something like::

    apt-get install gcc-avr avr-libc scons python-sphinx python-alabaster 
    
Or leave the Alabster installation in the above command and install the Alabaster theme via pip::

    apt-get install python-pip
    pip install alabaster
    
