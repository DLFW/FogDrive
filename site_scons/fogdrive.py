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

class FogDrive(object):
    def __init__(self, mcu, frequency, fog_drive_name):
        self.mcu = mcu
        self.frequency = frequency
        self.fog_drive_name = fog_drive_name
        
    @property
    def src_directory(self):
        return self.fog_drive_name
    
    @property
    def build_directory(self):
        """
        The build directory, relative to the base build directory
        """
        return os.path.join(self.fog_drive_name, self.variant_name)
    
    @property
    def build_file_name(self):
        """
        Filename of the built hex, map and elf files.
        """
        return "fd_{fd}".format(fd = self.fog_drive_name)
    
    @property
    def variant_name(self):
        """
        File system representation name of the variant, used for the build directory.
        """
        return "{mcu}_{f}".format(mcu = self.mcu, f = str(self.frequency)[0:4])
    
    @property
    def cpp_defines(self):
        """
        C pre processor defines as a dict (name -> value) that are injected from the gcc to the sources.
        """
        return {
            'F_CPU' : "{f}UL".format(f = self.frequency),
            'MCUHEADER' : "\\\"{mcu}.h\\\"".format(mcu = self.mcu)
        }
    
    @property
    def cc_flags(self):
        """
        C compiler flags as a list
        """
        return [
            '-mmcu={mcu}'.format(mcu = self.mcu),
            '-g',
            '-Os',
            '-w',
            '-fno-exceptions',
            '-ffunction-sections',
            '-fdata-sections',
        ]
    
class Mira(FogDrive):
    def __init__(self, mcu, frequency):
        FogDrive.__init__(self, mcu, frequency, "mira")