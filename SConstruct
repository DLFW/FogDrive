###############################################################################
# FogDrive (https://github.com/FogDrive/FogDrive)
# Copyright (C) 2016  Daniel Llin Ferrero
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
###############################################################################

import os
from fogdrive import Mira

FogDrives = [
    Mira(
        mcu = "atmega328p",
        frequency = 1000000
    ),
    #Mira(
        #mcu = "attiny45",
        #frequency = 1000000
    #)
]

for fogdrive in FogDrives:
    env = Environment(
        tools = ['avrgcc'],
        fogdrive = fogdrive,
        MCU = fogdrive.mcu,
        CCFLAGS = fogdrive.cc_flags,
        CPPDEFINES = fogdrive.cpp_defines,
    )
    
    SConscript(
        os.path.join("source","mcus",'SConscript'),
        #variant_dir = os.path.join('build','fogdrive','mcus'),
        variant_dir = os.path.join('build', 'fogdrive', 'mcus'),
        exports = ['env']
    )

    SConscript(
        os.path.join("source",fogdrive.src_directory,'SConscript'),
        variant_dir = os.path.join('build','fogdrive',fogdrive.build_directory),
        exports = ['env']
    )
    