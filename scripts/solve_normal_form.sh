#!/bin/bash

echo "Creando carpetas"
mkdir ../regret/$1
cd ../src

echo "Compilando programa"
g++ -I ../ solve.cpp -o solve -std=c++11

echo "Corriendo regret matching"
./solve $1

echo "Creando graficas"

echo "Eliminando programa"
rm solve
