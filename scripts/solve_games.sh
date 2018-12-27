#!/bin/bash

cd ../src
echo "Compilando domino y blotto_game"
g++ domino.cpp      -o domino      -std=c++11
g++ blotto_game.cpp -o blotto_game -std=c++11
echo "3 5" >> input_blotto.txt
echo "Creando input para domino y blotto_game"
./blotto_game < input_blotto.txt > ../juegos/forma_normal/blotto_game.txt
./domino      > ../juegos/forma_normal/domino.txt
echo "Eliminando programas"
rm domino blotto_game input_blotto.txt
cd ../scripts
echo "Resolviendo juegos"
gameList='matching_pennies RPS domino blotto_game'
# gameList='blotto_game'
for name in $gameList; do
	echo 'Resolviendo el juego: ' $name
	./solve_normal_form.sh $name
	echo ' '
done