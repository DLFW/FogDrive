..  FogDrive (https://github.com/FogDrive/FogDrive)
    Copyright (C) 2016  Daniel Llin Ferrero

    This program, including it’s documenation and related circuit designs
    is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

.. FogDrive documentation master file, created by
   sphinx-quickstart on Thu Sep 29 23:41:44 2016.
   
   

===================
Welcome to FogDrive
===================

The FogDrive project aims to provide free and open source electronics for vaping devices, the so called “mods”.
This includes the circuit specifications, parts lists, proposals on how to build the actual board
and – last but not least – the firmware for the micro-controller which is part of the circuit.

FogDrive is a free and open project, published under the `GNU General Public License`_, version 3.

.. toctree::
    :hidden:

    mira
    users
    developers


FogDrive is under early development. Currently, it provides one simple working circuit in beta status, namely :ref:`mira`.
Each of the (hopefully) multiple circuits the project will provide in the future is called “a FogDrive”.
So, Mira is the first FogDrive the FogDrive project provides. :)



     
.. image:: images/mira_button.png
    :target: mira.html
    
Mira is the first simple FogDrive that just switches the vaporizer on and off via a MOSFET.
The vaporizer is driven directly by the battery. In addition, Mira supports a few tiny comfort
features like battery voltage supervision.

.. image:: images/users_button.png
    :target: users.html
     
Well, there are two kind of stakeholders of FogDrive, the *Modder* who builds and uses a FogDrive to build an actual vape mod,
and the *Vapor*, the end user, who uses a mod with a FogDrive to vape. :) While the latter one might only be interested in some
background information (you’re welcome to browse this pages, of course!), the “User Documentation” here addresses the modder
who has to build a FogDrive.

.. image:: images/developer_button.png
    :target: developers.html
    
     
You can also work on FogDrives sources, the circuits, the firmware or the documentation. You can do that to adapt the projects for your needs.
Since Mira for example does not have any possibility to get configured, the sources are the only way to – for example – change the four-time-click
for switching the device on and off into a triple click. Furthermore (and even better :)), you can help the project by contributing to the development.
Add some features or improve the circuits!
FogDrive could definitely need some help by some electronic geeks, micro-controller hackers
and even some modders who wants to figure out clever ways to integrate a FogDrive in self-build or reused mods.

FogDrive in the Web
===================

FogDrive is hosted on on `GitHub`_ at https://github.com/FogDrive/FogDrive.

If you have a GitHub account, feel free to use `Mira’s GitHub wiki`_ to get in contact.


.. _GitHub: http://github.com

.. _Mira’s GitHub wiki: https://github.com/FogDrive/FogDrive/wiki


Supporting FogDrive
===================

FogDrive needs support!
There are various ways to help the project. Using it and giving some feedback is the first one.
Constructive feedback and simply knowing that people are using or intrested in FogDrive will increase the motivation. :)

If you like the idea of FogDrive, you can support the Projekt also by making more people get to know about it.
Mention it in a forum, at your regulars’ table or wherever you think other people could be intrested.

Last but not least, you can help FogDrive by active participation. Get in contact via GitHub if you're intrested,
or simply fork the project on GitHub. Especially electronic geeks could fill a significant competency gap. ;)
For the long term goal of FogDrive – an up-to-date, fully regulated vaping circuit – it would be great to
have people in the team that can contribute to the design of the voltage converter. But also firmware
developers are welcome. Even if you would like to maintain the documentation or if you have an idea how enhance
the projects basics (maybe you have an idea about a bigger Wiki or on how to produce cheap PCBs), you are
welcome to get in contact! As for any hobbiest open source project, the projects stability depends on the team size.
And as long as this is mostly a one-man show, the future of the project is always in danger.


Future
======

Since Mira was just a simple “first shoot” to get the project running, the next FogDrive is already in the queue.
After clarifying some questions about the repository structure and the build process, the development of **Vega**
will start. As of now, the planned Features for the Vega FogDrive are:

* MOSFET switch and battery voltage supervision as for Mira
* Measurement of the vaporizer (coil) resistance
* Vaporizer voltage control (step down) via PWM
* Support for different user interfaces

The progress on Vega will highly depend on the private time that can be spend on this. Some support could increase 
the development speed. ;)

The great goal is a fully regulated control that can properly lower and increase the battery’s voltage without
the PWM ripples but with a mostly smooth output voltage. If this can be archived depends also on the available time
and support the project gets.



  
+----------------------------------------------------------------------------------------+
| FogDrive is a free and open project, you can redistribute it and/or modify             |
| it under the terms of the `GNU General Public License`_ as published by                |
| the Free Software Foundation, either version 3 of the License, or any later version.   |
|                                                                                        |
| FogDrive is distributed in the hope that it will be useful,                            |
| but without any warranty; without even the implied warranty of                         |
| merchantability or fitness for a particular purpose.  See the                          |
| GNU General Public License for more details.                                           |
+----------------------------------------------------------------------------------------+

.. _GNU General Public License: http://www.gnu.org/licenses/