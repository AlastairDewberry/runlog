#!/bin/bash

clear

#g++ -g -Wall -pedantic -I/opt/include -L/opt/lib parser.cpp -DMAIN_TEST -o parser -lxerces-c | tee compile.text

g++ -g -Wall -pedantic -I/opt/include -L/opt/lib MySAXHandler.cpp MySAXParser.cpp -o MySAXParser -lxerces-c
# -DMAIN_TEST
# >(tee compile.output)
