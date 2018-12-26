#!/bin/bash

gameList='RPS matching_pennies domino'
for name in $gameList; do
	echo 'Resolviendo el juego: ' $name
	./solve_normal_form.sh $name
	echo ' '
done