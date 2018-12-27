#!/bin/bash

cd ..
echo "Creando carpetas"
mkdir -p regret/$1
mkdir -p graficas/$1
mkdir -p estrategias/mixtas/$1
mkdir -p tiempos/$1
cd src

echo "Compilando programa"
g++ -I ../ solve.cpp -o solve -std=c++11

echo "Corriendo regret matching"
./solve $1

echo "Creando graficas"
python graphics.py $1

echo "Eliminando programa"
rm solve
