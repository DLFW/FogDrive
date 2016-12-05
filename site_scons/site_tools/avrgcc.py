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


"""
The AVR-GCC as SCons tool.
This module set the avr-gcc as compiler, the avr-objcopy as objcopy, and adds the two additonal builders "Elf" and "Hex".

Thanks to https://bitbucket.org/scons/scons/wiki/ToolsForFools and to Marin and Valori Ivanov (https://github.com/metala/avr-gcc-scons-skel.git).
You helped me a lot with this! ;)
"""

import SCons.Util
import SCons.Tool.cc as cc

class AvrGccNotFound(SCons.Warnings.Warning):
    pass
class AvrObjectcopyNotFound(SCons.Warnings.Warning):
    pass
SCons.Warnings.enableWarningClass(AvrGccNotFound)
SCons.Warnings.enableWarningClass(AvrObjectcopyNotFound)


def _detect_avr_gcc(env):
    """
    Return the program name of the avr gcc if it could be found in the PATH.
    Otherwise it raises an error.
    :TODO: On Windows it might be unusual to have the avr-gcc/winavr binary directory in the PATH. We could additonally search for the env variable AVR32_HOME and check if the binary is in there.
    """
    gcc = env.WhereIs('avr-gcc')
    if gcc:
        return gcc
    raise SCons.Errors.StopError(
        AvrGccNotFound,
        "Could not detect avr-gcc compiler. Installed and in the PATH?")


def _detect_avr_objcopy(env):
    """
    Return the program name of the avr objcopy if it could be found in the PATH.
    Otherwise it raises an error.
    :TODO: On Windows it might be unusual to have the avr-gcc/winavr binary directory in the PATH. We could additonally search for the env variable AVR32_HOME and check if the binary is in there.
    """
    objcopy = env.WhereIs('avr-objcopy')
    if objcopy:
        return objcopy
    raise SCons.Errors.StopError(
        AvrObjectcopyNotFound,
        "Could not detect avr objcopy. Installed and in the PATH?")

def _get_elf_builder():
    return SCons.Builder.Builder(action = "$CC -mmcu=${MCU} -Wl,-Map=${TARGET}.map -Os -Xlinker -Map=${TARGET}.map -Wl,--gc-sections -o ${TARGET} ${SOURCES}")
    
def _get_hex_builder():
    return SCons.Builder.Builder(action = "$OBJCOPY -O ihex -R .eeprom $SOURCES $TARGET")

def exists(env):
    return _detect_avr_gcc(env) and _detect_avr_objcopy(env)

def generate(env):
    """Add Builders and construction variables for gcc to an Environment."""
    cc.generate(env)

    env['CC'] = _detect_avr_gcc(env)
    env['OBJCOPY'] = _detect_avr_objcopy(env)
    env.Append(BUILDERS = {
        'Elf': _get_elf_builder(),
        'Hex': _get_hex_builder(),
    })

