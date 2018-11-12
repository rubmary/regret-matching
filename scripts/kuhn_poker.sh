#!/bin/bash

cd ../src/
echo "Compilando el programa"
g++ normal_form.cpp -o normal_form -std=c++11
echo "Creando la forma normal del juego"
./normal_form ../juegos/forma_extensiva/tree_kuhn.txt > ../juegos/forma_normal/tree_kuhn.txt
echo "Ejecutando el algoritmo de regret matching"
echo "En construccion"
rm normal_form