#!/bin/bash

cd ../
echo "Creando carpeta"
mkdir -p regret/kuhn
cd src/

echo "Compilando los programas"
g++ normal_form.cpp -o normal_form -std=c++11
g++ behavorial_strategy.cpp -o behavorial_strategy -std=c++11
g++ -I ../ test_kuhn.cpp -o test_kuhn -std=c++11

echo "Creando variables"
TREE=../juegos/forma_extensiva/tree_kuhn.txt
NORMAL_FORM=../juegos/forma_normal/tree_kuhn.txt
MIX_ST=../estrategias/mixtas/kuhn_poker.txt
BEH_ST=../estrategias/comportamiento/kuhn_poker.txt

echo "Creando la forma normal del juego"
./normal_form  $TREE > $NORMAL_FORM

echo "Ejecutando el algoritmo de regret matching"
./test_kuhn $MIX_ST 0.00005

echo "Creando la estrategia de comportamiento"
./behavorial_strategy $TREE $MIX_ST > $BEH_ST

echo "Eliminando los programas"
rm normal_form test_kuhn behavorial_strategy
