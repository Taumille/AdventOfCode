#!/bin/bash

# Part 1
cat input.txt | grep -Eo "mul\([0-9]+,[0-9]+\)" | sed 's/mul(\([0-9]\+\),\([0-9]\+\))/\1*\2/' | sed ':a;N;$!ba;s/\n/+/g' | bc

# Part 2
grep -oP '(?<=do\(\)).*?(?=don'\''t\(\))' input.txt | grep -Eo "mul\([0-9]+,[0-9]+\)" | sed 's/mul(\([0-9]\+\),\([0-9]\+\))/\1*\2/' | sed ':a;N;$!ba;s/\n/+/g' | bc

