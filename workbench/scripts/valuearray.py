#!/usr/bin/env python
# -*- coding: utf-8 -*-

#FogDrive (https://github.com/FogDrive/FogDrive)
#Copyright (C) 2016  Daniel Llin Ferrero

#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.



from __future__ import division
import argparse
import sys


parser = argparse.ArgumentParser(
    prog='valuearray',
    usage='%(prog)s [options]\nPrints a C array containing values according to a specied function and a specified function argument range.\n' \
          'This script is used to create the LED PWM values for FogDrive.'
)

def simple_quadratic(mini, maxi, number):
    a = mini
    b = (maxi-a) / ((number-1)**2)
    result = []
    for n in range(number):
        result.append(
            a + b * n**2
        )
    return result

def exponential(mini, maxi, number):
    delta = maxi - mini
    base = (delta+1) ** (1/number)
    result = []
    for n in range(number):
        result.append(
            mini + base ** (n+1) - 1
        )
    result[0] = mini
    result[-1] = maxi
    print result
    return result

def up_increase(mini, maxi, number, last_delta):
    delta = int(last_delta)
    value = maxi - mini
    result = []
    for n in reversed(range(number)):
        result.append(value)
        value -= delta
        delta -= 1
        if (delta > value - mini) or (delta == 0):
            delta = 1
    result.reverse()
    min_value = mini
    for n in range(number):
        if result[n] < min_value:
            result[n] = min_value
        min_value += 1
    return result

def up_decrease(mini, maxi, number, first_delta):
    _maxi = maxi - mini
    result = [_maxi - v + mini for v in up_increase(0, _maxi, number, first_delta)]
    result.reverse()
    return result

def logarithmic(mini, maxi, number):
    _maxi = maxi - mini
    result = [_maxi - v + mini for v in exponential(0, _maxi, number)]
    print result
    result.reverse()
    return result

functions = {
    'simple-quadratic' : (lambda mini, maxi, number, p: simple_quadratic(mini, maxi, number),[]),
    'exponential':       (lambda mini, maxi, number, p: exponential(mini, maxi, number),[]),
    'logarithmic':       (lambda mini, maxi, number, p: logarithmic(mini, maxi, number),[]),
    'up-increase':       (lambda mini, maxi, number, p: up_increase(mini, maxi, number, p['last-delta']),[('last-delta','The delta between the last two values. (int)')]),
    'up-decrease':       (lambda mini, maxi, number, p: up_decrease(mini, maxi, number, p['first-delta']),[('first-delta','The delta between the first two values. (int)')]),
}
    

parser.add_argument('-a', '--min',    type=int, required=True, help="Minimum value")
parser.add_argument('-b', '--max',    type=int, required=True, help="Maximum value")
parser.add_argument('-n', '--number', type=int, required=True, help="Number of elements")
parser.add_argument('-f', '--function', required=True, help="The used function, one of {'simple-quadratic', 'exponential'}")
parser.add_argument('-p', '--params', help="Function specific extra parameters as 'name:value[,name:value]...'")

args = parser.parse_args()

assert args.min < args.max
assert args.number > 1
assert args.function in functions

params = {p.split(':')[0]:p.split(':')[1] for p in args.params.split(',')} if args.params else {}

number_of_values_per_row = 8
tab_length = 4

function_record = functions[args.function]

f = function_record[0]

for parameter_record in function_record[1]:
    parameter = parameter_record[0]
    help = parameter_record[1]
    if not parameter in params:
        print "Function parameter missing: {p} -> {h}".format(p=parameter, h=help)
        sys.exit(1)

values = f(args.min, args.max, args.number, params)

value_rows = [values[i:i+number_of_values_per_row] for i in range(0, len(values), number_of_values_per_row)] 
    
print ',\n'.join([
        ', '.join([
                str(int(round(value))).rjust(tab_length) for value in value_row
            ]) for value_row in value_rows
    ])
