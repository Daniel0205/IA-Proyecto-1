#!/bin/bash

g++ -std=c++11 *.cpp -o run

echo $1

./run $1
